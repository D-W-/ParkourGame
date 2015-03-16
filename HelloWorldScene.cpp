#include "HelloWorldScene.h"
#include "About.h"

#define userDefault UserDefault::getInstance()

USING_NS_CC;

bool isFirstMusic = true;
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}


bool HelloWorld::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//��ʼ��
	touchedBack = 0;
	exit = NULL;
	Size screenSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	CCSprite* Background = CCSprite::create("menu/UI1.png");
	Background->setPosition(ccp(screenSize.width/2,screenSize.height/2));
	this->addChild(Background);
	//����Ч������
	this->setTouchEnabled(true);

	//��ʼ��Ϸ
	auto item_Adventure = MenuItemImage::create(
							"menu/play1.png",
							"menu/play2.png",
							CC_CALLBACK_1(HelloWorld::startGame, this));
	item_Adventure->setPosition(screenSize.width/2+55,screenSize.height/2-28);
	//���ڽ���
	auto item_About= MenuItemImage::create(
							"menu/about1.png",
							"menu/about2.png",
							CC_CALLBACK_1(HelloWorld::aboutFunc, this));
	item_About->setPosition(item_About->getContentSize().width-20,item_About->getContentSize().height/2);
	//���ű�������
	if(!userDefault->getBoolForKey("Music")){
		userDefault->getBoolForKey("Music",true);
		userDefault->flush();
	}
	int musBef = userDefault->getBoolForKey("Music");
	userDefault->flush();
	if(isFirstMusic & musBef)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/Babkg_music.wav",true);
		isFirstMusic = false;
	}

	//��������
	//�򿪹ر�����״̬
	auto on = MenuItemImage::create("menu/voice1.png","menu/voice2.png",NULL,NULL);
	auto off = MenuItemImage::create("menu/voice3.png","menu/voice4.png",NULL,NULL);
	//��ʼ��״̬Ϊ1
	MenuItemToggle *item_Voice;
	int selectId;
	if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		item_Voice = MenuItemToggle::createWithTarget(this, menu_selector(HelloWorld::setOptions),on,off, NULL);
		AudioState = 1;
		selectId = AudioState? 0 : 1;
	}
	else
	{
		item_Voice = MenuItemToggle::createWithTarget(this, menu_selector(HelloWorld::setOptions),off,on, NULL);
		AudioState = 0;
		selectId = AudioState? 1 : 0;
	}
	//int selectId = AudioState? 0 : 1;
	item_Voice->setSelectedIndex(selectId);
	item_Voice->setPosition(item_Voice->getContentSize().width-20,item_Voice->getContentSize().height*2);

	CCMenu* menu = CCMenu::create(item_Adventure,item_Voice,item_About,NULL);
	menu->setPosition(0,0);
	this->addChild(menu);

	//��Ӧ������Ϣ
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	// bind touch eventʵ�ִ���Ч��
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}
//���ڰ����Ļص�����
void HelloWorld::aboutFunc(Ref* pSender)
{
	CCLOG("about_Menu item clicked");
	Director::sharedDirector()->pushScene(GameAbout::createScene());
	//Director::sharedDirector()->replaceScene();
}
//��ʼ��Ϸ�����Ļص�����
void HelloWorld::startGame(cocos2d::Ref* pSender)
{
	CCLOG("dventure_Menu item clicked");
	CCDirector::sharedDirector()->replaceScene(PlayLayer::createScene());
}
//���������Ļص����������û���ѡ��洢�ں�̨
void HelloWorld::setOptions(cocos2d::Ref* pSender)
{
	bool temp = userDefault->getBoolForKey("Music");
	userDefault->flush();
	userDefault->setBoolForKey("Music",!temp);
	userDefault->flush();

	bool tmpSound = AudioState;
	AudioState = !AudioState;

	if (!tmpSound) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/Babkg_music.wav",true);
		isFirstMusic = false;
	}else{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}
//��Ӧ��׿���ؼ�
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)
{
	exit = LabelTTF::create("Press back button again to exit", "fonts/MSYH.TTF", 48);
	if(keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		if(!touchedBack)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Point origin = Director::getInstance()->getVisibleOrigin();
			exit->runAction(CCFadeOut::create(2.0));
			exit->setColor(Color3B::BLACK);
			exit->setPosition(Point(origin.x + visibleSize.width/2,
				origin.y + visibleSize.height-60));
			this->addChild(exit);
			touchedBack = true;
		}
		else 
			Director::getInstance()->end();
	}
	else
	{
		touchedBack = false;
		if(exit)
		{
			exit->removeFromParentAndCleanup(true);
		}
	}
}
//��Ӧ����
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused)
{
	touchedBack = false;
	if(exit)
	{
		exit->removeFromParentAndCleanup(true);
	}
	return touchedBack;
}
