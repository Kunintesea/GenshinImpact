#pragma once
#ifndef __TREASURE_BOX_H__
#define __TREASURE_BOX_H__

#include "cocos2d.h"
#include "Player/Enemy.h"

USING_NS_CC;

class Treasurebox : public Enemy {
public:
    // 创建 Treasurebox 实例
    static Treasurebox* create(const std::string& closedImage, const std::string& openedImage);

    // 打开宝箱
    void open();

    // 关闭宝箱
    void close();

    void update(float t);

    // 检查宝箱是否打开
    bool isOpen() const;

protected:
    // 初始化方法
    bool init(const std::string& closedImage, const std::string& openedImage);

    // 当前宝箱状态：是否打开
    bool _isOpen;

    // 宝箱的关闭和打开贴图路径
    std::string _closedImage;
    std::string _openedImage;

    // 宝箱的精灵
    Sprite* _chestSprite;
};

#endif // __TREASURE_CHEST_H__
#pragma once
