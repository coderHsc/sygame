/**
 * ������ �����ƶ��� ������ ϵͳ�� С��ͼ ����ͷ��
 */
#pragma once
#include "cocos2d.h"
#include "RpgPlayerBag.h"
#include "UICenterBag.h"
#include "xmlScript.h"
#include "UITextArea.h"
NS_CC_BEGIN
class RpgMap;
class RpgPlayer;
class RpgUI;
class RpgSkillData;
/**
 * 1.������ �ǿɱ�� ��Ҫ���� ��.uipack ������ʱ �������ļ��л�ȡui��Ϣ ���ߴ�.uipack �л�ȡ��Ϣ
 * ���̵�ʱ�� ����Ҫ�������ͬ�� ������ֻ���Ƹü����Ƿ���� �ͻ����ڼ����ͷŵ�ʱ�� ��Ҫ�ж�������������
 * ��֤���ܵĴ���
 *
 * 2.����ͷ�� ������������������Ϣ λ�ô������ļ��м��� ������������ ���� .tmp �ļ�
 * 3.С��ͼ
 * 4.�ƶ��� ����lua�ű� ����ʵ�ʶ����ƶ��̵��߼� �� չʾ
 * 5.ϵͳ�� �������ж�ȡ ����lua��ʵ�����߼� �ر� ��Ч ���� ���� ���� ���� ==
 * 6.������ʾ��Ϣ �ò�����luaʵ�� on_visit �¼��Ĵ��� on_leave �¼��Ĵ���
 * 7.�������
 *		�������� .pbag ��
 */
class RpgMoveOPUI:public CCNode{
public:
	CCPoint opMoveCenter;
	// ���Բ�����ɫ�ƶ� 
	static RpgMoveOPUI* create(RpgPlayer *player);
	bool init(RpgPlayer *player);
	RpgPlayer *player;
	CCTouch *nowTouch;
	/**
	 * ������
	 * \parma touchType �������
	 * \param touchPoint �����
	 */
	bool doTouch(int touchType,CCTouch* touch);
	RpgMoveOPUI()
	{
		nowTouch = NULL;
		player = NULL;
		dirSprite = NULL;
		nowTouchIn = false;
		tagSprite = NULL;
	}
	bool nowTouchIn; // ��ǰ�Ƿ������ϲ���

	void showTouch(int dirType);
	CCSprite *dirSprite;
	CCSprite * tagSprite;
}; // �ƶ��� ����һֱ��Game��

class RpgHpValueUI:public CCNode{
public:
	static RpgHpValueUI* create(float maxValue,float defaultValue,const char *upName="hpstar2.png",const  char *backName="hpstar1.png");
	bool init(float maxValue,float defaultValue,const char *upName,const  char *backName);
	
	void setValue(float value);
	RpgHpValueUI()
	{
		maxValue = 0;
		value = 0;
		backSprite = NULL;
		valueSprite = NULL;
		width = 0;
	}
private:
	int width;
	float maxValue;
	float value;
	CCSprite *backSprite;
	CCSprite *valueSprite;
}; // ��ɫѪ��ֵ

class RpgPlayerSimpleInfoUI:public CCNode{
public:
	static RpgPlayerSimpleInfoUI* create(RpgPlayer *player);
	bool init(RpgPlayer *player);
	RpgPlayerSimpleInfoUI()
	{
		hpValue = NULL;
		player = NULL;
		tag = 0;
	}
	void update(); // ��������

	void resume();
private:
	int tag;
	RpgHpValueUI *hpValue;
	std::vector<RpgHpValueUI*> hpValues;
	RpgPlayer *player;

}; // ��ɫ������Ϣչʾ һ��ͷ�� һ��Ѫ��

/**
 * ��ɫװ����Ϣ �� ����ֵ
 */
