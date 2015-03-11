#ifndef __Raindrop_H__
#define __Raindrop_H__

#include "cocos2d.h"

USING_NS_CC;

class Raindrop :  public Sprite
{
public:
	static Raindrop *create(int row, int col);

	//������ڵ�������
	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
};

#endif /* defined(__Raindrop_H__) */
