#include "FarmUI.h"
#include "StartScene.h"
#include "FarmBuild.h"
#include "FarmMap.h"
NS_CC_BEGIN
bool FarmUI::initFromFile(const char *fileName)
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
void FarmUI::takeNode(script::tixmlCodeNode *node)
{
	if (node && node->equal("Config"))
	{
		/**
		 * ������� Я����
		 */
 		script::tixmlCodeNode mainNode = node->getFirstChildNode("opfarm");
		if (mainNode.isValid() && !mainDialog)
		{
			mainDialog = UIPanel::createFromNode(&mainNode);
			window->addPanel(mainDialog);
		}
	}
}
/**
 * ��ʼ������ϵͳ���߼�����ģ��
 */
void FarmUI::doInitEvent()
{
	struct stBindAction:public stExecPanelEach{
		void exec(UIBase *base)
		{
			base->bind(UIBase::EVENT_CLICK_DOWN,ui_object_function(panel,FarmUI::doTouchDown));
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
			base->setPosition(visibleSize.width /2 - base->w /2 -base->x ,visibleSize.height/2 - base->h /2 - base->y);
		} 
		FarmUI *panel;
		stBindAction(FarmUI *panel):panel(panel)
		{
		
		}
	}exec(this);
	mainDialog->execEach(&exec);
}
void FarmUI::doTouchDown(UIBase *item)
{
	// ���Դ�������
	FarmBuildInfo buildInfo = map->findFarmInfoById(item->uniqueId);
	FarmBuild * build = FarmBuild::createFromBuild(&buildInfo);
	if (build)
	{
		if (!map->placeBuild(build,build->info.gridX,build->info.gridY))
		{
			build->release(); // �ͷ�build ָ��
		}
	}
}
NS_CC_END