#pragma once
/**
 * RPG��Ϸ�����
 */
#include "cocos2d.h"
#include "RpgMap.h"
#include "RpgUI.h"
#include "RpgPlayer.h"

NS_CC_BEGIN

class RpgGame : public cocos2d::CCLayer{
public:
    virtual bool init();  
	virtual bool init(const char *sceneName);
    static cocos2d::CCScene* scene();
	static cocos2d::CCScene * scene(const char *sceneName);
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouch, cocos2d::CCEvent *pEvent);

	CREATE_FUNC(RpgGame);
	// �趨��ͼ
	RpgMap *map;
	// �趨UI
	RpgUI *ui;
	// �趨����
	RpgPlayer * player;

	RpgGame()
	{
		map = NULL;
		ui = NULL;
		player = NULL;
		canMove = false;
	}
	void step(float dt);
	bool canMove;
};

NS_CC_END