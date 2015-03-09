#ifndef __PLAYLAYER_H__
#define __PLAYLAYER_H__

#include "cocos2d.h"
#include "Runner.h"
#include "Manager.h"

USING_NS_CC;

class PlayLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PlayLayer);

	PlayLayer();

	virtual bool onTouchBegan(Touch *touch, Event *unused) override;
	virtual void onTouchMoved(Touch *touch, Event *unused) override;
	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
	//��ʼ������
	void initBG();
	//��update�����õ�ͼ����
	virtual void update(float dt);
	void runEffect(Sprite* coin);
private:
	bool onContactBegin(PhysicsContact& contact);
	//��������
	PhysicsWorld* m_world;

	//�洢���е�֡ͼƬ
	Vector<SpriteFrame* >allframes;
	Animation* animation;
	Animate* animate;
	//���ܵ�Ҷ��
	Runner* hero;
	//��������
	cocos2d::Sprite* bgSprite1;
	cocos2d::Sprite* bgSprite2;
	cocos2d::Sprite* groundSprite1;
	cocos2d::Sprite* groundSprite2;
	//���ڹ����ҵ�
	Manager* man;
	//�������
	int counter;
	//������ʼ��
	int startPoint;
};

#endif // __PLAYLAYER_H__
