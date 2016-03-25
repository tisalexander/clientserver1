#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "chatclient.h"
#include <QtGui/QDialog>

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
	ChatClient m_client;

	void connect();
};

#endif // MAINDIALOG_H
