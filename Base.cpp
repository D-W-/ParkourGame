#include "Base.h"

USING_NS_CC;

bool Base::init(){
	if (!Node::init()){
		return false;
	}
	return true;
}

Animate* Base::createAnimate(SpriteFrameCache* frameCache){
	SpriteFrame* frame = NULL;
	//���鲻�� Ҫ��vector
	//auto frameArray = Array::create();
	//frameArray->retain();
	Vector<SpriteFrame*>frameArray;

	// ��һ���б�������SpriteFrame���� 
	for (int i = 0; i <= 7; i++) {
		/* ��SpriteFrame������л�ȡCCSpriteFrame���� */
		frame = frameCache->spriteFrameByName(String::createWithFormat("coin%d.png", i)->getCString());
		frameArray.pushBack(frame);

	}
	/* ʹ��SpriteFrame�б����������� */
	auto animation = Animation::createWithSpriteFrames(frameArray);

	animation->setLoops(-1);

	animation->setDelayPerUnit(0.1f);

	/* ��������װ��һ������ */
	auto action = Animate::create(animation);

	return action;
}

void Base::initBody(int mask){
	auto phyBody = PhysicsBody::createEdgeBox(sprite->getContentSize());
	phyBody->getShape(0)->setDensity(1000000);
	phyBody->getShape(0)->setMass(10000);
	phyBody->getShape(0)->setMaterial(PHYSICSBODY_MATERIAL_DEFAULT);
	phyBody->setCategoryBitmask(1);
	//����Ϊ0������ͱ��ܵ�С�˷�����ײ����Ϊ��������ײ���������ֵ�߼���
	phyBody->setCollisionBitmask(mask);
	phyBody->setContactTestBitmask(1);

	this->setPhysicsBody(phyBody);
}

