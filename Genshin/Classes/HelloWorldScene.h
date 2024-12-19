#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "newCamera.h"
#include"Player\Enemy.h"
#include "mapManager\mapManager.h"


struct PlayerInformation
{
	string name; //人物名字
	string weapon; //人物武器
	float element[8] = { 0,0,0,0,0,0,0,0 }; //附着在人物身上的元素，0则为没有，1则为有

	//护盾
	int shield = 0;//护盾值
	int hp = 100;//血量
	int max_hp = 100;//最大血量

	int mp = 50;//元素能量
	int max_mp = 100;//最大元素能量
	bool isElement[8] = { false,false,false,false,false,false,false,false };//元素状态
	float defense_origin = 0;
	float defense = defense_origin;//防御。防御力的作用是减少一切伤害
	int level = 1;//等级

	//一些状态效果
	float superconductivity = 0;//超导状态，造成减防

	//技能冷却时间
	float E_CD = 0;//E技能冷却时间
	float Q_CD = 0;//Q技能冷却时间

	//最大冷却时间
	float max_E_CD = 5;//E技能冷却时间
	float max_Q_CD = 10;//Q技能冷却时间

	//人物头顶显示元素附着情况，最多两个图标
	Sprite* element_sprite[2];
	int element_sprite_type[2] = {};//元素附着图标种类

	//免疫某种攻击
	bool immune[8] = { false,false,false,true,false,false,false,false };

	//表示状态的数组
	statement statement[99];
	//记录状态时间的数组
	float statement_time[99];
};


class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init();//初始化函数，会在场景创建时调用


	void characterset();//设置角色
	bool PlayerAttack(Effects* me, BasePlayer* other);
	void update(float dt);//更新函数，每帧调用一次
	void menuCloseCallback(cocos2d::Ref* pSender);//退出按钮的回调函数
	void storeInfo(Player* sprite, int tag); //切换角色时储存信息

	



    CREATE_FUNC(HelloWorld);
private:
	//储存角色信息的数组
	PlayerInformation playerInfo[2];
	//召唤敌人的函数
	void summonEnemy(std::string name, Vec2 position);
	//召唤计时器
	float summonTime = 0;



	//存储删除的对象的数组
	Enemy* enemygroup_delete[20];
	//当前玩家
	Player* currentPlayer;

	//存储玩家的数组
	//Player* playergroup[20];
	//存储敌人的数组
	Enemy* enemygroup[20];

    newCamera* newCamera;
    Player* sprite;
    TMXTiledMap* map;
    mapManager* mapManager;
    int a = 0;
};

#endif // __HELLOWORLD_SCENE_H__
