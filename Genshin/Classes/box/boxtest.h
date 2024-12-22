#pragma once
#ifndef __TREASURE_BOX_H__
#define __TREASURE_BOX_H__

#include "cocos2d.h"
#include "Player/Enemy.h"

USING_NS_CC;

class Treasurebox : public Enemy {
public:
    // ���� Treasurebox ʵ��
    static Treasurebox* create(const std::string& closedImage, const std::string& openedImage);

    // �򿪱���
    void open();

    // �رձ���
    void close();

    void update(float t);

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
#pragma once
