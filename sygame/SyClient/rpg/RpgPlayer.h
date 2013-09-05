/**
 * ���ƶ��� �����ƶ� ����ָ�ĵ���
 * ���ƶ�ʱ���������λ��
 */

#pragma once
#include "cocos2d.h"
#include "RpgMonster.h"
#include "CalcDir.h"
NS_CC_BEGIN
class RpgMap;
class RpgBuild;
class RpgMinMapUI;
class RpgUI;
class RpgBuild;
class RpgSkillData{
public:
	int atkMinDistance; // ��С��������
	int atkMaxDistance; // ��󹥻�����
	int atkMaxValue; // ��󹥻�ֵ
	int atkMinValue; // ��С����ֵ
	int atkMaxNum; // ��󹥻�����
	int atkMinNum; // ��С��������
	RpgSkillData()
	{
		atkMinDistance = atkMaxDistance = atkMaxValue = atkMinValue = atkMaxNum = atkMinNum = 0;
	}
	int getAtkDistance();
	int getAtkValue();
	int getAtkNum();
};
class RpgPlayer:public RpgMonster{
public:
    enum{
		MOVE_SPEED_UP,
	};
	RpgPlayer()
	{
		continueMoveDir = CalcDir::_DIR_NULL;
		objectType = RpgObject::RPG_PLAYER;
		miniMap = NULL;
		ui = NULL;
		this->monsterData.step = 96;
		inBuild = false;
		speedTime = 0.6f;
	}
	/**
	 * ͨ����ͼ�������
	 */
	static RpgPlayer * create(RpgMap *map);

	bool init(RpgMap *map);
	virtual void v_putCartoon(CartoonInfo *action);
	virtual CartoonInfo* v_makeCartoon(int actionType);
	void putAtkSkill(const std::string& skillname,const RpgSkillData &skillData); 
	void visit();
	void beAttacked(int atkValue);
	/**
	 * ÿһ�������� �����Ƿ���ʵ���npc ���Զ������������չʾ
	 */
	virtual void nextStep();
	/**
	 * ϵͳ�еĽ�������
	 */
	int visitBuildID;
	RpgBuild *visitBuild;
	float speedTime; // �ٶ�
	/**
	 * ϵͳ�е�Monster��� ��ǰ�ƶ������ѡ�е�Monster �����������
	 */
	GridPoint monsterPoint;
	RpgMonster *nowMonster; // ��ǰѡ����Monster 
	RpgMinMapUI *miniMap; // С��ͼ
	RpgUI *ui; // ������
	/**
	 * �ƶ�
	 */
	virtual void setPosition(const CCPoint& point);

	void doVisitBuild(RpgBuild *build);
	bool inBuild;
	void doAttack(RpgMonster *monster);
public:
	// ��ش��̵���Ϣ
public:
	// �����ƶ�����Ϣ
	void doContinueMove(int nowDir);
	void clearContinueMove();
	bool isContinueMove(int nowDir);
	int continueMoveDir;
};

NS_CC_END