#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;






class Player : public Node
{
public:
	virtual bool init();//初始化函数，会在场景创建时调用

	void update(float dt);//更新函数，每帧调用一次
	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // 人物移动动画

	Sprite* getBody() { return m_body; }//获取身体
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	float getSpeed() { return speed; }
	CREATE_FUNC(Player);//创建一个Player对象
private:
	float speed;
	//人物身体组成部分
	Sprite* m_body;//身体
	Sprite* m_head;//头部
	//键盘事件监听
	std::map<EventKeyboard::KeyCode, bool> keyMap;//创建一个map，用来存储按键的状态

	//人物动画
	Vector<SpriteFrame*> walk_back;
	Vector<SpriteFrame*> walk_front;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;
	Vector<SpriteFrame*> staticForwards;


	//人物数据
	int m_hp=100;//血量
	int m_max_hp=100;//最大血量
	
};

#endif 
