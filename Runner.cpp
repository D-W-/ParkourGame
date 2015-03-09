#include "Runner.h"

USING_NS_CC;

bool Runner::init(){
	//����ͼƬ�������
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("parkour.plist", "parkour.png");

	m_runner = Sprite::createWithSpriteFrameName("runner0.png");

	run_jumpSize = m_runner->getContentSize();
	crouchSize = Sprite::createWithSpriteFrameName("runnerCrouch0.png")->getContentSize();

	this->addChild(m_runner);

	initActionSet();//��ʼ����������

	initBody();

	this->scheduleUpdate();

	this->setTag(1);

	return true;
}

void Runner::initActionSet(){
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("parkour.plist", "parkour.png");
	SpriteFrame* frame = NULL;
	//3.0�и���vector ��������Array
	Vector<SpriteFrame*>frameVector;

	/* 1.----------------�����ܶ���Animation-----------------*/
	for (int i = 0; i <= 7; i++) {
		//�ӻ�����м��ؾ��鵽Vector
		frame = frameCache->spriteFrameByName(String::createWithFormat("runner%d.png", i)->getCString());
		frameVector.pushBack(frame);
	}

	//��vector�����SpriteFrame�б���Animation  �Լ�����һЩ����
	auto run_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, -1);
	//���ܶ��� Animation ȡ��Ϊ running 
	AnimationCache::getInstance()->addAnimation(run_animation, "running");

	/*4---------------*/
	frameVector.clear();
	for (int i = 0; i <= 3; i++){
		frame = frameCache->spriteFrameByName(String::createWithFormat("runnerJumpUp%d.png", i)->getCString());
		frameVector.pushBack(frame);
	}
	auto jumpUp_animation = Animation::createWithSpriteFrames(frameVector, 0.2);//����������ѭ��
	AnimationCache::getInstance()->addAnimation(jumpUp_animation, "jumpUp");

	/**/
	frameVector.clear();
	for (int i = 0; i <= 1; i++){
		frame = frameCache->spriteFrameByName(String::createWithFormat("runnerJumpDown%d.png", i)->getCString());
		frameVector.pushBack(frame);
	}
	auto jumpDown_animation = Animation::createWithSpriteFrames(frameVector, 0.3);
	AnimationCache::getInstance()->addAnimation(jumpDown_animation, "jumpDown");

	/**/
	frameVector.clear();
	frame = frameCache->spriteFrameByName("runnerCrouch0.png");
	frameVector.pushBack(frame);
	auto crouch_animation = Animation::createWithSpriteFrames(frameVector, 0.3);//����������ѭ��
	AnimationCache::getInstance()->addAnimation(crouch_animation, "crouch");

}

void Runner::doAction(const char* actionName){
	auto animation = AnimationCache::getInstance()->animationByName(actionName);
	auto action = Animate::create(animation);
	m_runner->runAction(action);
}

void Runner::initBody(){
	//���ݲ�ͬ״̬���ò�ͬ�����С
	Size bodySize;
	if (m_state == crouch){
		bodySize = crouchSize;
	}
	else{
		bodySize = run_jumpSize;
	}

	//����runner�ĸ���
	auto runerBody = PhysicsBody::createBox(bodySize, PHYSICSBODY_MATERIAL_DEFAULT);
	//���С�˷���������
	runerBody->setRotationEnable(false);
	runerBody->getShape(0)->setRestitution(0);
	//���ÿ�����ײ���
	runerBody->setCategoryBitmask(1);
	runerBody->setCollisionBitmask(1);
	runerBody->setContactTestBitmask(1);

	//�󶨸���
	this->setPhysicsBody(runerBody);
}

void Runner::Run(){
	m_state = running;
	initBody();
	doAction("running");
}

/**/
void Runner::Jump(){
	//ֻ�����ܶ�ʱ��������
	if (m_state == running){
		m_state = jumpUp;

		auto mass = this->getPhysicsBody()->getMass() * 350;

		this->getPhysicsBody()->applyImpulse(Vect(0, mass));

		m_runner->stopAllActions();

		doAction("jumpUp");
	}
}

void Runner::update(float dt){
	auto vel = this->getPhysicsBody()->getVelocity();
	if (m_state == jumpUp){
		if (vel.y < 0.1){
			m_state = jumpDown;
			m_runner->stopAllActions();
			doAction("jumpDown");
		}
	}
	if (m_state == jumpDown){
		CCLOG("%f", vel.y);
		//��Ӧ���� ���� 0
		if (vel.y > 0){
			m_state = running;
			m_runner->stopAllActions();
			doAction("running");
		}
	}
}

void Runner::Crouch(){
	//ֻ�����ܶ���ʱ�����
	if (m_state == running){
		m_state = crouch;
		m_runner->stopAllActions();
		initBody();
		doAction("crouch");
	}
}