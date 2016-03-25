#include "maindialog.h"
#include "ui_maindialog.h"
#include <QtCore/QDebug>
#include <QtNetwork/QTcpSocket>

/*------- MainDialog --------------------------------------------------------*/
MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);

	if (!m_server.listen(QHostAddress::LocalHost, 4433)) {
		qDebug() << "Server can't start listening.";
	}

	ui->lineEditHostAddress->setText(m_server.serverAddress().toString());
	ui->lineEditClientCount->setText(QString::number(m_sockets.count()));

	connect();
}

MainDialog::~MainDialog()
{
	delete ui;
}

void MainDialog::onClose()
{
	qApp->quit();
}

void MainDialog::onNewConnection()
{
	if (m_server.hasPendingConnections()) {
		QTcpSocket *socket = m_server.nextPendingConnection();

		m_sockets.insert(socket, socket);

		QObject::connect(socket, SIGNAL(disconnected()),
						 SLOT(onSocketDisconnected()));

		QObject::connect(socket, SIGNAL(readyRead()),
						 SLOT(onReadyRead()));
	}

	ui->lineEditClientCount->setText(QString::number(m_sockets.count()));
}

void MainDialog::onSocketDisconnected()
{
	QTcpSocket *socket = static_cast<QTcpSocket *>(sender());

	if (m_sockets.contains(socket)) {
		QObject::disconnect(socket);
		m_sockets.remove(socket);
	}

	ui->lineEditClientCount->setText(QString::number(m_sockets.count()));
}

void MainDialog::onReadyRead()
{
	QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
	const qint64 bytes = socket->bytesAvailable();

	QByteArray array(bytes, (char)0);
	socket->read(array.data(), bytes);

	QString text = QString::fromAscii(array.constData());

	ui->listWidget->addItem(text);
}

void MainDialog::connect()
{
	QObject::connect(ui->pushButton, SIGNAL(clicked(bool)),
					 SLOT(onClose()));

	QObject::connect(&m_server, SIGNAL(newConnection()),
					 SLOT(onNewConnection()));
}
