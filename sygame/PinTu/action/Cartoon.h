#pragma once
#include "cocos2d.h"
NS_CC_BEGIN

/**
 * ������Ϣ
 */
class CartoonInfo:public CCObject{
public:
	/**
	 * ����������Ϣ ����autorelease
	 */
	static CartoonInfo* create(const CartoonInfo &info);
	static CartoonInfo* create();
	/**
	 * ���ݶ���������������
	 * \param parent ������������ʱ ������ʱSprite
	 */
	CCFiniteTimeAction * createAction(CCNode * self,CCNode *parent,const cocos2d::CCPoint &point,CCNode *target);

	int cartoonId; // �����ı��
	std::string cartoonName; // ��������
	enum{
		SELF = 0, // ����
		OTHER = 1, // ����
		FOLLOW = 2, // ���涯��
	};
	int cartoonType;// �������� ���� ���� ����

	enum{
		TIME_FRAMES = 0,
		MOVE_FRAMES = 1,
	};
	int frameType; // ��ʱ��֡ �����ƶ�֡
	
	float needTime; // ����ʱ��
	int actionType; // �������� ���ඨ��
	std::vector<CCSpriteFrame*> frames; // ��ʱ�����ı���	
	int nextConbineType; // ��һ���ϲ�����
	enum{
		SEQUENCE = 0,// ���� 
		TOGETHER = 1, // һ��
	};
	/**
	 * ������һ����������
	 */
	CartoonInfo* addNextCartoonInfo(int nextConbineType,const CartoonInfo& info);
	CartoonInfo* nextCartoon; // ��һ��������Ϣ
	/**
	 * �ͷ�����
	 */
	void release();
	/**
	 * ��������֡
	 */
	CCAnimation * createAnimation();

	CartoonInfo()
	{
		nextConbineType = SEQUENCE;
		cartoonId = -1;
		actionType = -1;
		cartoonType = -1;
		needTime = -1;
		nextCartoon = NULL;
		frameType = MOVE_FRAMES;
	}
	CartoonInfo &operator = (const CartoonInfo &info)
	{
		this->actionType = info.actionType;
		this->cartoonType = info.cartoonType;
		this->nextCartoon = info.nextCartoon;
		this->nextConbineType = info.nextConbineType;
		this->cartoonName = info.cartoonName;
		this->frameType = info.frameType;
		this->frames = info.frames;
		return *this;
	}
};
/**
 * �����ƶ����� �����������Լ����� 
 * ����֡���ƶ������
 */
class CartoonMoveAction:public CCMoveTo{
public:
	
	virtual void update(float time);
	bool isTempTarget;
	CartoonMoveAction()
	{
		isTempTarget = false;
	}

	/**
	 * ��������
	 */
	static CartoonMoveAction* create(const CartoonInfo &cartoonInfo, const CCPoint& position);
	/**
	 * ��ʼ��cartoon �ƶ���Ϊ
	 */
	bool init(const CartoonInfo &cartoonInfo, const CCPoint& position);
	/**
	 * �ͷ��Լ���ռ�е�֡
	 */
	void stop(void);
protected:
	CartoonInfo cartoonInfo;
};
/**
 * �������ƶ����������� 
 */
class CartoonAction:public CCAnimate{
public:
	bool isTempTarget;
	CartoonAction()
	{
		isTempTarget = false;
	}
	virtual void update(float time)
	{
		CCAnimate::update(time);
	}
	/**
	 * ������ͨ����
	 */
	static CartoonAction* create(const CartoonInfo &cartoonInfo);
	/**
	 * ��ʼ������
	 */
	bool init(const CartoonInfo &cartoonInfo);
	/**
	 * �ͷ��Լ���ռ�е�֡
	 */
	void stop(void);
};
/**
 * ����һ�����⶯��
 * ����Ŀ����������� 
 * ��target retain ÿ֡����Ƿ�ֻ�� 1 ����1�� ���� ˵��������ʧ ��¼��Ŀ�겻��
 * �����Ķ������ƶ�������
 */
class CartoonFollowAction:public CCMoveTo{
public:
	 static CartoonFollowAction* create(const CartoonInfo &cartoonInfo,CCNode *target);
	 /**
	 * ����
	 */
	 virtual void update(float t);
	 /**
	 * Ϊʹ������������
	 */
	void stop(void);

	bool initWithAnimation(CCAnimation *pAnimation);

    virtual void startWithTarget(CCNode *pTarget);
	void updateAnimate(float t);
private:
	CCNode *target;
	CartoonInfo cartoonInfo;
	/**
	 * ����Animate������
	 */
	CC_SYNTHESIZE_RETAIN(CCAnimation*, m_pAnimation, Animation)
	std::vector<float>* m_pSplitTimes;
	int                m_nNextFrame;
	CCSpriteFrame*  m_pOrigFrame;
	unsigned int    m_uExecutedLoops;
};
/**
 * ������ ���Բ��Ŷ���
 */
class Cartoon:public CCSprite{
public:
	/** �������ı�
	 * Ŀ��� position
	 * ��̬����Action
	 */
	void runSelfAction(const CartoonInfo &info,const CCPoint &position);

	/**
	 * �����������Ķ��� ָ��Ŀ�ĵ�
	 **/
	void runFlyAction(CCNode* parent,const CartoonInfo &info,const cocos2d::CCPoint &point);
	/**
	 * �������涯��
	 * �����������Ϣ
	 */
	void runFllowAction(CCNode *parent,const CartoonInfo&info,CCNode *target);

	/**
	 * ��϶����Ĳ���
	 * \param parent fly ���ؽڵ�
	 * \param info ������Ϣ
	 * \param point Ŀ�ĵ�
	 * \param target �������
	 */
	void runAction(CCNode *parent,const CartoonInfo*info,const cocos2d::CCPoint &point,CCNode *target);
	/**
	 * ���н�������Ҫ�����ʱ�ڵ�
	 */
	void flyEnd(CCNode *pSender,void *arg);
	/**
	 * ��������
	 */
	void doCartoonEnd();
	/**
	 * ִ����һ��
	 */
	virtual void nextStep() = 0;

	void attachSprite(CCSprite *sprite)
	{
		this->sprite = sprite;
	}
private:
	CCSprite *sprite;
	
public:
	 /**
	  * ��ĳ����ΪΪ��ʼִ��״̬
	  */
	 void start(int id);
	 void tryNextAction(int id);
	 /**
	  * ���е�ִ����Ϊ
	  */
	 void tryConbineAction(int type);
	 int actionType;
	 int oldActionType;
	 Cartoon()
	 {
		actionType = 0;
		oldActionType = -1;
		sprite = NULL;
	 }
	 /**
	  * ��鵱ǰ��Ϊ
	  */
	 bool isNowAction(int actionType);
	 /**
	  * ��һ��������ȥ����ϵ
	  */
	 void clearAction(int type);
	 /**
	  * �������ȼ� ������Ӧ�Ķ���
	  */
	 void putConbineAction();
protected:
	 void setAction(int actionType);
	 virtual CartoonInfo* makeCartoon(int actionType);
	 virtual void putCartoon(CartoonInfo *action);
	 virtual CartoonInfo* v_makeCartoon(int actionType) = 0;
	 virtual void v_putCartoon(CartoonInfo *action) = 0;
};

NS_CC_END