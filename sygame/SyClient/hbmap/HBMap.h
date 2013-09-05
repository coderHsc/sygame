#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
#include "Astar.h"
#include "HBMonster.h"
#include <map>
#include "UINumber.h"
NS_CC_BEGIN

class HBSky;
class HBMap;
class HBFollow:public CCFollow{
public:
	static HBFollow *create(HBSky * sky,CCNode *player);
	virtual void step(float dt);
	HBSky *sky;
	CCNode *player;
	HBFollow()
	{
		sky = NULL;
		player = NULL;
	}
};

class MonsterGenLogic{
public:
	int genTapTime;
	cc_timeval lastGenTime;
	int genCount;
	std::map<int,CCPoint> monsters;
	bool checkGenNow();
	typedef std::map<int,CCPoint>::iterator MONSTERS_ITER;
	void initWithNode(script::tixmlCodeNode *node);
	MonsterGenLogic();
};
/**
 * �ṩ���� ��ͼ �� ����� ����㰴y������
 */
class HBMap:public CCLayer,public script::tixmlCode{
public:
	cc_timeval gameStartTime;
	enum{
		MAP_LAYER_BACK,
		MAP_LAYER_OBJECT,
	};
	/**
	 * �������ļ��м��ص�ͼ��Ϣ
	 * ��Ҫ�Ǽ���Monster��Ϣ
	 */
	static HBMap * createFromXml(const char *fileName);

	bool initFromXml(const char *fileName);
	/**
	 * ���ҹ�����
	 */
	bool findEneries(HBMonster *monster,int eyeshort,std::vector<HBMonster*> &monsters);
	/**
	 * ͨ��id ��ȡmonster
	 */
	HBMonster * getEneryByID(int id);
	/**
	 * ��ʱ��Ϊ
	 */
	void tick();
	CCSprite * jianTou;
	CCSprite *opmove;
	void drawNowPoint(const CCPoint &src,const CCPoint &point);
	void showMissed(const CCPoint &point);
	/**
	 * ���Ʒ���
	 */
	void drawDir(int dir);
	void onTouch(const CCPoint &dest,int touchType);
	void setPosition(const CCPoint& pos);
	HBMap()
	{
		_player = NULL;
		_needSort = false;
		sky = NULL;
		jianTou = NULL;
		opmove = NULL;
		back = NULL;
		mapWidth = 0;
		mapHeight = 0;
		over = false;
		tickLbl = NULL;
		tickCount = 0;
		isEditBlock = true;
	}
	UINumber *tickLbl;
	int tickCount;
	void addMonster(HBMonster *monster);
	/**
	 * ��Ҫ���� ԭ��������������Ƿ� �������� ������������λ�÷����仯ʱ �͵���
	 */
	void setReSort(){_needSort = true;}
	HBSky *sky; // ���
	HBMonster *_player; // ����
	bool over;
	/**
	 * ����Ƿ��ڵ�ͼ��
	 * \param x ������
	 * \param y ������
	 * \return true �ڵ�ͼ�� false ���ڵ�ͼ��
	 */
	bool checkInMap(float x,float y);
	CCNode * back;
	float mapWidth;
	float mapHeight;
	float gridWidth;
	float gridHeight;
	void setBlock(float x,float y);
	bool checkBlock(float x,float y);
	void clearBlock(float x,float y);
	int getIndex(float x,float y);
	zPos getGridPoint(float x,float y);
	CCPoint getPointByGrid(const zPos& pos);

	bool isEditBlock; // �Ƿ��ڱ༭�赲��ģʽ
private:
	std::vector<unsigned char > blocks;
	std::vector<CCSprite*> blockDebugInfos;
	std::vector<HBMonster*> _monsters; // �����ϵĹ���
	typedef std::vector<HBMonster*>::iterator MONSTERS_ITER;

	std::vector<MonsterGenLogic> genLogics;
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * �����������
	 */
	virtual void sortAllChildren();
private:
	bool _needSort;
	std::map<int,HBMonsterInfo> monsterInfos;
	typedef std::map<int,HBMonsterInfo>::iterator MONSTERINFOS_ITER;

	int monsterCount();
};
NS_CC_END