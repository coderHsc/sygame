/**
 * ��ɫ �ĸ��ֶ��� �� ��Ч���� �̳�Cartoon 
 */

#pragma once
#include "cocos2d.h"
#include "RpgObject.h"
#include "Cartoon.h"
#include "xmlScript.h"
#include "Astar.h"
NS_CC_BEGIN
class RpgMap;
class RpgHpValueUI;// Ѫ����
class RpgDirAction{
public:
	std::string FramesName; // ֡����
	std::string frameLoadType; // ֡��������
	std::vector<std::string> frames;
	RpgDirAction()
	{
		
	}
	/**
	 * ��ȡ��֡
	 */
	bool getFrames(std::vector<CCSpriteFrame *> &frames);
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
};

class RpgAction{
public:
	std::string actionName; // ��������
	int actionType; // ��������
	float needTime; // ��Ҫʱ��
	int frameType; // ֡���� ʱ�� �����ƶ�����
	int cartoonType; // �������� [SELF,OTHER]
	std::map<int,RpgDirAction> dirActions;
	typedef std::map<int,RpgDirAction>::iterator DIRACTIONS_ITER;
	/**
	 * ��ȡ֡����
	 * \param frames ֡���� 
	 */
	bool getFrames(int dir,std::vector<CCSpriteFrame *> &frames);
	RpgAction()
	{
		actionType = 0;
		needTime = 0;
		cartoonType = 0;
		frameType = 0;
	}
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
};
/**
 * ���ȭ
 */
class RpgConbineAction:public RpgAction{
public:
	int nextType; // ��һ������
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * ��������
	 */
	CartoonInfo* getCartoonInfo(int dir);
};
/**
 * Monster ����������
 */
class RpgMonsterData{
public:
	int id; // ���
	std::string monsterName; // �Լ������� Ŀǰ�Ƕ�������
	int step; // ��ǰ�Ĳ���
	int eyeshort; // �Լ�����Ұ
	int maxAtkDistance; // ��󹥻�����
	int liveTime; // ����ʱ��
	int reliveTapTime; // ������ʱ��
	int reliveCount; // ����Ĵ��� -1 ��ʶ����
	int maxAtkValue; // ��󹥻���
	int minAtkValue; // ��С������
	int maxHp; // ���Ѫ��ֵ
	int xmlX;
	int xmlY;
	int actionId; // ��Ϊ���
	int walkPathId; // ·����
	int activeRectId; // ������
	RpgMonsterData()
	{
		actionId = 4;
	}
	void takeNode(script::tixmlCodeNode *node)
	{
		if (node)
		{
			node->getAttr("rectid",activeRectId);
			node->getAttr("pathid",walkPathId);
			node->getAttr("monstername",this->monsterName);
			node->getAttr("step",this->step);
			node->getAttr("eyeshort",this->eyeshort);
			node->getAttr("livetime",this->liveTime);
			node->getAttr("maxatkdistance",this->maxAtkDistance);
			node->getAttr("maxatkvalue",this->maxAtkValue);
			node->getAttr("minatkvalue",this->minAtkValue);
			node->getAttr("maxhp",this->maxHp);
			node->getAttr("x",this->xmlX);
			node->getAttr("y",this->xmlY);
			node->getAttr("actionid",this->actionId);
			node->getAttr("id",this->id);
		}
	}
};
struct stOpTime{
	cc_timeval opTime;
	int lastTime;
	stOpTime()
	{
		lastTime = 0;
	}
};
class RpgMonster:public RpgObject,public zAStar<>{
public:
    int faceDir;
	CCRect activeRect; // ���ƵĻ��Χ
	std::vector<CCPoint> path; // ·��
	int dir; // ��ǰ����
	int hp; // ��ǰѪ��
	RpgHpValueUI *hpShow;
	//std::string monsterName; // �Լ������� Ŀǰ�Ƕ�������
	//int step; // ��ǰ�Ĳ���
	//int eyeshort; // �Լ�����Ұ
	//int maxAtkDistance; // ��󹥻�����
	RpgMonsterData monsterData;
	RpgMonster():RpgObject(RPG_MONSTER)
	{
		dir = 0;
		monsterData.step = 32;
		monsterData.eyeshort = 32;
		nowTarget = NULL;
		quickTargetId = -1;
		faceDir = -1;
		monsterData.maxAtkDistance = 3;
		nowDestination = GridPoint(-1,-1);
		deathTag = false;
		CCTime::gettimeofdayCocos2d(&birthTime, NULL);
		hpShow = NULL;
	}
	~RpgMonster()
	{
		rpgSprite = NULL;
		hpShow = NULL;
	}
	CCSprite* rpgSprite;
	cc_timeval birthTime;
	bool isReachDestination();
	/**
	 * ��������
	 */
	static RpgMonster * create(int id);
	bool init(int id);
	enum{ // Խ�������ȼ�Խ�� �����Ǳ���¼ �����ǲ���ͬʱ������
		ACTION_DEATH= 1 << 0, // ��������
		ACTION_BIRTH = 1 << 1, // ��������
		ACTION_ATTACK = 1 << 2, // ����
		ACTION_MOVE = 1 << 3, // ��·
		ACTION_BE_ATTACK = 1 << 4, // ����
		IDLE_ACTION = 1 << 5, // ����
	};
	void showHp();
	virtual void beAttacked(int atkValue);
	void actionEnd_removeLabel(CCNode *pSender,void *arg);
	void tryMove();
	void setDir(int dirType);
	/**
	 * ��ȡ������Ϣ
	 * \param actionName ��������
	 * \param dir ��������
	 * \param info ������Ϣ
	 */
	bool getCartoonInfo(const std::string& actionName,int dir, CartoonInfo &info);

