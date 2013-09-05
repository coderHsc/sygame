#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
#include <map>
NS_CC_BEGIN
/**
 * ֡��Ϣ
 */
class TFFrameInfo{
public:
	int framesId; // ֡���
	std::vector<std::string> pngs; // ͼƬ����
	void getFrames(std::vector<CCSpriteFrame*> &frames);
	CCParticleSystemQuad * particle; // ����ϵͳ
	std::vector<CCSpriteFrame*> frames;
	TFFrameInfo()
	{
		framesId = -1;
		particle = NULL;
	}
};
/**
 * ÿ���������Ϣ
 */
class TFActionInfo{
public:
	int frameType; //֡����
	int actionType; // ��Ϊ����
	int actionId; // ��Ϊid
	float needTime; // ֡�����ʱ��
	int direction; // ����
	int framesId; // ֡��
	int conbineType; // ��һ����������
	int distance; // ���þ���
	int angle; // ��ת�Ƕ�
	CCPoint offset; // ƫ��
	CCPoint anchor; // ê��
	enum{
		FRAME_SELF = 0,
		FRAME_OTHER = 1,
	};
	enum
	{
		ACTION_ORIGIN = 0, // ԭ���ƶ�
		ACTION_FOLLOW = 1, // ����з�
		ACTION_TO = 2, // ��ĳ���㲥�š�
		ACTION_DIR = 3, // ��ĳ�������ƶ�
		ACTION_REVERSE_DIR = 4, // ��ĳ������ �������ƶ�
		ACTION_SPECIAL_ROTATE = 5, // ����Ч�� ������ת
		ACTION_SPECIAL_SCALE = 6, // ����Ч�� ��������
		ACTION_PARTICLE_MOVE = 7, // �ƶ�����
	};
	enum{
		CONBINE_SEQUENCE = 0, // ˳��
		CONBINE_SPAWN = 1, // �ϲ�
	};
	TFActionInfo()
	{
		actionType = FRAME_SELF;
		framesId = -1;
		distance = 0;
		angle = 0;
	}
};
/**
 * һ��ħ����Ϊ3���׶� ��ʼ ���� ���� 
 */
class TFAction{
public:
	std::vector<std::map<int,TFActionInfo> > actions; // ���� 
	typedef std::vector<std::map<int,TFActionInfo> >::iterator ACTIONS_ITER;
	typedef std::map<int,TFActionInfo>::iterator ACTION_INFOS_ITER;
};
struct stLoadProcessCallBack{
	virtual void doLoad(int allCount,int nowIndex) = 0;
};
/**
 * �������ﶯ���ļ���
 */
class TFActionManager:public script::tixmlCode{
public:
	static TFActionManager& getMe()
	{
		static TFActionManager tfm;
		return tfm;
	}
	/**
	 * \param id ����id
	 * \param dir ����
	 * \param dest Ŀ��λ��
	 * \param target Ŀ��
	 * \return ����
	 */
	CCFiniteTimeAction * getAction(int id,int dir,const CCPoint &dest,CCNode *target);
	/**
	 * ���ļ��г�ʼ��
	 */
	void initFromFile(const char *fileName,stLoadProcessCallBack *loadCallback = NULL);
	stLoadProcessCallBack * loadCallback;
private:
	/**
	 * ����������Ϊ
	 */
	CCFiniteTimeAction * createSelfAction(TFActionInfo &actionInfo,const CCPoint &dest);
	/**
	 * ����������Ϊ
	 */
	CCFiniteTimeAction * createFlyAction(TFActionInfo &actionInfo,const CCPoint &dest,CCNode *target);
	std::map<int,TFAction> _actions; // ��Ϊ����
	typedef std::map<int,TFAction>::iterator ACTIONS_ITER;
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);

	std::map<int,TFFrameInfo> frames; // ����֡
	typedef std::map<int,TFFrameInfo>::iterator FRAMES_ITER;

	void loadParticeFromNode(CCParticleSystemQuad * particle,script::tixmlCodeNode &frameNode);

	void loadingCallBack(CCObject *obj);
};

NS_CC_END