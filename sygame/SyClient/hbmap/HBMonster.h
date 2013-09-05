#pragma once
#include "MTAction.h"
#include "cocos2d.h"
#include "xmlScript.h"
#include "UIItem.h"
#include "UIValue.h"
#include "Astar.h"
NS_CC_BEGIN
/**
 * ���PK ��Ϸ����
 * ������Ҫ�� �ṩ���Monster ��PK ��·��Ϊ ����һ���򵥵�ֱ��Ѱ·��Ϊ
 */
#define OP_SIZE 256
class HBMap;
class HBMonsterInfo{
public:
	int uniqueId; // Ψһ��
	int atkActionId;
	int walkActionId;
	int beAttackActionId;// ��������actionId
	int idleActionId; // ���е�id
	int monsterType; // ��������
	int deathActionId; // ����ִ����Ϊ
	float _hp; // ��ǰѪ��
	float _maxHp; // ��ǰ���Ѫ��
	int _step; // ÿ��
	float _atkTime; // ����ʱ��
	float _eyeshort; // ���Ӿ���
	int _atkDistance;
	float x;
	float y;
	HBMonsterInfo()
	{
		x = y = 0;
		
		idleActionId = -1;
		atkActionId = -1;
		walkActionId = -1;
		deathActionId = -1;
		uniqueId = -1;
		beAttackActionId = -1;
		
		_atkTime = 0;
		_eyeshort = 0;
		monsterType = 0;
		_atkDistance = -1;
		
		_hp = 0;
		_maxHp = 0;
	}

	void initWithNode(script::tixmlCodeNode *node);
};
class HBMonster:public CCSprite,public MTAction,public zAStar<>{
public:
	int tempId; // �������е�λ��
	int oldActionId; // ��ǰִ�е���Ϊ
	int oldDir;
	// Ŀǰ֧�� ���� ���� ���� ���� ��· ����
	// ���ȼ� ���� > ���� > ��· > ����  > ���� > ����
	enum{
		ACTION_DEATH= 1 << 0, // ��������
		ACTION_BIRTH = 1 << 1, // ��������
		ACTION_MOVE = 1 << 2, // ��·
		ACTION_ATTACK = 1 << 3, // ����
		ACTION_BE_ATTACK = 1 << 4, // ����
		IDLE_ACTION = 1 << 5, // ����
	};
	enum{
		_DIR_LEFT = 0,
		_DIR_RIGHT = 1,
	};
	bool isDeath();
	void setPosition(const CCPoint& pos);
	bool init();
	static HBMonster* create();
	bool initWithNode(script::tixmlCodeNode *node);
	static HBMonster * createFromNode(script::tixmlCodeNode *node);

	bool initWithInfo(const HBMonsterInfo &info);
	static HBMonster * createFromInfo(const HBMonsterInfo &info);
	/**
	 * ��ʱ��Ϊ �����ӷ�Χ�ڵĵط� ���ߵ����������� ���й���
	 */
	void tick();
	/**
	 * ִ�й���
	 */
	void doAttack();
	CCFiniteTimeAction* v_makeAction(int actionid);
	void v_putAction(CCFiniteTimeAction *action);
	void actionEnd1();
	/**
	 * ���������
	 */
	CCPoint opMoveCenter;
	bool nowMove; // ��ǰ�Ƿ��ڲ����ƶ�
	int opMoveTap; // �ж�ϵ��
	void actionEnd();
	/**
	 * ���Բ��еĴ���һЩ��Ϊ ��ͬ����Ϊ�����д���
	 */
	void conbineActionEnd();
	int nowDir;
	void updateOpMoveCenter(const CCPoint &dest);
	/**
	 * �����ߵ��õ�
	 */
	void onTouch(const CCPoint& point);
	
	/**
	 * TOUCH �����ƶ����·�ʽ
	 */
	enum{
		ON_TOUCH_DOWN,
		ON_TOUCH_MOVE,
		ON_TOUCH_END,
	};
	void onTouch(const CCPoint &point,int moveType);
	CCPoint getStepPointByDir(int dir);
	/**
	 * ����ͼ
	 */
	HBMap *map;
	HBMonsterInfo monsterInfo; // ��������
	CCSprite *sprite;
	CCPoint getStepPointBy(const CCPoint &dest);
	/**
	 * �ͷŹ�������
	 */
	void putAttack(int actionId);
	/**
	 * �������
	 */
	float calcDistance(HBMonster *monster);
	std::vector<int> atktemppoints;
	CCPoint getPkDestination(HBMonster *attaker,int dir);
	
	/**
	 * �Ƿ���cd ʱ����
	 */
	bool checkInCdTime(float cdtime);
	cc_timeval lastAtkTime; // �ϴ���Ϊ��ʱ��
	/**
	 * ����Ѫ��
	 */
	void updateHp(int hp);
	void actionEnd_removeLabel(CCNode*,void*);

	CCPoint calcBeAtkPosition(HBMonster * monster);

	int getReverseDir(int nowDir);
	CCPoint getBackPointByDir(int dir);

	bool checkInXLine(HBMonster *monster);

	void visit();
private:
	HBMonster()
	{
		oldActionId = 0;
		oldDir= 0;
		opMoveTap = 32;
		nowMove = false;
		map = NULL;
		_nowTargetId = -1;
		sprite = NULL;
		lineValue = NULL;
	}
	UIValue *lineValue;
	
	cc_timeval _lastActionTime; // �ϴ���Ϊ��ʱ��
	CCPoint _nowDestination;
	int _nowTargetId;
	
	
	/**
	 * ����ʵ�ʷ���
	 */
	int calcDir(const CCPoint &dest);

	/**
	 * ����ģ�ͷ���
	 */
	int calcMonsterDir(const CCPoint &dest);

	virtual bool moveable(const zPos &tempPos,const zPos &destPos,const int radius1 = 12);
};
NS_CC_END