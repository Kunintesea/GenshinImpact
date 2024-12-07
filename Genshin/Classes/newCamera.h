#ifndef __NEWCAMERA_NODE_H__
#define __NEWCAMERA_NODE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "UI/PlayerStatusUI.h"

USING_NS_CC;
class Player;

class newCamera : public Node
{
public:
    virtual bool init();//��ʼ�����������ڳ�������ʱ����
    void update(float dt);//���º�����ÿ֡����һ��
    CREATE_FUNC(newCamera);//����һ��Player����
    // ���ø�������ƶ�
    void moveSet(int x, int y, float delta);
    // ���ð󶨽�ɫ
    void bindPlayer(Player* player);


    // ���ش�����������������ʼ���ã�
    Camera* getCamera() { return camera; }
    // ���������������磨0��0����ƫ����
    Vec2 getCameraPostionChange() { return cameraSprite->getPosition() + initialOffset; }
private:
      // ��ʼ�����ƫ����
      Vec2 initialOffset;
    // �������
      Sprite* cameraSprite;
    // �����С
      Size visibleSize;
      Vec2 origin;
    // �������
      Camera* camera;
    // �󶨵Ľ�ɫ
      Player* player;
    // ����ƶ���ز���
      Vec2 cameraMove;
      Vec2 cameraBackMove;
      const float cameraOffsetTime = 0.3f;
      const bool isFollowedDynamicly = true;
      int maxOffSet;
};

#endif 
