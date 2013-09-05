#pragma once
#include "cocos2d.h"
#include "LineBlockMap.h"
NS_CC_BEGIN
class ActionInLineMap : public CCActionInterval
{
public:
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& position);

    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float time);
	enum{
		MOVE_LEFT, // �����ƶ�
		MOVE_RIGHT, // �����ƶ�
		JUMP_LEFT, // ��������
		JUMP_RIGHT, // ��������
	};
public:
    /** creates the action 
    @deprecated: This interface will be deprecated sooner or later.
    */
    CC_DEPRECATED_ATTRIBUTE static ActionInLineMap* actionWithDuration(float duration, const CCPoint& position);
    /** creates the action */
    static ActionInLineMap* create(float duration, const CCPoint& position);
protected:
    CCPoint m_endPosition;
    CCPoint m_startPosition;
    CCPoint m_delta;
};
NS_CC_END