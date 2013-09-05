#pragma once
/**
 * ��Ϸ������
 */
#include "cocos2d.h"
#include "UIPanel.h"
#include "UIItem.h"
#include "UIChoiceList.h"
#include "UIBag.h"
#include "UILabel.h"
#include "UIEditField.h"
#include "UIWindow.h"
NS_CC_BEGIN

class StartDialog:public script::tixmlCode,public UIPanel{
public:
	bool initFromFile(const char *fileName);
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	StartDialog()
	{
		mainDialog = NULL;
		window = NULL;
	}
	UIWindow *window;
private:
	void doInitEvent();
	UIPanel *mainDialog;
};

NS_CC_END