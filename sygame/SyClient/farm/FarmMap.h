/**
 * ũ���ĵ�ͼ �����ڵ�ͼ�Ϸ����κε�����
 */
#pragma once
#include "cocos2d.h"
#include "xmlScript.h"
#include "FarmBuild.h"
NS_CC_BEGIN

/**
 * ���ý����������� 
 */
class FarmMap:public CCNode,public script::tixmlCode{
public:
	/**
	 * ���ļ��д��� ��ͼ
	 */
	static FarmMap* createFromFile(const  char *fileName);
	/**
	 * ���ļ��г�ʼ��
	 * \param fileName �ļ�����
	 */
	bool initFromFile(const char *fileName);
	/**
	 * ����ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
	/**
	 * �����Ƿ��ܹ����ý�����
	 * \param build ������
	 * \param gx ���Ӻ�id
	 * \param gy ������id
	 * \return �Ƿ��ܹ�����
	 */
	bool canPlaceBuild(FarmBuild * build,int gx,int gy);
	/**
	 * ���ý�����
	 * \param build ������
	 * \param gx ���Ӻ� id
	 * \param gy ������ id
	 * \return �Ƿ���óɹ�
	 */
	bool placeBuild(FarmBuild *build,int gx,int gy);
	/**
	 * ����index �Ƿ��ڽ�����������
	 */
	bool checkIndexInBuild(FarmBuild *build,int gx,int gy);
	/**
	 * ���ҽ�����
	 * \param tx touch������
	 * \param ty touch������
	 * \return ������ָ�� 
	 */
	FarmBuild *pickBuild(float tx,float ty);
	/**
	 * ��ȡ����ֵ
	 */
	int getIndex(int gx,int gy);
	/**
	 * ���ӽ�����
	 */
	void addBuild(FarmBuild *build);
	/**
	 * ��ȡȫ�ֵĵ�
	 */
	CCPoint getPixelPoint(int gx,int gy);
	/**
	 * ����赲��
	 */
	void clearBlock(const FarmBuildInfo &build);
	/**
	 * �����赲��
	 */
	void setBlock(const FarmBuildInfo &build,int buildId);
	enum{
		TOUCH_DOWN,
		TOUCH_MOVE,
		TOUCH_END,
	};
	/**
	 * ����touch
	 */
	void doTouch(int touchType,const CCPoint&touchPoint );

	FarmMap()
	{
		mapGridWidth = mapGridHeight = 0;
		nowMoveBuild = NULL;
	}
	FarmBuild *nowMoveBuild;
	std::map<DWORD,FarmBuildInfo> buildInfos;
	typedef std::map<DWORD,FarmBuildInfo>::iterator BUILD_INFOS_ITER;
	FarmBuildInfo findFarmInfoById(int id);

	void showBlocks();
private:
	int mapGridWidth; // ��ͼ���ӿ�
	int mapGridHeight; // ��ͼ���Ӹ�
	std::vector<int> _grids; // ��ͼ�ϵĸ�����
	std::vector<CCSprite*> _gridSprites; // ��ͼ�ϵĸ�����
	std::list<FarmBuild*> _builds; // �����Ｏ��
	typedef std::list<FarmBuild*>::iterator BUILDS_ITER;
	typedef std::vector<int>::iterator GRIDS_ITER;
};

NS_CC_END