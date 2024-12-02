#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"


USING_NS_CC;

class Player : public Node
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用
	Sprite* getBody() { return m_body; }//获取身体
	//相机跟随函数，传入一个相机对象，让相机始终跟随m_body
	void update(float dt);//更新函数，每帧调用一次
	CREATE_FUNC(Player);//创建一个Player对象
private:
	
	//人物身体组成部分
	Sprite* m_body;//身体
	Sprite* m_head;//头部
	//键盘事件监听
	std::map<EventKeyboard::KeyCode, bool> keyMap;//创建一个map，用来存储按键的状态
	
	
	//人物动画
	Animate* PlayerAction;
	Animation* animation_left;
	Animation* animation_right;
	Animation* animation_up;
	Animation* animation_down;




};

#endif 