class RpgPlayerInfoUI:public UISuperBag,public script::tixmlCode{
public:
	static RpgPlayerInfoUI* create();
	/**
	 * ��ʼ������λ�� �Լ��ɸ������ݵ�λ��
	 **/
	bool init();
	RpgPlayerInfoUI()
	{
		
	}
	/**
	 * ������ֵ
	 */
	void updateValue(const std::string& content,float value);

	/**
	 * ��ȡ��ǰ���ӵĿ�
	 */
	float getViewWidth();
	/**
	 * ��ȡ��ǰ���ӵĸ�
	 **/
	float getViewHeight();
	const CCSize & getContentSize()
	{
		return CCSizeMake(getViewWidth(),getViewHeight());
	}
private:
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * ����ֵ��λ��
	 */
	CCPoint getValuePosition(const std::string& content);
	std::map<std::string,CCLabelTTF*> values;
	std::map<std::string,CCPoint> valuePositions;
	typedef std::map<std::string,CCLabelTTF*>::iterator VALUES_ITER;
	typedef std::map<std::string,CCPoint>::iterator VALUES_POS_ITER;
	/**
	 * ��ȡ��ǰid ������λ��
	 */
	virtual CCPoint getPixelPosition(int id);

	virtual int getNowTouchBagIdByCursorPosition(const CCPoint& pos);
	/**
	 * ��������Ƿ���������
	 */
	virtual bool checkIn(int x,int y);
	std::vector<CCPoint> positions; // �㼯��
}; // ��ɫ��Ϣ չʾװ�� �� ������Ϣ չʾ�������Ϣ

/**
 * ���᷽�����չʾ��Ϣ
 */
class RpgAdSysUI:public CCNode{
public:
	static RpgAdSysUI* create();
	bool init();
	/**
	 * ��ʱ��
	 */
	void tick();

	void addContent(const std::string& content);
private:
	std::list<CCLabelTTF*> infos;
	std::vector<CCLabelTTF*> temps;
}; // ϵͳ����չʾ

/**
 * ���ٹ�����Ŀ
 */
class RpgQuickItem:public UICenterItem{
public:
	RpgQuickItem()
	{
		quickType = 0;
		skillData = NULL;
		invalid = false;
		cdtime = 1.0f;
	}
	int cdtime;
	int quickType; // ��������
	std::string skillName; // ��������
	RpgSkillData *skillData; // ��������
	static RpgQuickItem* create(int quickId);
	static RpgQuickItem * create(const char *upName,const char * downName,const CCSize & rect);
	bool invalid; // ��ǰ������Ч��״̬
	/**
	 * չʾCD ��Ч
	 */
	void startShowCD();
	void cdTimeEnd(CCNode *pSender,void *arg);
};
class RpgQuickOPUI:public UICenterBag,public script::tixmlCode{
public:
	// ��ʼ��һ���������� ������Ե�����ߵ������ ������ҩƷ ���� ���� ��Ŀ֮������໥�ƶ�
	static RpgQuickOPUI * create(RpgPlayer *player);
	bool init(RpgPlayer *player);
	RpgPlayer *player;
	RpgQuickOPUI()
	{
		player = NULL;
		
	}
	/**
	 * չʾ��Ŀ
	 * \param item ��չʾ��item û����ʱֱ��չʾ
	 */
	virtual void showItemWithXml(int dirType,UICenterItem *item);
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * չʾ��Ŀ
	 * \param item ��չʾ��item û����ʱֱ��չʾ
	 */
	virtual void showItem(int dirType,UICenterItem *item);

	void onClick();
	std::vector<CCPoint> pointList;
};// ������

class RpgSummonOPUI
{
public:
	// ����Ұ������ȡ�����ٻ��ĵ��� ���ɲ���Item ����� ��Ŀ�괦Ѱ�ҿ����� ���
};// �ٻ��� �빥���̲���ͬʱչʾ
/**
 * ������Ϸ�� 
 * 1.�ر� 
 * 2.չʾ����İ��� 
 * 3.չʾ�ٻ���
 */
