/**
 * ��������Ϸ�Ŀ�ʼѡ�����
 */
#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
#include "UIPanel.h"
#include "UIWindow.h"
NS_CC_BEGIN

class HBStartScene{
public:

};
/**
 * ��ʼ���� - ս������ - ��������
 */
class HBStart{
public:
	HBStart()
	{
		_bottomDialog = NULL;
		_heroDialog = NULL;
		_mapDialog = NULL;
		window = NULL;
	}
	bool initFromFile(const char *fileName);
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * ����Ԫ��
	 */
	UIWindow *window;
private:
	/**
	 * ������ť ������븱��ս������
	 * Ӣ����ϢLabel ��� ��չʾ��ϸ��Ϣ ���Ե����װ��ϵͳ ����װ��Scene ���� <UIRichText��Ϣ>
	 * ��ǰ������Ϣ �����չʾ��ϸ��Ϣ ��ϸ��Ϣ�����ѡ��ť �������ѡ�񳡾�
	 * ������ť
	 */
	UIPanel * _bottomDialog;
	/**
	 * Ӣ�۵�ѡ����� Ŀǰ�ӱ��ػ�ȡӢ����Ϣ �������ʱ _bottonDialog ��ʧ ��ѡ����������ʱ _bottonDilog չʾ
	 * Ĭ��չʾ����
	 * ������״̬�� �᲻�ϵĻ�ȡhero �ĸ�����Ϣ �����Զ��Ų�
	 **/
	UIPanel * _heroDialog; 
	/**
	 * ������Ϣ չʾ������Ϣ Ŀǰ�ӱ��ػ�ȡ Ĭ������ 
	 **/
	UIPanel * _mapDialog; 


};

NS_CC_END