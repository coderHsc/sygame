#pragma once
#include "cocos2d.h"
#include "Cartoon.h"
#include "quickidmanager.h"
NS_CC_BEGIN
/**
 * ���ӵ�
 */
class GridPoint{
public:
	int x;
	int y;
	GridPoint()
	{
		x = y = 0;
	}
	GridPoint(int x,int y)
	{
		this->x = x;
		this->y = y;
	}
	GridPoint & operator=(const GridPoint &point)
	{
		this->x = point.x;
		this->y = point.y;
		return *this;
	}
	bool isInvalid() const
	{
		return (x == -1 || y == -1);
	}
	bool equal(const GridPoint &point)
	{
		return (x == point.x && y == point.y);
	}
	bool equal(const GridPoint &point,int range)
	{
		return (abs(x - point.x) < range && abs(y - point.y) < range);
	}
};
/**
 * rpg ����
 */
class RpgObject:public Cartoon,public QuickObjectBase{
public:
	int objectType; // ��������
	int quickId; //����������
	enum{
		RPG_BUILD = 0, // ������
		RPG_MONSTER = 1, // ����
		RPG_PLAYER = 2, // ���
	};
	RpgObject(int objectType):objectType(objectType)
	{
		
	}
	virtual void nextStep(){}
	virtual CCFiniteTimeAction* v_makeAction(int actionType)
	{
		return NULL;
	}

	virtual void v_putAction(CCFiniteTimeAction *action){}
	/**
	 * ���ÿ���Ψһ����
	 * \param uniqueQuickId ���ÿ���Ψһ����
	 */
	virtual void setUniqueQuickId(int uniqueQuickId)
	{
		this->quickId = uniqueQuickId;
	}
	/**
	 * ��ȡ����Ψһ����
	 * \return ����Ψһ����
	 */
	virtual int getUniqueQuickId() 
	{
		return quickId;
	}
	bool isType(int type)
	{
		return objectType == type;
	}
};

class RpgObjectManager:public QuickIdManager{
public:
	/**
	 * ����ģʽ 
	 * ��ȡRpg���������
	 */
	static RpgObjectManager & getMe(){static RpgObjectManager rom; return rom;}
};

#define theObjectM RpgObjectManager::getMe()
NS_CC_END