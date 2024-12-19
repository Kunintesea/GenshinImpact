#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "newCamera.h"
#include"Player\Enemy.h"
#include "mapManager\mapManager.h"


struct PlayerInformation
{
	string name; //��������
	string weapon; //��������
	float element[8] = { 0,0,0,0,0,0,0,0 }; //�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��

	//����
	int shield = 0;//����ֵ
	int hp = 100;//Ѫ��
	int max_hp = 100;//���Ѫ��

	int mp = 50;//Ԫ������
	int max_mp = 100;//���Ԫ������
	bool isElement[8] = { false,false,false,false,false,false,false,false };//Ԫ��״̬
	float defense_origin = 0;
	float defense = defense_origin;//�������������������Ǽ���һ���˺�
	int level = 1;//�ȼ�

	//һЩ״̬Ч��
	float superconductivity = 0;//����״̬����ɼ���

	//������ȴʱ��
	float E_CD = 0;//E������ȴʱ��
	float Q_CD = 0;//Q������ȴʱ��

	//�����ȴʱ��
	float max_E_CD = 5;//E������ȴʱ��
	float max_Q_CD = 10;//Q������ȴʱ��

	//����ͷ����ʾԪ�ظ���������������ͼ��
	Sprite* element_sprite[2];
	int element_sprite_type[2] = {};//Ԫ�ظ���ͼ������

	//����ĳ�ֹ���
	bool immune[8] = { false,false,false,true,false,false,false,false };

	//��ʾ״̬������
	statement statement[99];
	//��¼״̬ʱ�������
	float statement_time[99];
};


class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();//��ʼ�����������ڳ�������ʱ����


	void characterset();//���ý�ɫ
	bool PlayerAttack(Effects* me, BasePlayer* other);
	void update(float dt);//���º�����ÿ֡����һ��
	void menuCloseCallback(cocos2d::Ref* pSender);//�˳���ť�Ļص�����
	void storeInfo(Player* sprite, int tag); //�л���ɫʱ������Ϣ

	



    CREATE_FUNC(HelloWorld);
private:
	//�����ɫ��Ϣ������
	PlayerInformation playerInfo[2];
	//�ٻ����˵ĺ���
	void summonEnemy(std::string name, Vec2 position);
	//�ٻ���ʱ��
	float summonTime = 0;



	//�洢ɾ���Ķ��������
	Enemy* enemygroup_delete[20];
	//��ǰ���
	Player* currentPlayer;

	//�洢��ҵ�����
	//Player* playergroup[20];
	//�洢���˵�����
	Enemy* enemygroup[20];

    newCamera* newCamera;
    Player* sprite;
    TMXTiledMap* map;
    mapManager* mapManager;
    int a = 0;
};

#endif // __HELLOWORLD_SCENE_H__