	std::map<std::string,RpgAction> actions; // ����
	typedef std::map<std::string,RpgAction> ACTIONS;
	typedef ACTIONS::iterator ACTIONS_ITER;
// ���������ʵ��
	/**
	 *  TODO ���õ�ǰ�ĸ���
	 *  TODO �ж��Ƿ���Ҫֹͣ��·
	 *  TODO �ж��Ƿ���Ҫ���������¼�
	 *  TODO ���ﶯ�������� ˼����һ����Ϊ ����ƶ� ���� ������
	 */
	virtual void nextStep();
	virtual CartoonInfo* v_makeCartoon(int actionType);
	virtual void v_putCartoon(CartoonInfo *action);
// �������ʵ�ֽ���
	// ʹ�ü���
	std::list<std::string> useatkskills; // ʹ�õĹ�������
	virtual void putAtkSkill(const std::string& skillname); 
	std::string nowSkillName;// ��ǰ��������
	bool isSkill(const std::string& skillName){return nowSkillName == skillName;}
	// ������صĽ���

	/*
	 *���ݷ��� ��ȡ��һ�����ƶ���
	 */
	CCPoint getPixelPositionByDir(int dir);

	// ����Ұ��Χ��Ѱ�Ҷ��� ���Ҳ鿴�Ƿ���Թ��� �ܹ����򹥻� �����߽�
	void doAttack();
	RpgObject * nowTarget;
	int quickTargetId; // ��ǰ�Ŀ���������
	RpgMap * getMap()
	{
		return (RpgMap*)(this->getParent());
	}
	GridPoint getGridPoint();
	/**
	 * ��ȡʵ�ʸ���
	 */
	GridPoint getNowGridPoint();
	/**
	 * �������
	 * \param point Ŀ�ĵ�
	 */
	unsigned int calcDistance(const GridPoint &point);
	
	/**
	 * ��ȡһ������Ч�ĵ�
	 */
	GridPoint getValidCirclePoint();

	GridPoint getRandomPoint(const CCSize &rect);
	/**
	 * ��ȡ��Ч�Ĺ�����
	 */
	GridPoint getValidAtkPoint();
	/**
	 * �����Ƿ��ǿ��Թ����ĵ�
	 */
	bool checkValidAtkPoint(const GridPoint &point);
	GridPoint nowDestination; //��ǰĿ��� 
	GridPoint oldGridPoint; // ��һ�εĸ��ӵ�
	virtual bool moveable(const zPos &tempPos,const zPos &destPos,const int radius1 = 12);

