#include "chatclient.h"

/*------- ChatClient --------------------------------------------------------*/
ChatClient::ChatClient(QObject *parent)
	: QObject(parent)
{
	connect();
}

ChatClient::~ChatClient()
{
}

void ChatClient::connectToHost(QHostAddress address, quint16 port)
{
	m_socket.connectToHost(address, port);
}

void ChatClient::disconnectFromHost()
{
	m_socket.disconnectFromHost();
}

void ChatClient::sendMessage(const QString &text)
{
	m_socket.write(text.toAscii().constData(), text.size());
}

QAbstractSocket::SocketState ChatClient::state() const
{
	return m_socket.state();
}

void ChatClient::connect()
{
	QObject::connect(&m_socket, SIGNAL(connected()),
					 SIGNAL(connected()));

	QObject::connect(&m_socket, SIGNAL(disconnected()),
					 SIGNAL(disconnected()));
}
