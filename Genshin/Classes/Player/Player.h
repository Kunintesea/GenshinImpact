#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;






class Player : public Node
{
public:
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	void update(float dt);//���º�����ÿ֡����һ��
	void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // �����ƶ�����

	Sprite* getBody() { return m_body; }//��ȡ����
	bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	float getSpeed() { return speed; }
	CREATE_FUNC(Player);//����һ��Player����
private:
	float speed;
	//����������ɲ���
	Sprite* m_body;//����
	Sprite* m_head;//ͷ��
	//�����¼�����
	std::map<EventKeyboard::KeyCode, bool> keyMap;//����һ��map�������洢������״̬

	//���ﶯ��
	Vector<SpriteFrame*> walk_back;
	Vector<SpriteFrame*> walk_front;
	Vector<SpriteFrame*> walk_left;
	Vector<SpriteFrame*> walk_right;
	Vector<SpriteFrame*> staticForwards;


	//��������
	int m_hp=100;//Ѫ��
	int m_max_hp=100;//���Ѫ��
	
};

#endif 