	// �Ƿ�����
	bool deathTag; 
	bool isDeath(){return deathTag;}

	void doDeath(); // ����Լ��Ƿ��Ѿ�����
	void visit();

	void dropItems();
	bool checkIn(const GridPoint &point,int tag = 1);
	
	/**
	 * ����Ƿ��Ƿ�ʱ
	 */
	bool checkTimeOut(int opId);
	/**
	 * ����Ƿ���ʱ����
	 */
	bool checkInTime(int opId);
	/**
	 * ���Ӹ�ʱ��
	 */
	void addTime(int opId,int lastTime);
	/**
	 * ����ʱ�伯��
	 **/
	std::map<int,stOpTime> optimes;
	typedef std::map<int,stOpTime>::iterator OPTIMES_ITER;
};
/**
 * �������
 */
class MonsterManager:public script::tixmlCode{
public:
	static MonsterManager & getMe();
	/**
	 * ��������
	 */
	void loadConfig();
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * ��ȡ��������
	 */
	bool getActionByName(const char *actionName,RpgMonster::ACTIONS &actionmap);
	/**
	 * ϵͳ�еĶ���
	 */
	std::map<std::string,RpgMonster::ACTIONS> actionmaps;
	typedef std::map<std::string,RpgMonster::ACTIONS>::iterator ACTIONMAPS_ITER; 

	/**
	 * ϵͳ�е����ȭ����
	 */
	typedef std::vector<RpgConbineAction> COBINE_ACTIONS;
	std::map<std::string,COBINE_ACTIONS > conbineactionmaps;
	typedef std::map<std::string,COBINE_ACTIONS>::iterator CONBINEACTIONMAPS_ITER; 
	std::map<int,RpgMonsterData> monsterDatas;
	typedef std::map<int,RpgMonsterData>::iterator MONSTERDATAS_ITER;

	/**
	 * ��ȡ����
	 */
	CartoonInfo * getCobineCartoon(const char *actionName,int dir);

	bool initMonsterData(int id,RpgMonsterData &data);

	bool initMonseterPath(int pathId,std::vector<CCPoint> &path);
	std::map<int ,std::vector<CCPoint> > paths;
	typedef std::map<int,std::vector<CCPoint> >::iterator PATHS_ITER;

	bool initMonsterRect(int rectId,CCRect &rect);
	std::map<int,CCRect> activeRects; // ϵͳ���޶��Ļ����
	typedef std::map<int,CCRect>::iterator ACTIVE_RECTS_ITER;
};
typedef void (*ACTION_EXT) (RpgMonster *monster);
class MonsterActionTable{
public:
	MonsterActionTable()
	{
		init();
	}
	static std::vector<ACTION_EXT> functions;
	void init()
	{
		functions.push_back(&MonsterActionTable::doAttackAndWalk);
		functions.push_back(&MonsterActionTable::doOnlyAttack);
		functions.push_back(&MonsterActionTable::doOnlyMove);
		functions.push_back(&MonsterActionTable::doStop);
		functions.push_back(&MonsterActionTable::doAttackPlayerFirstOnlyOneTarget);
		functions.push_back(&MonsterActionTable::doMovePathAndAttack);
	}
	static MonsterActionTable & getMe()
	{
		static MonsterActionTable mat;
		return mat;
	}
	static void doAction(int id,RpgMonster *monster);
	static void doAttackAndWalk(RpgMonster *monster);
	static void doOnlyAttack(RpgMonster *monster);
	static void doOnlyMove(RpgMonster *monster);
	static void doStop(RpgMonster *monster);
	/**
	 *  ������������ ͬʱֻ����һ��Ŀ�� �����Эͬ��ս
	 */
	static void doAttackPlayerFirstOnlyOneTarget(RpgMonster *monster);

	/**
	 * ���żȶ�·������ �������������ڸ���ʱ���� ���ƶ�
	 */
	static void doMovePathAndAttack(RpgMonster *monster);
    
    static void doAttackMutiTargetDefaultWalkInPath(RpgMonster *monster);
};

#define theActionLib MonsterActionTable::getMe()
NS_CC_END