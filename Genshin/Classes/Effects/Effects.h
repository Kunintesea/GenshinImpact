#ifndef __EFFECTS_NODE_H__
#define __EFFECTS_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;




class Effects : public Node
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用
    void update(float dt);//更新函数，每帧调用一次

	CREATE_FUNC(Effects);//创建一个Player对象
private:
	//Sprite，放特效
	Sprite* effect;


	//特效动画
	Vector<SpriteFrame*> Explode;
	Vector<SpriteFrame*> walk_back;
	Vector<SpriteFrame*> walk_front;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;
	Vector<SpriteFrame*> staticForwards;
};

#endif 
