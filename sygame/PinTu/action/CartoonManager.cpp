#include "CartoonManager.h"
#include <pthread.h>
NS_CC_BEGIN
/**
* ��ȡ������Ϣ ��ʵ�����CartoonInfo::frames ��Ϣ
*/
bool CartoonManager::getCartoonInfo(const std::string& name,int dir,CartoonInfo &info)
{
	return false;
}
/**
* �첽������Դ ����һ���߳�������
* �� cartoon �м��ض���
* <pack name="animation.pack" cartooncount="100">
*      <cartoon name="" id=""><!--����-->
*			<dir value="0" name=""/> <!--ʵ������ ����+ʵ������-->
*		</cartoon>
* </pack>
*/
void CartoonManager::loadSync(const char *configName,CartoonLoadCallback *back)
{
	pthread_t hid;
	pthread_create(&hid, NULL, threadLoadResource, this);
}
void* CartoonManager::threadLoadResource(void* object)
{
	CartoonManager * loader = (CartoonManager*) object;
	if (loader)
	{
		// ������Դ
		// �ȼ��� cartoon ����cartoon ��Ϣ��
		// �ټ���pack ��Ϣ [�ϴ�]
		// �ȶ��� ÿ����һ������ص�һ��
		// thePack.setCallBack(PackLoadCallBack);
		// thePack.doCallback(count); // ��ǰ������ֽ���
		// loadObject() ���� + 1
	}
	return NULL;
}
NS_CC_END