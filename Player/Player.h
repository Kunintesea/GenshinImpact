#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Map/Map.h"

USING_NS_CC;
using namespace ui;

//�Ը������͵�Ԫ���˺��Ķ��塣���������硢�ҡ��ס��ݡ�ˮ���𡢱�����Ӧ����0-7
enum ElementType
{
	Physical = 0,
	Wind = 1,
	Rock = 2,
	Thunder = 3,
	Grass = 4,
	Water = 5,
	Fire = 6,
	Ice = 7
};



class Player : public Node
{
public:

	friend class PlayerStatusUI;//��Ԫ��
	virtual bool init();//��ʼ�����������ڳ�������ʱ����

	virtual void update(float dt);//���º�����ÿ֡����һ��
	virtual void moveAnimation(Vector<SpriteFrame*> frame, int actionTag); // �����ƶ�����
	virtual Sprite* getBody() { return m_body; }//��ȡ����
	virtual bool getKeyBoardState(EventKeyboard::KeyCode key) { return keyMap[key]; }
	virtual float getSpeed() { return speed; }//��ȡ�ٶ�
	bool testCol(Sprite* other);//�����ײ����
	bool testCol(TMXTiledMap* map, TMXLayer* layer);//�����ײͼ�������
	bool testCol_up(TMXTiledMap* map, TMXLayer* layer);
	bool testCol_down(TMXTiledMap* map, TMXLayer* layer);
	bool testCol_left(TMXTiledMap* map, TMXLayer* layer);
	bool testCol_right(TMXTiledMap* map, TMXLayer* layer);





	//ʵ����ֵ�ı�
	//���˺�������Ϊ�˺�ֵ���˺�����
	virtual void hurt(int damage, int damage_type);


	//�����˺����֣����20��
	Label* m_damage_label[20];
	//Ԫ�ط�Ӧ������֣����20��
	Label* m_element_label[20];



	CREATE_FUNC(Player);//����һ��Player����
private:

	TMXTiledMap* map = TMXTiledMap::create("Map/map-un.tmx");//��������ĵ�ͼ
	TMXLayer* layer = map->getLayer("wall");//��ͼ��ײ��

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

	//����״̬
	bool isDead = false;//�Ƿ�����
	bool isDodge = false;//�Ƿ�����

	//��������
	//�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��
	bool m_element[8] = { 0,0,0,0,0,0,0,0 };

	std::string m_name = "MM";//��������
	int m_hp = 10000;//Ѫ��
	int m_max_hp = 10000;//���Ѫ��
	int m_mp = 50;//Ԫ������
	int m_max_mp = 100;//���Ԫ������
	bool m_isElement[8] = { false,false,false,false,false,false,false,false };//Ԫ��״̬
	float m_defense = 0;//�������������������Ǽ���һ���˺�

	//������ȴʱ��
	float m_E_skill1_cd = 0;//E������ȴʱ��
	float m_Q_skill2_cd = 0;//Q������ȴʱ��

};

#endif 



