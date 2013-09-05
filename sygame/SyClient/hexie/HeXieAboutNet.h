#pragma once
#include "mcenter.h"
#include "singleton.h"
#include "dealcmddelegate.h"
#include "remotefunction.h"
#include "nullcommand.h"
#include "netlib.h"
/**
 * ��Ϣ���ĳ�
 */
class AboutNet:public MessageCenter,public Singleton<AboutNet>{
public:
    AboutNet(){}
    ~AboutNet(){destroy();}
    void init();
	bool connect();
};
extern AboutNet theAboutNode ;
/**
 * ������Ϣ
 **/
class DealCmd:public DealCmdDelegate,public Singleton<DealCmd>,public LocalCallDelegate{
public:
	/**
	 * ������Ϣ
	 * \param socket ����
	 * \param cmd ��Ϣ
	 * \param size ��Ϣ��С
	 */
	void doObjectCmd(Socket *socket,void *cmd,int size);
	/**
	 * ��������Ϣ
	 * \param socket ���Ӿ��
	 * \param object ��Ϣ����
	 */
	void doLocalCmd(Socket *socekt,void *cmd,int size);

	/**
	 * �����������
	 * \param socket ���Ӿ��
	 * \param cmd ��Ϣ
	 * \param size ��Ϣ��С
	 */
	void doPackCmd(Socket *socekt,void *cmd,int size);
};
/**
 * �������ӵĹر�
 */
class DealClose:public SocketCloseDelegate,public Singleton<DealClose>{
public:
	/**
	 * �������ӵ��ͷ�
	 * \param socket ���Ӷ���
	 */
	void handleClose(Socket *socket);
	/**
	 * �������ӵ�����
	 * \param socket ���Ӷ���
	 */
	void handleAdd(Socket *socket);
	/**
	 *  �����i
	 **/
	sys::Mutex _mutex;
};
#define theDeal DealCmd::getMe()
#define theCloseDeal DealClose::getMe()