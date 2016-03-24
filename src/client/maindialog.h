#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QtGui/QDialog>
#include <QtNetwork/QTcpSocket>

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
	void onConnect();
	void onClose();
	void onSend();

	void onConnected();
	void onDisconnected();

private:
	Ui::MainDialog *ui;
	QTcpSocket m_socket;

	void connect();
};

#endif // MAINDIALOG_H
