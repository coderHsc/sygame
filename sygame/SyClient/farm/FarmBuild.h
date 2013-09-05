#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
NS_CC_BEGIN
class FarmMap;
class FarmBuildInfo{
public:
	/**
	 * ���Ӻ�����
	 */
	int gridX;
	/**
	 * ����������
	 */
	int gridY;
	/**
	 * ���������
	 */
	int gridWidth;
	/**
	 * ���������
	 */
	int gridHeight;

	bool initWithNode(script::tixmlCodeNode * node);
	/**
	 * ���
	 */
	int id ;
	/**
	 * ����������
	 */
	std::string buildName;
	FarmBuildInfo()
	{
		id = -1;
		gridWidth = gridHeight = -1;
		gridX = gridY = -1;
	}
	FarmBuildInfo & operator = (const FarmBuildInfo &info)
	{
		gridX = info.gridX;
		gridY = info.gridY;
		gridWidth = info.gridWidth;
		gridHeight = info.gridHeight;
		id = info.id;
		buildName = info.buildName;
		return *this;
	}
};
/**
 * ũ��������
 */
class FarmBuild:public CCNode{
public:
	/**
	 * ����λ��
	 */
	void setPosition(float px,float py);
	/**
	 * �����Ƿ��ڽ�����
	 **/
	bool checkIn(float tx,float ty);
	FarmBuildInfo info;
	/**
	 * �ӽڵ��д���������
	 */
	static FarmBuild * createFromNode(script::tixmlCodeNode * node);
	bool initWithNode(script::tixmlCodeNode * node);
	/**
	 * ����һ��Build
	 */
	static FarmBuild *createFromBuild(FarmBuildInfo *buildInfo);
	bool initWithBuild(FarmBuildInfo *buildInfo);
	int actionId; // ��ǰ����Ϊ

	CCSprite *buildSprite;
	FarmMap *map;
	std::vector<CCSprite*> gridBacks;
	void showInvalidGridBack();
	void showValidGridBack();
	void drawGrid();
	FarmBuild()
	{
		buildSprite = NULL;
		actionId = -1;
		map = NULL;
		uniqueId = 0;
	}
	int uniqueId;

	void preSetPosition(float px,float py);
};

NS_CC_END