#pragma once
#include "cocos2d.h"
#include <vector>
#include "MapObject.h"
NS_CC_BEGIN
/**
 * �ر�
 */
class MapBackGroud:public MapObject{
public:
	MapBackGroud():MapObject(OBJECT_BACK_GROUD)
	{
	
	}
	/**
	 * ����һ���ر�
	 */
	static MapBackGroud* create(const char *fileName,int width,int height,int eachWidth,int eachHeight);
	/**
	 * ʹ�������ʼ��
	 */
	virtual bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated);
	/**
	 * ��������
	 */
	void setTextureRect(const CCRect& rect, bool rotated, const CCSize& untrimmedSize);
	/**
	 * ����
	 */
	virtual void draw(void);
	virtual void updateTransform(void);

	bool checkIn(float x,float y);
private:
	std::vector<ccV3F_C4B_T2F> points; // ���㼯��
	int _width;
	int _height;
	int _eachWidth;
	int _eachHeight;
};

NS_CC_END