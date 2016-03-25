#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QtGui/QDialog>
#include <QtNetwork/QTcpServer>

namespace Ui {
	class MainDialog;
}

/*------- MainDialog --------------------------------------------------------*/
class MainDialog : public QDialog
{
	Q_OBJECT

public:
	explicit MainDialog(QWidget *parent = 0);
	~MainDialog();

private slots:
	void onClose();
	void onNewConnection();
	void onSocketDisconnected();
	void onReadyRead();

private:
	Ui::MainDialog *ui;
	QTcpServer m_server;
	QMap<QTcpSocket *, QTcpSocket *> m_sockets;

	void connect();
};

#endif // MAINDIALOG_H
