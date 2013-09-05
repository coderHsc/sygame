
#pragma once
#include "cocos2d.h"
#include "ModelLoader.h"
#include "AnimateMoveAction.h"
NS_CC_BEGIN
/**
 * ���ܵ��Ӷ���
 * ������ , Action ��չʾ
 * ����ض���
 */
class SkillAction:public AnimateMoveAction{
public:
	 static SkillAction* create(float duration, const CCPoint& position,const std::vector<CCSpriteFrame*> &frames,CCParticleSystemQuad *actionParticle = NULL);
	 static SkillAction* create(float duration,const CCPoint &src, const CCPoint& position,const std::vector<CCSpriteFrame*> &frames,CCParticleSystemQuad *actionParticle = NULL);
	 static SkillAction* create(float duration,const std::vector<CCSpriteFrame*> &frames);
	 static SkillAction* create(float duration,const std::vector<CCSpriteFrame*> &frames,CCNode *target);
	/**
	 * ����
	 */
	 virtual void update(float t);
	 /**
	  * ����
	  */
	 virtual void startWithTarget(CCNode *pTarget);
protected:
	bool hadFrom;
	bool hadEnd;
	// �½�һ��CCSprite �������ض���
	CCSprite *actionSprite;
	CCParticleSystemQuad *actionParticle; // ���������ϵͳ
	CCNode *target;
	/**
	 * Ϊʹ������������
	 */
	void stop(void);
	
	SkillAction()
	{
		actionSprite = NULL;
		actionParticle = NULL;
		hadFrom = false;
		hadEnd = true;
		target = NULL;
	}
	
};
/**
 * ���� Я������ϵͳ���ƶ� 
 */
class SkillParticleAction:public CCMoveTo{
public:
	virtual void update(float time);
	static SkillParticleAction* create(CCParticleSystemQuad *actionParticle,float duration, const CCPoint& dest);
	static SkillParticleAction* create(CCParticleSystemQuad *actionParticle,float duration, const CCPoint& src,const CCPoint &dest);
	void startWithTarget(CCNode *pTarget);
	void stop(void);
protected:
	CCParticleSystemQuad *actionParticle;
	bool hadFrom;
	SkillParticleAction()
	{
		hadFrom = false;
		actionParticle = NULL;
	}
};
/**
 * ��ĳ�������ƶ��ļ���
 */
class SkillMoveAction:public SkillAction{
public:
	static SkillMoveAction* create(float duration, const CCPoint& position,const std::vector<CCSpriteFrame*> &frames,float distance,int moveType);
	enum{
		TO_DIR, // ��������
		TO_REVERSE_DIR, // �򷴷���
	};
	 /**
	  * ����
	  */
	 void startWithTarget(CCNode *pTarget);
private:
	float _distance;
	float _dirType;
	SkillMoveAction()
	{
		_distance = 0;
		_dirType = 0;
	}
};
/**
 * ��ĳ��������ת ����ָ��anchorPoint
 */
class SkillRotateBy:public CCRotateBy{
public:
	 static SkillRotateBy* create(float duration, float fDeltaAngle,const CCPoint& newAnchorPoint,const CCPoint &offsetPoint);
	 void startWithTarget(CCNode *pTarget);
	 virtual void update(float time);
	 void stop(void);
private:
	CCPoint oldAnchorPoint;
	CCPoint nowPoint;
};
/**
 * ����������
 * ����ָ�� anchor �� ����ƫ��
 */
class SkillScaleTo:public CCScaleTo{
public:
	 static SkillScaleTo* create(float duration, float scale,const CCPoint& newAnchorPoint,const CCPoint &offsetPoint);
	 void startWithTarget(CCNode *pTarget);
	 virtual void update(float time);
	 void stop(void);
private:
	CCPoint oldAnchorPoint;
	CCPoint nowPoint;
};
NS_CC_END