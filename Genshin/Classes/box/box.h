#pragma once
#ifndef __TREASURE_CHEST_H__
#define __TREASURE_CHEST_H__

#include "cocos2d.h"

USING_NS_CC;

class TreasureChest : public Node {
public:
    // 创建 TreasureChest 实例
    static TreasureChest* create(const std::string& closedImage, const std::string& openedImage);

    // 打开宝箱
    void open();

    // 关闭宝箱
    void close();

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
