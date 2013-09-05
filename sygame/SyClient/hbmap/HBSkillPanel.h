#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
#include "UIPanel.h"
#include "UIWindow.h"
NS_CC_BEGIN
class HBMap;
class HBMonster;
/**
 * ���ļ��ܲ���
 * ��Ҫ��Ϊ����� �����������
 * һЩ��ť %100 �ȵ�λ�ã���С�趨 
 **/
class HBSkillPanel:public script::tixmlCode,public UIPanel{
public:
	bool initFromFile(const char *fileName);
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	HBMap *map;
	UIWindow *window;
	HBMonster *player;
	HBSkillPanel()
	{
		map = NULL;
		window = NULL;
		player = NULL;
		mainDialog = NULL; 
		opDialog = NULL;
	}
private:
	UIPanel *mainDialog;
	UIPanel *opDialog;
	void doInitEvent();
	void doTouchDown(UIBase *item);

	void doGiveup(UIBase *item);
};

NS_CC_END