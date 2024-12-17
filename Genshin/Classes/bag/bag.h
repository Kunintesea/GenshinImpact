// bag.h
#ifndef __BAG_NODE_H__
#define __BAG_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player/Player.h"
#include"vector"
USING_NS_CC;

struct WeaponInfo {
    Sprite* sprite;   // 指向 Sprite 的指针
    std::string name; // 武器名称
    int damage;       // 武器伤害
    std::string type; // 武器类型，例如 "sword", "bow"
};


class Player;  // 前向声明 Player 类

class Bag : public Node {
public:

    virtual bool init() override;  // 重载初始化方法
    void toggleBag();  // 显示/隐藏背包
    void togglelayer(LayerColor* colorLayer, LayerColor* colorLayer2,Sprite* small_grid1, Sprite* small_grid2);//显示/隐藏装备介绍
    void Bag::toggletext(Label* label_equipped, Label* label_introduce, Sprite* equipmentSprite);//隐藏显示文字
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
    Player* m_player;  // 持有 Player 对象的指针
    Sprite* m_bagSprite;  // 背包精灵
    // 按键状态存储
    std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyMap;
};


#endif // BAG_H#pragma once#pragma once
