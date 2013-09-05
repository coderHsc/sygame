#pragma once
#include "xmlScript.h"
#include "serialize.h"
#include "RpgPlayer.h"
#include "RpgMap.h"
#include "RpgUI.h"

NS_CC_BEGIN
/**
 * RPG����������
 */
class RpgGuideStep:public serialize::Object{
public:
	int actionId; // ִ�к�
	int delayTime; // ��ʱִ�е�ʱ��
	std::string actionName; // ��Ϊ����
	IMP_SERIALIZE_DATA_FUNC()
	{
		SERIALIZE_DATA(actionId,0);
		SERIALIZE_DATA(delayTime,1);
		SERIALIZE_DATA(actionName,2);
	}
	RpgGuideStep()
	{
		actionId = 0;
		delayTime = 0;
	}
};
class RpgGuide;
typedef void (RpgGuide::*GUIDE_STEP_FUNCTION)(int);
#define BIND_GUIDE_ACTION(functionName) \
	stepNameIds[#functionName] = stepFunctions.size();\
	stepFunctions.push_back(&RpgGuide::functionName);
/**
 * ����ִ��
 */
class RpgGuideStepManager:public serialize::Object{
public:
	std::string stepName;
	int hadLoad; // �Ѿ��������м��ع�?
	std::list<RpgGuideStep> steps; // �����Ĳ���
	RpgGuideStepManager()
	{
		hadLoad = 0;
		nowGuideId = 0;
	}
	int nowGuideId; // �򵼺� CCObject::m_nLuaID ������������ʾ

	void start(RpgGuide *guide,int guideId = 0);

	IMP_SERIALIZE_DATA_FUNC()
	{
		SERIALIZE_DATA(stepName,0);
		SERIALIZE_DATA(hadLoad,1);
		SERIALIZE_DATA(steps,2);
		SERIALIZE_DATA(nowGuideId,3);
	}
};

/**
 * RPG��
 */
class RpgGuide:public script::tixmlCode,public serialize::Object{
public:
	static RpgGuide & getMe()
	{
		static RpgGuide guide;
		return guide;
	}
	/**
	 * ��ʼ��
	 */
	void init(RpgPlayer *player,RpgMap *map,RpgUI *ui);
	/**
	 * ִ����һ������
	 * ִ�б�� �������
	 */
	void doNextStep(unsigned int & stepId,int guideId);
	/**
	 * ����
	 */
	void start(const std::string& stepName);
	/**
	 * �浵
	 */
	void save();
	/**
	 * ���¿�ʼ����
	 */
	void redo(std::string stepName);

	void takeNode(script::tixmlCodeNode *node);
	/**
	 * �����½���������
	 */
	RpgGuideStepManager * findGuide(const std::string &stepName);
	/**
	 * û�л��½���������
	 */
	RpgGuideStepManager * getGuide(const std::string &stepName);
public:
	/**
	 * ����Ϊ
	 */
	void bindActions()
	{
		BIND_GUIDE_ACTION(Guide_step_1);
		BIND_GUIDE_ACTION(Guide_step_2);
		BIND_GUIDE_ACTION(Guide_step_3);
	}
	/**
	 * ϵͳ�����ִ�в���
	 */
	void Guide_step_1(int stepID);
	void Guide_step_2(int stepID);
	void Guide_step_3(int stepID);
	/**
	 * ��ȡ��ǰ����ı��
	 */
	int getIndexByStepName(const std::string& name);
	std::string getStepNameByIndex(int stepId);
	std::vector<GUIDE_STEP_FUNCTION> stepFunctions; // �����Ӧ����Ϊ
	std::map<std::string,int> stepNameIds; // ÿ�����ֶ�Ӧ��ID

	int getGuideActionByName(const std::string& name);
	
	IMP_SERIALIZE_DATA_FUNC()
	{
		SERIALIZE_DATA(_steps,0);
	}
	/**
	 * ִ����Ϊ
	 */
	void doAction(int actionId,int stepId);
	CCSprite * guideSprite;

	void showGuideDir(int dir,const CCPoint &point);

	void setStepTag(CCObject *object,int stepID);
private:
	std::map<std::string,RpgGuideStepManager> _steps;
	std::map<std::string,RpgGuideStepManager> _xmlSteps;
	typedef std::map<std::string,RpgGuideStepManager>::iterator STEPS_ITER;
	RpgPlayer *_player;
	RpgMap *_map;
	RpgUI *_ui;
	RpgGuide()
	{
		_player = NULL;
		_map = NULL;
		_ui = NULL;
		guideSprite = NULL;
	}
};
NS_CC_END
#define theGuide RpgGuide::getMe()