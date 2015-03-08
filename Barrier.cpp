#include "Barrier.h"

USING_NS_CC;

bool Barrier::init(){
	if (!Node::init()){
		return false;
	}

	//�����
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("parkour.plist", "parkour.png");

	sprite = Sprite::createWithSpriteFrameName("rock.png");

	//��
	//setSprite(sprite);
	this->addChild(sprite);
	//ִ�ж���
	//sprite->runAction(createAnimate(frameCache));
	//�󶨸���
	initBody(1);

	return true;
}
