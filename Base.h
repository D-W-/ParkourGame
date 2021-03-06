#ifndef __BASE__H__
#define __BASE__H__

#include "cocos2d.h"

USING_NS_CC;

class Base : public cocos2d::Node{
	//coin 和 Barrier 的基类
public:
	virtual bool init();
	CREATE_FUNC(Base);

	//动画
	Animate* createAnimate(SpriteFrameCache* frameCache,int n,const char* name);
	//物理刚体初始化
	void initBody(int mask);
	Sprite* sprite;

};

#endif