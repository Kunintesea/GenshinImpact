#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include<map>
#include "cocos2d.h"
#include "newCamera.h"
#include"Player\Enemy.h"
#include "mapManager\mapManager.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#include "SimpleaudioEngine.h"
#include "box/box.h"
struct PlayerInformation
{
      //基础属性
      int base_attack = 10;//基础攻击力
      float base_defense = 0.1;//基础防御力
      int base_hp = 100;//基础血量
      //额外属性
      int extra_attack = 0;//额外攻击力
      float extra_defense = 0;//额外防御力
      int extra_hp = 0;//额外血量

      string name; //人物名字
      string weapon; //人物武器
      float element[8] = { 0,0,0,0,0,0,0,0 }; //附着在人物身上的元素，0则为没有，1则为有

      int exp = 20;//经验值
      int max_exp = 100;//最大经验值

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
	//攻击力
      int attack = 10;

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

      bool isFog1Enabled000 = true;  // 迷雾是否启用
      bool isFog2Enabled000 = true;
      bool isFog3Enabled000 = true;
      bool isFog4Enabled000 = true;

      TreasureChest* getchest1() { return chest1; }
      TreasureChest* getchest2() { return chest2; }

    void set_New_Teleport_position(const Vec2& position) { New_Teleport_position = position; } 
    static cocos2d::Scene* createScene();

    virtual bool init(); //初始化函数，会在场景创建时调用

    void refreshMonster();//刷新怪物
    
    void characterset();//设置角色
    bool PlayerAttack(Effects* me, BasePlayer* other);
    void update(float dt);//更新函数，每帧调用一次
    void menuCloseCallback(cocos2d::Ref* pSender);//退出按钮的回调函数
    void storeInfo(Player* sprite, int tag); //切换角色时储存信息
    void startDialog(string name);//开始对话
    bool isTeleported() {return New_Teleport_position == Vec2(0, 0); }
    Player* getcurrentplayer()
    {
          return currentPlayer;
    }
    //存储小地图，别的对象可能会修改迷雾。


	//文件存储
    void savemessage();
    void loadmessage();
    void initmessage(const char* pName);//传入路径

    //仓库，有物品名称与数量
    std::map<string, int> storage;

    bool getFogEnabled(int i) {
          switch (i) {
          case 1: return isFog1Enabled;
          case 2: return isFog2Enabled;
          case 3: return isFog3Enabled;
          case 4: return isFog4Enabled;
          }
    }

    void setFogEnabled(int i) {
          switch (i) {
          case 1: isFog1Enabled = false;
                break;
          case 2: isFog2Enabled = false;
                break;
          case 3: isFog3Enabled = false;
                break;
          case 4: isFog4Enabled = false;
                break;
          }
    }
    CREATE_FUNC(HelloWorld);
private:

      TreasureChest* chest1;
      TreasureChest* chest2;
      //储存角色信息的数组
      PlayerInformation playerInfo[2];
      //召唤敌人的函数
      void summonEnemy(std::string name, Vec2 position);
      //召唤计时器
      float summonTime = 0;
      //当前上传的角色
      int team;

      bool isrefresh = true;

      bool isFog1Enabled = true;  // 迷雾是否启用
      bool isFog2Enabled = true;
      bool isFog3Enabled = true;
      bool isFog4Enabled = true;

      //存储删除的对象的数组
      Enemy* enemygroup_delete[20];
      //当前玩家
      Player* currentPlayer;

      //存储玩家的数组
      //Player* playergroup[20];
      //存储敌人的数组
      Enemy* enemygroup[20];

      newCamera* myCamera;
      Player* sprite;
      TMXTiledMap* map;
      mapManager* mapManager;
      Vec2 New_Teleport_position;
      int a = 0;

      //存储当前接到任务的vector
      vector<string> task;//存任务名字
      //存任务进度
      vector<int> task_progress;//存任务进度
      //对话的npc名字
      string dialogername;
      int dialoging = 0;//对话的进度
      //是否面临选择
      bool ischoose = false;
      int choose = 0;
      // 怪物刷新状态
      std::set<std::pair<int,int>> monsterRefreshState;

      //当前对话的npc名字
      string currentdialogername;
	  string currentrealdialogername;

      //一个map，存储对话的名字（string）和对话内容（string的数组，按照顺序进行对话），前一个作为key，后一个作为value
      std::map<string, vector<string>> dialog_map;
      //std::map<string, string> dialog_map;

};

#endif // __HELLOWORLD_SCENE_H__
