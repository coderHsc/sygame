/**
 * ���ص�ͼ ���ҽ�����ͬ����λ�ø��� �зֲ�ĸ��� ���Լ����� ���Զ����ӽڵ��λ�ø����߼�
 **/
#pragma once
#include "cocos2d.h"

NS_CC_BEGIN
/**
 * ��
 */
class RpgTerrain:public CCNode{
public:
	/**
	 * ������� 
	 * \param pngName ����ͼ
	 * \param position λ��
	 */
	static RpgTerrain * create(const char *pngName,const CCPoint& position,const CCSize & size);
	bool init(const char *pngName,const CCPoint& position,const CCSize & size);
	/**
	 * ����λ��
	 * \param mapNowPosition ��ͼ��ǰ��λ��
	 * \param mapSize ��ͼ�Ĵ�С
	 */
	void updatePosition(const CCPoint & mapNowPosition,const CCSize &mapSize);
	/**
	 * ϵͳ���µ�ͼλ�õĻص�
	 */
	void setPosition(const CCPoint& pos);
	/**
	 * ��ǰ��Ĵ�С
	 */
	CCSize size;
	RpgTerrain()
	{
		
	}
	std::vector<RpgTerrain*> childs;
	typedef std::vector<RpgTerrain*>::iterator CHILDS_ITER;
};

NS_CC_END