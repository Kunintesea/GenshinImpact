#pragma once
#ifndef __TREASURE_CHEST_H__
#define __TREASURE_CHEST_H__

#include "cocos2d.h"

USING_NS_CC;

class TreasureChest : public Node {
public:
    // ���� TreasureChest ʵ��
    static TreasureChest* create(const std::string& closedImage, const std::string& openedImage);

    // �򿪱���
    void open();

    // �رձ���
    void close();

    // ��鱦���Ƿ��
    bool isOpen() const;

protected:
    // ��ʼ������
    bool init(const std::string& closedImage, const std::string& openedImage);

    // ��ǰ����״̬���Ƿ��
    bool _isOpen;

    // ����Ĺرպʹ���ͼ·��
    std::string _closedImage;
    std::string _openedImage;

    // ����ľ���
    Sprite* _chestSprite;
};

#endif // __TREASURE_CHEST_H__
