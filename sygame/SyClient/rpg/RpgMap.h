/**
 * rpg ��ͼ ���ض��ر� ������� �� ����� ������ �� �ر������pack
 */
#pragma once
#include "cocos2d.h"
#include "RpgBuild.h"
#include "RpgPlayer.h"
#include "RpgMonster.h"
#include "RpgTerrain.h"
#include "xmlScript.h"
NS_CC_BEGIN
class RpgUI;
class RpgMap;
class RpgFollow:public CCFollow{
public:
	static RpgFollow *create(const CCSize & mapSize,CCNode *player);
	virtual void step(float dt);
	CCSize mapSize;
	CCNode *player;
	RpgFollow()
	{
		player = NULL;
	}
};

/**
 * ���ɲ���
 */
class stGenLogic:public CCNode{
public:
	stGenLogic()
	{
		timer = 0;
		maxCount = 0;
		monsterid = 0;
		CCTime::gettimeofdayCocos2d(&lastGenTime, NULL);
	}
	int maxCount;
	int timer;
	std::vector<CCPoint> positions;
	int monsterid;
	cc_timeval lastGenTime;
	CCPoint getRandomPos();
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
};
/**
 * �ִβ���
 */
class stStepLogic:public CCNode{
public:
	bool hadStart;
	cc_timeval startTime;
	int delayTime; // ��ʱ��ʼ�ִ�
	int stepTime; // �ִ�ʱ��
	std::string adContent; // ���ʱ��
	RpgMap *map;
	stStepLogic()
	{
		hadStart = false;
		map = NULL;
		stepTime = delayTime = 0;
		valid = false;
	}
	/**
	 * �������ݼ���
	 */
	std::vector<RpgMonsterData> monsterDatas;
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);

	/**
	 * ����
	 */
	void start();

	/**
	 * ��ʼ��
	 */
	void init(RpgMap *map);

	/**
	 * ������
	 */
	bool isOver();

	/**
	 * ��ʱ��Ϊ
	 */
	void doTick();
	bool valid;
	bool isInvalid(){return !valid;}
	bool isValid(){return valid;}
	void setInvalid(){valid = false;}
};
/**
 * ��������Ļص�
 */
struct stExecEachTarget{
	virtual void exec(RpgObject *object) = 0;
};
/**
 * ��ͼ���赲��չʾ
 */
class MapBlockSprite:public CCNode{
public:
	static MapBlockSprite* create();
	void show(int blockType);
	bool init();
	std::vector<CCSprite*> taps;
};
struct stMonstersYSort{
public:
	int yValue;
	std::list<RpgMonster*> monsters;
	stMonstersYSort()
	{
		yValue = 0;
	}
};

class RpgMap:public CCNode,public script::tixmlCode{
public:
	RpgMap()
	{
		nowMoveBuild = NULL;
		sceneNode = NULL;
		nowSetBlockType = BUILD_CANWALK;
		doTouchType = DO_TOUCH_BUILD;
		infoLog = NULL;
		
		player = NULL;
		ui = NULL;
		score = 0;
		activeSprite = NULL;
		preActiveSprite = NULL;
		barrierSprite = NULL;
	}
	CCSprite *activeSprite;
	CCSprite *preActiveSprite;
	CCSprite *barrierSprite;
    CCRect activeRect;
	int score;
	RpgUI *ui;
	std::string adContent;
	RpgPlayer * player;
	std::string mapName;
	CCNode *  sceneNode;
	std::list<CCNode*> childs;
	typedef std::list<CCNode*>::iterator CHILDS_ITER;
	void addChild(CCNode * child); // ���ӽڵ�
	CCLabelTTF *infoLog;
	void removeChild(CCNode* child, bool cleanup); // ɾ���ڵ�
	/**
	 * ���ļ��м��ص�ͼ
	 */
	static RpgMap* create(const char *mapName,CCNode *parent);
	bool init(const char *mapName,CCNode *parent);
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * ѡ����Ч�Ľڵ���л���
	 */
	virtual void visit();
	/**
	 * ��ȡ��Χ8�������Ƿ�����Ч�� ���ж�����ȡһ��
	 * \param point Ԥ���
	 * \param size ��ռ�ĸ�����
	 * \return ��ǰ��Ч�ĵ�
	 */
	GridPoint getValidGridPoint(const GridPoint &point,const CCSize &size);
	/**
	 * �����Ч��
	 * \param point ���Ե�
	 * \param blockType ������ͨ�������� 
	 */
	GridPoint getValidGridPoint(const GridPoint &point,int blockType);
	/**
	 * ͨ�����ص� ��ȡ�����
	 * \param point ���ص�
	 * \return �����
	 */
	GridPoint getGridPointByPixelPoint(const CCPoint &point);
	/**
	 * ͨ������� ��ȡ���ص�
	 * \param point �����
	 * \return ���ص�
	 */
	CCPoint GetPixelPointByGridPoint(const GridPoint &point);
	/**
	 * ͨ������� ��ȡ����
	 * \param point �����
	 * \return ����
	 */
	int getIndexByGridPoint(const GridPoint &point);
	/**
	 * ���ݱ�Ż�ȡ�����
	 */
	GridPoint getGridPointByIndex(int index);
	/**
	 * ���õ��Ƿ�����ͨ��
	 * \param point ���
	 * \param size ��ǰ�����С
	 * \return �Ƿ���Ч
	 */
	bool checkValid(const CCPoint &point,const CCSize &size);
	/**
	 * ��ȡ��Χ��Ŀ��
	 * \param point ��ǰ��
	 * \param distance ����
	 * \param exec �ص�
	 */
	void execTargets(const GridPoint &point,int distance,stExecEachTarget *exec);

