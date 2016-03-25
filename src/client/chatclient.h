#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

/*------- ChatClient --------------------------------------------------------*/
class ChatClient : public QObject
{
	Q_OBJECT

public:
	ChatClient(QObject *parent = 0);
	~ChatClient();

	void connectToHost(QHostAddress address, quint16 port);
	void disconnectFromHost();

	void sendMessage(const QString &text);

	QAbstractSocket::SocketState state() const;

signals:
	void connected();
	void disconnected();

private:
	QTcpSocket m_socket;

	void connect();
};

#endif // CHATCLIENT_H
