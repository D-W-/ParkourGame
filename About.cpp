#include "About.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* GameAbout::createScene()
{
	auto scene = Scene::create();
	auto layer = GameAbout::create();
	scene->addChild(layer);
	return scene;
}


bool GameAbout::init()
{

	if ( !Layer::init() )
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//����
	auto sprite = Sprite::create("about/aboutui.png");
	sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite);

	//��Ӧ������Ϣ
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(GameAbout::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	//���Դ��� 
	this->setTouchEnabled(true);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameAbout::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

//����������
void GameAbout::onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)
{
	if(keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		/*Scene* newScene = HelloWorld::createScene();
		HelloWorld* layer = HelloWorld::create();
		newScene->addChild(layer);
		Director::sharedDirector()->pushScene(newScene);*/
		Director::sharedDirector()->popScene();
	}
}

//��Ӧ����
bool GameAbout::onTouchBegan(Touch *touch, Event *unused)
{
	CCLOG("here");
	Director::sharedDirector()->popScene();
	return false;
}