	/**
	 * ���ӹ��� ֻ��һ�����ӵ��赲����
	 */
	void addMonster(RpgMonster *monster);

	/**
	 * ɾ������
	 */
	void removeMonster(RpgMonster *monster);

	/**
	 * ���¹��� ʵ��Ϊ����λ��
	 */
	void updateMonster(RpgMonster *monster);

	void preUpdateMonster(RpgMonster *monster,const GridPoint &nowPoint);
	/**
	 * ���ӹ��� �����ӵ�
	 */
	void addMonsterByGridPoint(RpgMonster *monster,const GridPoint &point);
	/**
	 * ɾ�����ﵽ���ӵ�
	 */
	void removeMonsterByGridPoint(RpgMonster *monster,const GridPoint &point);
	/**
	 * ����λ��
	 */
	void setPosition(const CCPoint& pos);
	/**
	 * ���ӵر� �����Ӹ��ӵ��赲��Ϣ
	 */
	void addTerrain(RpgTerrain *terrain);
	/**
	 * ɾ���ر�
	 */
	void removeTerrain(RpgTerrain *terrain);
	/**
	 * ͨ�������ȡ����
	 */
	RpgMonster *findMonsterByGridPoint(const GridPoint &point);
	
	/**
	 * ��ʱ��Ϊ �ڳ�������Χ ���ɹ���
	 */
	void doTick();

	std::vector<stGenLogic> genLogics; // ���ɲ���
	typedef std::vector<stGenLogic>::iterator GEN_LOGICS_ITER;
	
	std::list<stStepLogic> stepLogics; // �ִβ���
	typedef std::list<stStepLogic>::iterator STEP_LOGICS_ITER;
	stStepLogic nowStep; // ��ǰ����

	int getMonsterCount();

	RpgMonster *pickMonster(const CCPoint& touchPoint);
public:
	/**
	 * ���ļ��м����赲����Ϣ 
	 */
	void loadBlock(const char *blockFile);
	/**
	 * ����Ϣ���浽�ļ���
	 */
	void saveBlock(const char *blockFile);
	/**
	 * ������Ϣ
	 */
	enum{
		NULL_BLOCK = 0, // û���赲
		TERRAIN_BLOCK = 1 << 0, // ���赲 
		TERRAIN_CANWALK = 1 << 1, // �ؿ�ͨ
		BUILD_BLOCK = 1 << 2, // �������赲
		BUILD_CANWALK = 1 << 3, // �������ͨ
		PLAYER_BLOCK = 1 << 4, // �����赲
		MONSTER_BLOCK = 1 << 5, // �����赲
	};
	std::vector<unsigned char> blocks; // �ر���Ϣ
	std::vector<MapBlockSprite*> mapblockSprites; // �ر��赲����Ϣչʾ
	/**
	 * �����赲��
	 */
	void setBlock(int index,int blockType);
	/**
	 * ����赲��
	 */
	void clearBlock(int index,int blockType);
	/**
	 * ����赲��
	 */
	bool checkBlock(int index,int blockType);
	std::list<RpgTerrain*> terrains; // �ر���
	typedef std::list<RpgTerrain*>::iterator TERRAINS_ITER;


	std::vector<std::vector<RpgMonster*> > monsters; // ����
	typedef std::vector<std::vector<RpgMonster*> >::reverse_iterator MONSTERS_MAP_ITER;
	typedef std::vector<RpgMonster*>::iterator MONSTERS_ITER;
	
