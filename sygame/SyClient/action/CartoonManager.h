#pragma once
#include "vector"
#include "Cartoon.h"
NS_CC_BEGIN
class CartoonLoadCallback{

};

/**
 * ����������
 */
class CartoonManager{
public:
	/**
	 * ��ȡ������Ϣ ��ʵ�����CartoonInfo::frames ��Ϣ
	 */
	bool getCartoonInfo(const std::string& name,int dir,CartoonInfo &info);
	/**
	 * �첽������Դ ����һ���߳�������
	 * �� cartoon �м��ض���
	 * <pack name="animation.pack">
	 *      <cartoon name="" id=""><!--����-->
	 *			<dir value="0" name=""/> <!--ʵ������ ����+ʵ������-->
	 *		</cartoon>
	 * </pack>
	 */
	void loadSync(const char *configName,CartoonLoadCallback *back = NULL);
	
	static void* threadLoadResource(void* object);
private:
	/**
	 * �������� + [dir,cartoon]
	 **/
	std::map<std::string,std::map<int,CartoonInfo> > cartoonInfos;
};

NS_CC_END