/**
 * �߶ι��ɵ��赲�ռ�
 */
#pragma once
#include "LineCollide.h"
#include <vector>
#include "xmlScript.h"
NS_CC_BEGIN
/**
 * ���ص��㷨 ��������Ƿ��ܽ�����Χ���߶ι��ɵ�������
 */
class LineBlockMap:public script::tixmlCode,public CCLayer{
public:
	bool loadFromXml(const char*fileName);
	bool checkCollide(const CCRect& rect);
	bool checkSpriteNextPointValid(CCSprite *sprite,const CCPoint &dest);
	void draw();
	CREATE_FUNC(LineBlockMap);
	bool init()
	{
		return true;
	}
private:
	std::vector<Line> _lines;
	/**
	 * �������ļ��м�������
	 * \param node ���ø��ڵ�
	 */
	void takeNode(script::tixmlCodeNode *node);
};

NS_CC_END