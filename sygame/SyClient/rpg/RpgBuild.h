/**
 * ϵͳ�д������ֽ�����
 * �ٻ��� �� ������
 */
#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
#include "RpgObject.h"
NS_CC_BEGIN
class RpgMap;
class RpgBuild;
class RpgHpValueUI;// Ѫ����
class RpgBuildEventcallback{
public:
	virtual void doTouch(RpgBuild *build ) = 0;
};
/**
 * ��������Ϣ
 */
class RpgBuildInfo{
public:
	/**
	 * ���Ӻ�����
	 */
	int gridX;
	/**
	 * ����������
	 */
	int gridY;
	/**
	 * ���������
	 */
	int gridWidth;
	/**
	 * ���������
	 */
	int gridHeight;

	bool initWithNode(script::tixmlCodeNode * node);
	/**
	 * ���
	 */
	int id ;
	/**
	 * ����������
	 */
	std::string buildName;
	/**
	 * ��������
	 **/
	int opType; 

	/**
	 * Ѫ��
	 */
	int maxHp;
	std::string name;
	enum {
		OP_NULL = -1,
		CAN_PICK = 0, // ���Լ���
		CAN_MOVE = 1, // �����ƶ�
		CAN_VISIT = 2, // ���Է���
	};
	RpgBuildInfo()
	{
		id = -1;
		gridWidth = gridHeight = -1;
		gridX = gridY = -1;
		opType =CAN_MOVE;
	}
	RpgBuildInfo & operator = (const RpgBuildInfo &info)
	{
		gridX = info.gridX;
		gridY = info.gridY;
		gridWidth = info.gridWidth;
		gridHeight = info.gridHeight;
		id = info.id;
		buildName = info.buildName;
		this->opType = info.opType;
		return *this;
	}
};
/**
 * ������
 */
class RpgBuild:public CCNode{
public:
	enum{
		VISIT_TYPE = 0, // ������
		SUMMON_TYPE = 1,// �ٻ���
		BUILD_NULL = -1, // ��Ч������
	};
	int buildType;
	RpgBuild()
	{
		buildType = BUILD_NULL;
		buildSprite = NULL;
		actionId = -1;
		map = NULL;
		uniqueId = 0;
		callback = NULL;
		hp = 5;
		hpShow = NULL;
	}
	int hp;
	RpgHpValueUI *hpShow;
	void setCanMove(){info.opType = RpgBuildInfo::CAN_MOVE;}
	void setCanVisit(){info.opType= RpgBuildInfo::CAN_VISIT;}
	/**
	 * ����λ��
	 */
	void setPosition(float px,float py);
	/**
	 * �����Ƿ��ڽ�����
	 **/
	bool checkIn(float tx,float ty);
	RpgBuildInfo info;
	/**
	 * �ӽڵ��д���������
	 */
	static RpgBuild * createFromNode(script::tixmlCodeNode * node);
	bool initWithNode(script::tixmlCodeNode * node);
	/**
	 * ����һ��Build
	 */
	static RpgBuild *createFromBuild(RpgBuildInfo *buildInfo);
	bool initWithBuild(RpgBuildInfo *buildInfo);
	int actionId; // ��ǰ����Ϊ

	CCSprite *buildSprite;
	RpgMap *map;
	std::vector<CCSprite*> gridBacks;
	void showInvalidGridBack();
	void showValidGridBack();
	void showNonBack();
	void drawGrid();
	int uniqueId;
	void preSetPosition(float px,float py);
	void showHp();
	void doTouchDown();
	void bind(RpgBuildEventcallback * call){callback = call;}
	RpgBuildEventcallback *callback;
	virtual CartoonInfo* v_makeCartoon(int actionType){return NULL;}
	virtual void v_putCartoon(CartoonInfo *action){return ;}
};

class RpgBuildManager:public script::tixmlCode{
public:
	RpgBuildManager();
	static RpgBuildManager &getMe()
	{
		static RpgBuildManager rbm;
		return rbm;
	}
	void init();
	void takeNode(script::tixmlCodeNode *node);
	bool findBuildInfo(int id,RpgBuildInfo &info);
	std::map<int,RpgBuildInfo> buildInfos;
	typedef std::map<int,RpgBuildInfo>::iterator BUILD_INFOS_ITER;
};
NS_CC_END