class RpgSystemOPUI:public UICenterBag{
public:
	static RpgSystemOPUI* create(RpgUI *uiSys);
	bool init(RpgUI *uiSys);
	RpgSystemOPUI()
	{
		
	}
	void showItem(int dirType,UICenterItem *item);
}; // ϵͳ������

class RpgTalkNpcOPUI{

}; // NPC���������

/**
 * ��ϵͳ�еĹ����Ժ�ɫ�� �����λ�ñ�ʶ���� ���ĵ������Ϊ����
 */
class MiniMap:public CCSprite{
public:
	static MiniMap* create();
	bool init();
	void visit();
	bool checkTimeOut();
	cc_timeval lastTime;
};
class RpgMinMapUI:public CCNode{
public:
	static RpgMinMapUI* create(RpgMap *map);
	bool init(RpgMap *map);
	RpgMinMapUI()
	{
		map = NULL;
		mask = NULL;
		miniPlayer = NULL;
		target = NULL;
		miniMap = NULL;
	}
	void setSize(const CCSize &size);
	/**
	 * ���µ�
	 */
	void updatePosition(const CCPoint &point);
	void visit();
private:
	MiniMap * miniMap;
	CCSprite * target;
	RpgMap *map;
	CCSprite *mask;
	CCSize minMapSize;
	CCSprite *miniPlayer;
}; // С��ͼ 
/**
 * ��ͼ�༭��ָ��
 */
class RpgMapOPUI:public UICenterBag{
public:
	static RpgMapOPUI* create(RpgUI *uiSys);
	bool init(RpgUI *uiSys);
	RpgMapOPUI()
	{
		
	}
	void showItem(int dirType,UICenterItem *item);
}; // ��ͼ�༭��

/**
 * һ�ֽ�������Ϣ��ʾ
 */
class RpgText:public CCNode{
public:
	static RpgText * create(script::tixmlCodeNode *node);
	static RpgText *create(const char *str,float width,float fontSize,const ccColor3B& color);
	bool init(const char *str,float width,float fontSize,const ccColor3B& color);
	void update(const std::string &content);
private:
	UIMultiLineArea* infoLabel;
	RpgText()
	{
		infoLabel = NULL;
	}
};
class RpgInfoUI:public CCNode,public script::tixmlCode{
public:
	/**
	 * ��ʼ��
	 */
	bool init(const char *fileName);
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	std::map<std::string,RpgText*> updateContents;
	typedef std::map<std::string,RpgText*>::iterator UPDATE_CONTENTS_ITER;

	std::map<std::string,CCSprite*> sprites; // �����б�
	std::vector<RpgXmlBag*> bags;
	/**
	 * ����name ָ������ֵ
	 */
	void updateNumber(const std::string& name,int number);

	void updateString(const std::string &name,const std::string& content);
	/**
	 * ����ÿ��tag��չʾ
	 */
	void show(const std::string &name,bool showTag);

	/**
	 * չʾ
	 */
	void show();
	/**
	 * ����
	 */
	void hide();
	/**
	 * ������
	 **/
	bool doTouch(int touchType,const CCPoint &touchPoint);
    UICenterItem * getBtnByName(const std::string & name);
    std::map<std::string,UICenterItem*> buttons;
	//UICenterItem *close;
	const CCSize & getContentSize();
	CCSize backSize;
};

class RpgStepEndUI:public RpgInfoUI{
public:	
	/**
	 * ��������
	 */
	static RpgStepEndUI* create();
};

class RpgVisitUI:public RpgInfoUI{
public:
	/**
	 * ��������
	 */
	static RpgVisitUI* create();
};

class RpgScoreUI:public RpgInfoUI{
public:
	static RpgScoreUI*create();
};
/**
 * ������Ϣ˵��
 */
