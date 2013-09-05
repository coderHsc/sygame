#pragma once
#include "cocos2d.h"

NS_CC_BEGIN
/**
 * �������
 */
class HBSky:public CCNode{
public:
	/**
	 * ������� 
	 * \param pngName ����ͼ
	 * \param position λ��
	 * \param width ��
	 * \param height ��
	 */
	static HBSky * create(const char *pngName,const CCPoint& position,const CCSize & mapSize,const CCSize & skySize);
	bool init(const char *pngName,const CCPoint& position,const CCSize & mapSize,const CCSize & skySize);
	/**
	 * ����λ��
	 * \param mapNowPosition ��ͼ��ǰ��λ��
	 */
	void updatePoistion(const CCPoint & mapNowPosition);

	CCSize mapSize;
	CCSize skySize;
	HBSky()
	{
		
	}
};

NS_CC_END