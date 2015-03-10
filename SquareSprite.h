#ifndef __SquareSprite_H__
#define __SquareSprite_H__

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
	DISPLAY_MODE_NORMAL = 0,
	DISPLAY_MODE_HORIZONTAL,
	DISPLAY_MODE_VERTICAL,
} DisplayMode;


class SquareSprite :  public Sprite
{
public:
	static SquareSprite *create(int row, int col);
	static float getContentWidth();

	//�������ڵ�������
	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	//�Ƿ�ѡ��
	CC_SYNTHESIZE(bool,m_selected,Selected);
	//ѡ·ʱǰ��ķ���
	CC_SYNTHESIZE(SquareSprite*,m_prev,Prev);
	//ѡ·ʱ�Ƿ��ڶ�������
	//CC_SYNTHESIZE(bool,m_inQueue,Que);
	//CC_SYNTHESIZE_READONLY(DisplayMode, m_displayMode, DisplayMode);
	//void setDisplayMode(DisplayMode mode);
};

#endif /* defined(__SquareSprite_H__) */
