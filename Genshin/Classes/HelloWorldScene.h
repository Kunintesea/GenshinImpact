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
      //��������
      int base_attack = 10;//����������
      float base_defense = 0.1;//����������
      int base_hp = 100;//����Ѫ��
      //��������
      int extra_attack = 0;//���⹥����
      float extra_defense = 0;//���������
      int extra_hp = 0;//����Ѫ��

      string name; //��������
      string weapon; //��������
      float element[8] = { 0,0,0,0,0,0,0,0 }; //�������������ϵ�Ԫ�أ�0��Ϊû�У�1��Ϊ��

      int exp = 20;//����ֵ
      int max_exp = 100;//�����ֵ

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
	//������
      int attack = 10;

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

      bool isFog1Enabled000 = true;  // �����Ƿ�����
      bool isFog2Enabled000 = true;
      bool isFog3Enabled000 = true;
      bool isFog4Enabled000 = true;

      TreasureChest* getchest1() { return chest1; }
      TreasureChest* getchest2() { return chest2; }

    void set_New_Teleport_position(const Vec2& position) { New_Teleport_position = position; } 
    static cocos2d::Scene* createScene();

    virtual bool init(); //��ʼ�����������ڳ�������ʱ����

    void refreshMonster();//ˢ�¹���
    
    void characterset();//���ý�ɫ
    bool PlayerAttack(Effects* me, BasePlayer* other);
    void update(float dt);//���º�����ÿ֡����һ��
    void menuCloseCallback(cocos2d::Ref* pSender);//�˳���ť�Ļص�����
    void storeInfo(Player* sprite, int tag); //�л���ɫʱ������Ϣ
    void startDialog(string name);//��ʼ�Ի�
    bool isTeleported() {return New_Teleport_position == Vec2(0, 0); }
    Player* getcurrentplayer()
    {
          return currentPlayer;
    }
    //�洢С��ͼ����Ķ�����ܻ��޸�����


	//�ļ��洢
    void savemessage();
    void loadmessage();
    void initmessage(const char* pName);//����·��

    //�ֿ⣬����Ʒ����������
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
      //�����ɫ��Ϣ������
      PlayerInformation playerInfo[2];
      //�ٻ����˵ĺ���
      void summonEnemy(std::string name, Vec2 position);
      //�ٻ���ʱ��
      float summonTime = 0;
      //��ǰ�ϴ��Ľ�ɫ
      int team;

      bool isrefresh = true;

      bool isFog1Enabled = true;  // �����Ƿ�����
      bool isFog2Enabled = true;
      bool isFog3Enabled = true;
      bool isFog4Enabled = true;

      //�洢ɾ���Ķ��������
      Enemy* enemygroup_delete[20];
      //��ǰ���
      Player* currentPlayer;

      //�洢��ҵ�����
      //Player* playergroup[20];
      //�洢���˵�����
      Enemy* enemygroup[20];

      newCamera* myCamera;
      Player* sprite;
      TMXTiledMap* map;
      mapManager* mapManager;
      Vec2 New_Teleport_position;
      int a = 0;

      //�洢��ǰ�ӵ������vector
      vector<string> task;//����������
      //���������
      vector<int> task_progress;//���������
      //�Ի���npc����
      string dialogername;
      int dialoging = 0;//�Ի��Ľ���
      //�Ƿ�����ѡ��
      bool ischoose = false;
      int choose = 0;
      // ����ˢ��״̬
      std::set<std::pair<int,int>> monsterRefreshState;

      //��ǰ�Ի���npc����
      string currentdialogername;
	  string currentrealdialogername;

      //һ��map���洢�Ի������֣�string���ͶԻ����ݣ�string�����飬����˳����жԻ�����ǰһ����Ϊkey����һ����Ϊvalue
      std::map<string, vector<string>> dialog_map;
      //std::map<string, string> dialog_map;

};

#endif // __HELLOWORLD_SCENE_H__
