/**
 * ʵ�ִ��вü�����Ĺ�����ͼ
 */
#pragma once
#include "cocos2d.h"
#include "UIBase.h"
NS_CC_BEGIN
class UIScrollView:public UIBase{
public:
	static UIScrollView* create(float x,float y,float w,float h);
	/**
	 * ���ô�С
	 */
	void setSize(float width,float height);
	/**
	 * ����λ��
	 */
	void setPosition(float x,float y);
	/**
	 * ��������
	 */
	bool addContent(UIBase*node);
	/**
	 * ��Ⱦǰ����
	 */
	virtual void visit();
	/**
	 * create ��������
	 */
	CREATE_FUNC(UIScrollView);
	bool init(){return true;}
	/** 
	 * ����Ƿ���������
	 */
	bool touchDown(float x,float y);
	/**
	 * ����λ��
	 */
	bool touchMove(float x,float y);
	/**
	 * ֹͣ�϶�
	 */
	bool touchEnd(float x,float y);

	bool checkIn(float x,float y);
	enum{
		UP_DOWN = 1, // �����ƶ�
		LEFT_RIGHT = 2, // �����ƶ�
		SCROLL_ALL = 3, // ���������ƶ�
	};
	/**
	 * ���ù�������
	 */
	void setScrollType(int scollType)
	{
		_scrollDir = scollType;
	}
	virtual void setEditable(bool tag){
		_editable = tag;
	}
	UIBase* child;
protected:
	int _scrollDir; // ���ù�������
	bool _touchIn; // �Ƿ��ڸ������ڲ���
	CCPoint nowTouchPoint; // ��ǰtouch �ĵ�
	bool _editable;
	float _x;
	float _y;
	float _width;
	float _height;
	UIScrollView()
	{
		_editable = true;
		_x = _y = _width = _height = 0;
		child = NULL;
		_scrollDir = LEFT_RIGHT;
		_touchIn = false;
	}
};

NS_CC_END