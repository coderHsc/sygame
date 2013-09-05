#include "RpgTerrain.h"
#include "PngPack.h"
NS_CC_BEGIN

/**
* ������� 
* \param pngName ����ͼ
* \param position λ��
*/
RpgTerrain * RpgTerrain::create(const char *pngName,const CCPoint& position,const CCSize & size)
{
	RpgTerrain *pRet = new RpgTerrain();
    if (pRet && pRet->init(pngName,position,size))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
	return NULL;
}
bool RpgTerrain::init(const char *pngName,const CCPoint& position,const CCSize & size)
{
	//CCSprite *back = CCSprite::create(pngName);
	PackPng *back = PngPack::getMe().getPackPng(pngName);
	if (back)
	{
		this->size = size;
		this->addChild(back);
		back->setScaleX(size.width / back->getContentSize().width);
		back->setScaleY(size.height / back->getContentSize().height);
		back->setAnchorPoint(ccp(0,0));
	}
	this->setPosition(position);
	return true;
}
/**
* ����λ��
* \param mapNowPosition ��ͼ��ǰ��λ��
* \param mapSize ��ͼ�Ĵ�С
*/
void RpgTerrain::updatePosition(const CCPoint & mapNowPosition,const CCSize &mapSize)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float dx = ((size.width - visibleSize.width ) / (mapSize.width - visibleSize.width)) * mapNowPosition.x - mapNowPosition.x;
	float dy = ((size.height - visibleSize.height ) / (mapSize.height - visibleSize.height)) * mapNowPosition.y - mapNowPosition.y;
	this->setPosition(ccp(dx,this->getPositionY()));
}
/**
* ϵͳ���µ�ͼλ�õĻص�
*/
void RpgTerrain::setPosition(const CCPoint& pos)
{
	CCNode::setPosition(pos);
	for( CHILDS_ITER iter = childs.begin(); iter != childs.end();++iter)
	{
		(*iter)->updatePosition(pos,size);
	}
}


NS_CC_END