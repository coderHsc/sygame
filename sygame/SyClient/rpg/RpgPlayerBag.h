#pragma once
#include "cocos2d.h"
#include "UISuperBag.h"
#include "xmlScript.h"
#include "UIScrollView.h"
NS_CC_BEGIN
/**
 * ��ɫ�İ��� ����ٻ����� �� װ������� ҩˮƿ��
 */
class RpgItemInfo{
public:
	int itemId; // ���߱��
	std::string name; // ��������
	int itemType; // ��������
	int equipPos; // ��װ�����ϵ�λ��
	int buildId; // ��Ӧ�Ľ�����λ��
	int functionType; // ��Ӧ�Ĺ���
	int level; // Ʒ��
	std::string spriteName; // ��������
	std::string desc; // ��Ӧ������
	int addSpeed; // �����ٶ�
	int addLife; // ��������
	int addHp; // ����Ѫ��
	int addAtkValue; // ���ӹ���ֵ
	int addAtkValuePercent; // ���ӹ���ֵ�İٷֱ�
	int maxNum;
	enum{
		ITEM_TYPE_SUMMON, // �ٻ�
		ITEM_TYPE_EQUIP, // װ��
		ITEM_TYPE_HP, // Ѫƿ
		ITEM_TYPE_SKILL, // ����
	};
	RpgItemInfo()
	{
		itemId = 0;
		itemType = ITEM_TYPE_EQUIP;
	}
	void takeNode(script::tixmlCodeNode *node);
};
class RpgItemDatas:public script::tixmlCode{
public:
	static RpgItemDatas * getMe()
	{
		static RpgItemDatas data;
		return &data;
	}
	void init();
	
	bool get(int itemId,RpgItemInfo &info);

	void takeNode(script::tixmlCodeNode *node);

	std::map<int,RpgItemInfo> infos;
};
#define theItemData RpgItemDatas::getMe()
/**
 * �����е���Ŀ
 */
class RpgItem:public UIItem{
public:
	/**
	 * ������Ŀ չʾ���ǵ���ͼ�� ����������������ͬ�Ĵ��� �������С 6 * 6 ÿ����Ŀ 64 * 64
	 */
	static RpgItem*create(int dataid);
	bool init(int dataid);
	RpgItemInfo info;
	bool canMove(int bagId);
	virtual void setSize(float w,float h);
	CCSprite *content;
	int num;
	RpgItem()
	{
		num = 0;
		content = NULL;
		numberLbl = NULL;
	}
	CCLabelTTF *numberLbl;
	void showNum();
};

/**
 * ����
 **/
class RpgPlayerBag:public UISuperBag{
public:
	static RpgPlayerBag* create();
	bool init();
	int nowItemId;
	virtual bool setItem(UIItem *item,int id);
	virtual bool addItem(int itemId,int itemNum);
	/**
	 * ��ȡ��ǰ���ӵĿ�
	 */
	float getPixelWidth();
	/**
	 * ��ȡ��ǰ���ӵĸ�
	 **/
	float getPixelHeight();
	
	/**
	 * ͨ��bagid��ȡzpos
	 */
	//zPos getZPosByBagId(int bagId);
	CCPoint getPixelPosition(int x,int y);
	const CCSize & getContentSize();
public:
	/**
	 * ��ȡ��ǰid ������λ��
	 */
	virtual CCPoint getPixelPosition(int id);

	virtual int getNowTouchBagIdByCursorPosition(const CCPoint& pos);
	/**
	 * ��������Ƿ���������
	 */
	virtual bool checkIn(int x,int y);

	float _width; // ��
	float _height; // ��
	float _eachUpSpan; // ÿ���� span
	float _eachLeftSpan; // ÿ����span
	RpgPlayerBag()
	{
		_width = _height = 0;
		_eachUpSpan = _eachLeftSpan = 0;
		nowItemId = -1;
	}
	float getViewWidth();
	float getViewHeight();
};

/**
 * �̳�ϵͳ ���Թ�����չʾϵͳ�г��۵ĵ���
 */
class RpgShop:public RpgPlayerBag,public script::tixmlCode{
public:
	/**
	 * ����UI����
	 */
	static RpgShop *create();
	bool init();
	const CCSize & getContentSize();
	void show();
	void hide();
	bool isVisible();
	UIBase *view;

	void takeNode(script::tixmlCodeNode *node);
};
/**
 * RPG ����
 */
class RpgXmlBag:public RpgPlayerBag,public script::tixmlCode{
public:
	/**
	 * ����UI����
	 */
	static RpgXmlBag *create(const char*bagName);
	static RpgXmlBag *create(script::tixmlCodeNode *node);
	bool initWithNode(script::tixmlCodeNode *node);
	bool init(const char*bagName);
	const CCSize & getContentSize();
	void show();
	void hide();
	bool isVisible();
	void addToParent(CCNode *node);
	void takeNode(script::tixmlCodeNode *node);
	bool doTouch(int touchType,const CCPoint &touchPoint);
	RpgXmlBag()
	{
		view = NULL;
	}
	UIBase *view;
};
NS_CC_END