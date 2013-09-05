#include "StartDialog.h"
#include "UIButton.h"
#include "UIWindow.h"
NS_CC_BEGIN
bool StartDialog::initFromFile(const char *fileName)
{
	unsigned long nSize = 0;
	unsigned char * buffer = CCFileUtils::sharedFileUtils()->getFileData(fileName,"rb",&nSize);
	if (!nSize)return false;
	if (script::tixmlCode::initFromString((char*)buffer))
	{
		doInitEvent();
		return true;
	}
	return false;
}
/**
	* �������ļ��м�������
	* \param node ���ø��ڵ�
	*/
void StartDialog::takeNode(script::tixmlCodeNode *node)
{
	if (node && node->equal("Config"))
	{
 		// ����Label TextArea Button ���ɽ���ϵͳ
		// ������ӭ����
		script::tixmlCodeNode mainNode = node->getFirstChildNode("start");
		if (mainNode.isValid() && !mainDialog)
		{
			mainDialog = UIPanel::createFromNode(&mainNode);
			window->addPanel(mainDialog);
			mainDialog->setZOrder(12);
		}
	}
}

void StartDialog::doInitEvent()
{
	
	CCSize s = CCDirector::sharedDirector()->getWinSize();
   
	do{
		GET_UI_BYNAME(mainDialog,UIButton,reqLoginBtn,"login");
		if (reqLoginBtn)
		{
			struct stReqLogin:public UICallback{
				void callback(UIBase *base)
				{
					// ���Զ�ȡϵͳ�е� ��¼�� ��¼���� �����͵�����
					// ��Request.cpp �д�������
					// �����ȴ�����
					//theNet.reqLogin("test","123456"); ���Ե�¼��ϵͳ
				}
				stReqLogin(UIWindow *window):window(window)
				{
				
				}
				UIWindow *window;
			};
			reqLoginBtn->bind(UIBase::EVENT_CLICK_DOWN,new stReqLogin(window));
		}
		
	} while (false);
}


NS_CC_END
