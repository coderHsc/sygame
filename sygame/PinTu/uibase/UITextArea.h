#pragma once
#include "cocos2d.h"
#include "vector"
NS_CC_BEGIN
/**
 * ʵ����ɫ�����ı��� ��Ϣչʾ�� ��������򵥵ķ��� 
 */
class UITextArea:public CCLabelBMFont{
public:
	/**
	 * ����UITextArea
	 */
	static UITextArea * create(const char *str, const char *fntFile);
	/**
	 * ����ʵ�ָ��ļ�����
	 */
	void createFontChars();
	/**
	 * ����������ɫ
	 */
	void setColors(int startId,int endId,const ccColor3B& color);
private:
	std::vector<ccColor3B> colors;
};
 
// TODO ���ı�����Ϣչʾ չʾ����������xml �ļ� ������Ϣ����
/***
 * <richtext fnt="">
 *		<font x="" y="" fontSize="" color="" content=""/>
 *		<font x="" y ="" fontSize="" color="" content=""/>
 *		<img src="" x="" y="" width="" height=""/>
 * </richtext>
 */
NS_CC_END