class RpgItemDescUI:public RpgInfoUI{
public:
	/**
	 * �������ߵ�����
	 */
	static RpgItemDescUI *create();
	/**
	 * չʾ����
	 */
	void showItem(RpgItem *item);
	
};
/**
 * RPG ��UIϵͳ
 */
class RpgUI:public UIBase{
public:
	/**
	 * ֱ�Ӵ���
	 */
	static RpgUI* create(RpgMap *map,RpgPlayer *player,CCNode *parent);
	/**
	 * ��ʼ�� �趨��ʼ����
	 **/
	bool init(RpgMap *map,RpgPlayer *player,CCNode *parent);
	/**
	 * ����uiType չʾ��ͬ��UI
	 */
	void showUI(int uiType);
	
	//static RpgPlayer * gloabPlayer;
	enum{
		TOUCH_DOWN = 0, // ����
		TOUCH_MOVE = 1, // �ƶ�
		TOUCH_END = 2, // ����
	};
	enum{
		UI_TYPE_MOVE, // �ƶ���
		UI_TYPE_QUICK, // ����� ���Խ���ͬ���͵�UI ������ Ȼ�������ָ�UI���¼���Ӧ ��Ӧ��Item
		UI_TYPE_SUMMON, // �ٻ���
		UI_TYPE_TALK, // �Ի���
		UI_TYPE_PLAYER_INFO, // ��ɫ��Ϣ��
		UI_TYPE_MINI_MAP, // С��ͼ
		UI_TYPE_NPC_TALK, // NPC������Ϣ
		UI_TYPE_MAP_OP, // ��ͼ����
		UI_TYPE_BAG, // �������
		UI_TYPE_SHOP, // �̵�
	};
	/**
	 * ������
	 * \parma touchType �������
	 * \param touchPoint �����
	 */
	bool doTouch(int touchType,CCTouch *touch);
/**
 * ϵͳ�е�ǰ�Ľ���Ԫ��
 **/
	RpgPlayer *player; // ��ǰ��ɫ
	RpgMap *map; // ��ͼ
	RpgMoveOPUI *moveOP; // �ƶ���
	RpgPlayerInfoUI *playerInfo; // ��ɫ��Ϣ��
	RpgPlayerSimpleInfoUI *simplePlayerInfo;//�򵥽�ɫ��Ϣ
	RpgQuickOPUI *quickOP;// �����
	RpgSummonOPUI *summonOP; // �ٻ���
	RpgPlayerBag *playerBag; // ��Ұ���
	RpgSystemOPUI *systemOP; // ϵͳ����
	RpgMinMapUI *minMapInfo; // С��ͼ��Ϣ
	RpgTalkNpcOPUI *talkNpcOP; // ���������
	RpgAdSysUI *adUI; // ����Ŀ
	RpgMapOPUI *mapOpUI;//��ͼ������ 
	RpgShop *shop; // �̵�
	RpgStepEndUI *stepEnd;
	RpgVisitUI *visitUI; // ����UI
	RpgScoreUI *scoreUI; // ����UI
	RpgItemDescUI *descUI; // ����UI
	RpgUI()
	{
		descUI = NULL;
		scoreUI = NULL;
		visitUI = NULL;
		stepEnd = NULL;
		simplePlayerInfo = NULL;
		moveOP = NULL;
		playerInfo = NULL;
		quickOP = NULL;
		summonOP = NULL;
		player = NULL;
		playerBag = NULL;
		systemOP = NULL;
		minMapInfo = NULL;
		talkNpcOP = NULL;
		adUI = NULL;
		mapOpUI = NULL;
		map = NULL;
		shop = NULL;
	}
	/**
	 * ִ�ж�ʱ��Ϊ
	 */
	void tick();
	void doItemDownPlayerBag(UIBase *base);

	void updateHp(RpgPlayer *player);

	void showItemDescInfo(RpgItem *item);
};
NS_CC_END