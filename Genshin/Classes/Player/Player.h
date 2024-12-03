#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "UI/PlayerStatusUI.h"


USING_NS_CC;

class Player : public Node
{
public:
	virtual bool init();//��ʼ�����������ڳ�������ʱ����
	Sprite* getBody() { return m_body; }//��ȡ����
	//������溯��������һ��������������ʼ�ո���m_body
	void update(float dt);//���º�����ÿ֡����һ��
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
	Animate* PlayerAction;
	Animation* animation_left;
	Animation* animation_right;
	Animation* animation_up;
	Animation* animation_down;

	//UI����
	PlayerStatusUI* m_statusUI = PlayerStatusUI::create();


};

#endif 
