#include "HeXieAboutNet.h"
#include "sstream"
#include "netlib.h"
#include "selectpool.h"
#include "AboutRequest.h"

/**
 * ������Ϣ
 * \param socket ����
 * \param cmd ��Ϣ
 * \param size ��Ϣ��С
 */
void DealCmd::doObjectCmd(Socket *socket,void *cmd,int size)
{
	ENTER_FUNCTION
	theAboutNode.handle(&theRequest,cmd,size,socket);
};


/**
 * �������ӵ����Ӹ�
 * \param socket ���Ӷ���
 */
void DealClose::handleAdd(Socket *socket)
{
	
}
/**
 * �������ӵ��ͷ�
 * \param socket ���Ӷ���
 */
void DealClose::handleClose(Socket *socket)
{
	ENTER_FUNCTION
	_mutex.lock();
	ClientNode * client = theClient.addRemoteClient("request");
	if (client)
	{
		if (socket == client->getSocket())
		{
			printf("xxx");
		}
	}
	_mutex.unlock();
}

/**
 * ��������Ϣ
 * \param socket ���Ӿ��
 * \param object ��Ϣ����
 */
void DealCmd::doLocalCmd(Socket *socket,void *cmd,int size)
{
	// ������
};
/**
 * �����������
 * ���������Կͻ�����Ϣ�Ĵ���
 * \param socket ���Ӿ��
 * \param cmd ��Ϣ
 * \param size ��Ϣ��С
 */
void DealCmd::doPackCmd(Socket *socket,void *cmd,int size)
{
	// ������
}
AboutNet theAboutNode ;
/**
 * �ڵ���Ϣ���ĵĳ�ʼ��
 **/
void AboutNet::init()
{
	static bool init = false;
	if (!init) // ȷ����ʼ��ֻ��һ��
	{
		// ��½����
		BIND_FUNCTION(1,AboutRequest,getMapInfo); //ע�ᵽ��½����
		BIND_FUNCTION(2,AboutRequest,retMapInfo); //ע�ᵽ��½����
		init = true;
		ConnectionSelectPool *pool = new ConnectionSelectPool();
		pool->setDealCmdDelegate(&theDeal);
		pool->setSocketCloseDelegate(&theCloseDeal);
		theClient.setConnectionPool(pool);
		pool->start();
		theClient.start();
		WSADATA wsaData;
		int nResult;
		nResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		// ����(һ�㶼�����ܳ���)
		if (NO_ERROR != nResult)
		{
	//		this->_ShowMessage(_T("��ʼ��WinSock 2.2ʧ�ܣ�\n"));
			return; 
		}	

	}
}


bool AboutNet::connect()
{
	ClientNode * client = theClient.addRemoteClient("request");
	std::string ip="localhost";
	WORD port = 4008;
	if (client)
	{
		if (!client->connect(ip.c_str(),port))
		{
			client->getSocket()->setInvalid();
			return false;
		}
		else
		{
			client->reconnect(ip.c_str(),port);
			theRequest.getMapInfo(client->getSocket(),100,100); // ��������map����Ϣ
			//client->getSocket()->setInvalid();
		}
	}
	return true;
}