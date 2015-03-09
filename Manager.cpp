#include "Manager.h"

USING_NS_CC;


bool Manager::init(){
	if (!Node::init()){
		return false;
	}
	createCoin();
	createBarrier();
	this->scheduleUpdate();
	return true;
}

void Manager::createCoin(){
	for (int i = 0; i < 5; ++i){
		auto coin = Coin::create();
		coin->setVisible(false);
		coin->setTag(coinTag);
		this->addChild(coin);
		this->m_coinArr.pushBack(coin);
	}
}

void Manager::createBarrier(){
	for (int i = 0; i < 5; ++i){
		auto barr = Barrier::create();
		barr->setVisible(false);
		barr->setTag(barrTag);
		this->addChild(barr);
		this->m_barr.pushBack(barr);
	}
}

void Manager::update(float dt){
	int setNum = 0;
	for (Vector<Coin*>::iterator iter = this->m_coinArr.begin(); iter != this->m_coinArr.end(); ++iter){
		Coin* coin = *iter;
		//������Ļ
		if (coin->getPositionX() < -coin->getContentSize().width / 2){
			coin->setVisible(false);
		}
		//Ҫ�ǲ��ɼ���Ҫ�����ǲ�����Ļ�Ҫ�����Ǳ���ײ��
		if (!coin->isVisible()){
			setNum++;
		}
		//�ý���ƶ�
		coin->setPositionX(coin->getPositionX() - 2);
	}
	if (setNum == 5){
		int i = 0;
		float posX = 640 + 50;
		float posY = 59 + 15 + CCRANDOM_0_1() * 160;
		for (Vector<Coin*>::iterator iter = this->m_coinArr.begin(); iter != this->m_coinArr.end(); ++iter){
			Coin* coin = *iter;
			//��������һ��
			if (i < 2){
				posX += 100;//�������ͬһ�߶ȣ����30
			}
			else{
				//��������λ�� 
				i = -1;
				posY = 49 + 15 + CCRANDOM_0_1() * 160;
				posX += 400;
			}
			i++;//���ý�Ҹ�����¼
			//
			coin->setVisible(true);
			coin->setPosition(posX, posY);
		}
	}
	setNum = 0;
	//�ϰ���
	for (Vector<Barrier*>::iterator iter = this->m_barr.begin(); iter != this->m_barr.end(); ++iter){
		Barrier* barr = *iter;
		if (barr->getPositionX() < -barr->getContentSize().width / 2)
			barr->setVisible(false);
		if (!barr->isVisible())
			setNum++;
		//�ȱ����ƶ��Ŀ�һ��
		barr->setPositionX(barr->getPositionX() - 4);
	}
	if (setNum == 5){
		float posX = 640 + 50;
		float posY;
		for (Vector<Barrier*>::iterator iter = this->m_barr.begin(); iter != this->m_barr.end(); ++iter){
			auto barr = *iter;
			posX += 400;
			posY = 49 + 15 + CCRANDOM_0_1() * 160;
			barr->setPosition(posX, posY);
			barr->setVisible(true);
		}
	}
	
}