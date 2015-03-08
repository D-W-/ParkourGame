#include "Coin.h"

USING_NS_CC;

bool Coin::init(){
	if (!Node::init()){
		return false;
	}

	//�����
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("parkour.plist", "parkour.png");

	sprite = Sprite::createWithSpriteFrameName("coin0.png");

	//��
	//setSprite(sprite);
	this->addChild(sprite);
	//ִ�ж���
	sprite->runAction(createAnimate(frameCache));
	//�󶨸���
	initBody(0);

	return true;
}
