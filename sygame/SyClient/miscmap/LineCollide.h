#pragma once
#include "cocos2d.h"
NS_CC_BEGIN
class Line{
public:
	CCPoint src;
	CCPoint dest;
	Line(float sx,float sy, float dx,float dy)
	{
		src = ccp(sx,sy);
		dest = ccp(dx,dy);
	}
	Line()
	{
	}
	Line(const CCPoint _s,const CCPoint _d)
	{
		src = _s;
		dest = _d;
	}
};
class LineCollide{
public:
	static bool checkCollide(const Line &src,const Line & dest)
	{
		/*
	private function simpleLineTest(l1p1x:Number,l1p1y:Number,l1p2x:Number,l1p2y:Number,l2p1x:Number,l2p1y:Number,l2p2x:Number,l2p2y:Number):Boolean {//��������Ǻ��ģ�������������Ƿ��ཻ��ÿ�������������ݣ���ʼ����������꣬��������������꣩�������������ܹ���Ҫ8������
    var line1p1:Number;
    line1p1=(l1p2x-l1p1x)*(l2p1y-l1p1y)-(l2p1x-l1p1x)*(l1p2y-l1p1y);//��һ���߶ε������ͣ���һ���߶εĿ�ʼ����ڶ����߶εĿ�ʼ����ɵ���������������
    var line1p2:Number;
    line1p2=(l1p2x-l1p1x)*(l2p2y-l1p1y)-(l2p2x-l1p1x)*(l1p2y-l1p1y);//��һ���߶ε������ͣ���һ���߶εĿ�ʼ����ڶ����߶εĽ�������ɵ���������������
    var line2p1:Number;
    line2p1=(l2p2x-l2p1x)*(l1p1y-l2p1y)-(l1p1x-l2p1x)*(l2p2y-l2p1y);//�ڶ����߶ε������ͣ��ڶ����߶εĿ�ʼ�����һ���߶εĿ�ʼ����ɵ���������������
    var line2p2:Number;
    line2p2=(l2p2x-l2p1x)*(l1p2y-l2p1y)-(l1p2x-l2p1x)*(l2p2y-l2p1y);//�ڶ����߶ε������ͣ��ڶ����߶εĿ�ʼ�����һ���߶εĽ�������ɵ���������������
    if ((line1p1*line1p2<=0)&&(line2p1*line2p2<=0)) {//�жϷ�������ǰ����
     return true;//�ཻ
    } else {
     return false;//�����ཻ
    }
   }
		*/
		float L1p1x = src.src.x;
		float L1p1y = src.src.y;
		float L1p2x = src.dest.x;
		float L1p2y = src.dest.y;
		float L2p1x = dest.src.x;
		float L2p1y = dest.src.y;
		float L2p2x = dest.dest.x;
		float L2p2y = dest.dest.y;

		float line1p1 = (L1p2x-L1p1x)*(L2p1y-L1p1y)-(L2p1x-L1p1x)*(L1p2y-L1p1y);
		float line1p2 = (L1p2x-L1p1x)*(L2p2y-L1p1y)-(L2p2x-L1p1x)*(L1p2y-L1p1y);
		float line2p1 = (L2p2x-L2p1x)*(L1p1y-L2p1y)-(L1p1x-L2p1x)*(L2p2y-L2p1y);
		float line2p2 = (L2p2x-L2p1x)*(L1p2y-L2p1y)-(L1p2x-L2p1x)*(L2p2y-L2p1y);
		if ((line1p1*line1p2<=0)&&(line2p1*line2p2<=0)) {
			return true;//�ཻ
		} else {
		 return false;//�����ཻ
		}
	}
};

NS_CC_END