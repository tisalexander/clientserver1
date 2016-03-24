#include "maindialog.h"
#include "ui_maindialog.h"
#include <QtNetwork/QHostAddress>

/*------- MainDialog --------------------------------------------------------*/
MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog)
{
	ui->setupUi(this);

	connect();
}

MainDialog::~MainDialog()
{
	delete ui;
}

void MainDialog::onConnect()
{
	if (m_socket.state() == QAbstractSocket::UnconnectedState) {
		m_socket.connectToHost(QHostAddress::LocalHost, 4433);
	} else if (m_socket.state() == QAbstractSocket::ConnectedState) {
		m_socket.disconnectFromHost();
	}
}

void MainDialog::onClose()
{
	qApp->quit();
}

void MainDialog::onSend()
{

}

void MainDialog::onConnected()
{
	ui->pushButtonConnect->setText(tr("Disconnect"));
}

void MainDialog::onDisconnected()
{
	ui->pushButtonConnect->setText(tr("Connect"));
}

void MainDialog::connect()
{
	QObject::connect(ui->pushButtonConnect, SIGNAL(clicked(bool)),
					 SLOT(onConnect()));

	QObject::connect(ui->pushButtonClose, SIGNAL(clicked(bool)),
					 SLOT(onClose()));

	QObject::connect(ui->pushButtonSend, SIGNAL(clicked(bool)),
					 SLOT(onSend()));

	QObject::connect(&m_socket, SIGNAL(connected()),
					 SLOT(onConnected()));

	QObject::connect(&m_socket, SIGNAL(disconnected()),
					 SLOT(onDisconnected()));
}
