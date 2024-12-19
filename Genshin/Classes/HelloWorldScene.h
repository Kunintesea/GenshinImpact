#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "newCamera.h"
#include"Player\Enemy.h"
#include "mapManager\mapManager.h"


class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();//��ʼ�����������ڳ�������ʱ����


	void characterset();//���ý�ɫ
	bool PlayerAttack(Effects* me, BasePlayer* other);
	void update(float dt);//���º�����ÿ֡����һ��
	void menuCloseCallback(cocos2d::Ref* pSender);//�˳���ť�Ļص�����

	
	//�洢��ҵ�����
	Player* playergroup[20];
	//�洢���˵�����
	Enemy* enemygroup[20];
	//���������õ�sprite
	//Sprite* Namesprite;


    CREATE_FUNC(HelloWorld);
private:




	//�洢ɾ���Ķ��������
	Enemy* enemygroup_delete[20];

    newCamera* newCamera;
    Player* sprite;
    TMXTiledMap* map;
    mapManager* mapManager;
    int a = 0;
};

#endif // __HELLOWORLD_SCENE_H__
