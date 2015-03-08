#ifndef __BASE__H__
#define __BASE__H__

#include "cocos2d.h"

USING_NS_CC;

class Base : public cocos2d::Node{
	//coin �� Barrier �Ļ���
public:
	virtual bool init();
	CREATE_FUNC(Base);

	//����
	cocos2d::Animate* createAnimate(cocos2d::SpriteFrameCache* frameCache);
	//��������ʼ��
	void initBody(int mask);
	Sprite* sprite;

};

#endif