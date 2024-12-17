// bag.h
#ifndef __BAG_NODE_H__
#define __BAG_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player/Player.h"
#include"vector"
USING_NS_CC;

struct WeaponInfo {
    Sprite* sprite;   // ָ�� Sprite ��ָ��
    std::string name; // ��������
    int damage;       // �����˺�
    std::string type; // �������ͣ����� "sword", "bow"
};


class Player;  // ǰ������ Player ��

class Bag : public Node {
public:

    virtual bool init() override;  // ���س�ʼ������
    void toggleBag();  // ��ʾ/���ر���
    void togglelayer(LayerColor* colorLayer, LayerColor* colorLayer2,Sprite* small_grid1, Sprite* small_grid2);//��ʾ/����װ������
    void Bag::toggletext(Label* label_equipped, Label* label_introduce, Sprite* equipmentSprite);//������ʾ����
    std::vector<WeaponInfo> weapons;
    int is_Fill[4][4];
    bool is_openbag;
    int is_1weaponGridEmpty;
    int is_2weaponGridEmpty;
    int select_x, select_y;
    //Player* getPlayer(Player* player) { return  player; }
    void getPlayer(Player* player){m_player=player;}
    void getPlayerplace();
    
    CREATE_FUNC(Bag);
private:
    Player* m_player;  // ���� Player �����ָ��
    Sprite* m_bagSprite;  // ��������
    // ����״̬�洢
    std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyMap;
};


#endif // BAG_H#pragma once#pragma once