	std::list< stMonstersYSort > newMonsters; // �µĹ��������
	typedef std::list<stMonstersYSort >::reverse_iterator NEW_MONSTERS_MAP_ITER;
	typedef std::list<RpgMonster*>::iterator NEW_MONSTERS_ITER;
	CCSize mapSize; // ��ͼ��С
	CCSize canBlockSize; // ����ͨ���Ĵ�С
	CCSize gridSize; // ÿ�����Ӵ�С
	/**
	 * ������ص� �Ƿ��ڵ�ͼ��
	 */
	bool checkInMap(const CCPoint& pixelPoint);
	/**
	 * ������ص� �Ƿ����赲����
	 * \param blockType �赲������
	 * \param pixelPoint ���ص� ����ڵ�ǰ��
	 */
	bool checkInBlock(const CCPoint& pixelPoint,int blockType);

	/**
	 * չʾ�赲��
	 */
	void showMapBlocks();

	/**
	 * �����Ƿ��ǿ��Թ����ĵ�
	 */
	bool checkValidAtkPoint(const GridPoint &src,const GridPoint &point);
	/**
	 * ��ȡ��Ч�Ĺ�����
	 */
	GridPoint getValidAtkPoint(const GridPoint &point);
public:
///////////////////////////////// �������� ��Farm//////////////////////////////////
	/**
	 * �����Ƿ��ܹ����ý�����
	 * \param build ������
	 * \param gx ���Ӻ�id
	 * \param gy ������id
	 * \return �Ƿ��ܹ�����
	 */
	bool canPlaceBuild(RpgBuild * build,int gx,int gy);
	/**
	 * ���ý�����
	 * \param build ������
	 * \param gx ���Ӻ� id
	 * \param gy ������ id
	 * \return �Ƿ���óɹ�
	 */
	bool placeBuild(RpgBuild *build,int gx,int gy);
	/**
	 * ����index �Ƿ��ڽ�����������
	 */
	bool checkIndexInBuild(RpgBuild *build,int gx,int gy);
	/**
	 * ���ҽ�����
	 * \param tx touch������
	 * \param ty touch������
	 * \return ������ָ�� 
	 */
	RpgBuild *pickBuild(float tx,float ty);
	RpgBuild *pickBuild(const GridPoint &point);
	/**
	 * ��ȡ����ֵ
	 */
	int getIndex(int gx,int gy);
	/**
	 * ���ӽ�����
	 */
	void addBuild(RpgBuild *build);
	/**
	 * ɾ��������
	 */
	void removeBuild(RpgBuild *build);
	/**
	 * ��ȡȫ�ֵĵ�
	 */
	CCPoint getPixelPoint(int gx,int gy);
	/**
	 * ����赲��
	 */
	void clearBlock(const RpgBuildInfo &build);
	/**
	 * �����赲��
	 */
	void setBlock(const RpgBuildInfo &build,int buildId);
	
	/**
	 * ������
	 */
	bool doTouch(int touchType,const CCPoint&touchPoint);

	enum{
		DO_TOUCH_BUILD, // ������
		DO_TOUCH_MOVE, // �ƶ�
		DO_TOUCH_SET, // ����
	};
	int doTouchType;
	/**
	 * ����touch ĿǰҲ�ʹ������﷽��
	 */
	bool doTouchPlace(int touchType,const CCPoint&touchPoint );

	void doTouchBuild(RpgBuild *build);
	CCPoint nowTouchPoint; // ��ǰtouch��
	/**
	 * ���Ƶ�ͼ���ƶ�
	 */
	bool doTouchMove(int touchType,const CCPoint &touchPoint);
	/**
	 * ����趨��ͼ���赲����Ϣ
	 */
	int nowSetBlockType; // ��ǰӦ�����õ��赲������
	bool doTouchSet(int touchType,const CCPoint &touchPoint);

	RpgBuild *nowMoveBuild;
	std::map<int,RpgBuildInfo> buildInfos;
	typedef std::map<int,RpgBuildInfo>::iterator BUILD_INFOS_ITER;
	RpgBuildInfo findFarmInfoById(int id);

	void showBlocks();
	void actionEnd_removeTemp(CCNode *pSender,void *arg);
	bool checkCollide(RpgMonster *monster,const GridPoint &point);
private:
	std::vector<int> _grids; // ��ͼ�ϵĸ�����
	std::vector<CCSprite*> _gridSprites; // ��ͼ�ϵĸ�����
	std::vector<RpgBuild*> _builds; // �����Ｏ�� �ǲ����ཻ��
	typedef std::vector<RpgBuild*>::iterator BUILDS_ITER;
	typedef std::vector<int>::iterator GRIDS_ITER;
/////////////////////// �������� ��Farm ����//////////////////////////////////
};

NS_CC_END
