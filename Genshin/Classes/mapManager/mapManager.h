#ifndef __MAPMANAGER_NODE_H__
#define __MAPMANAGER_NODE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "newCamera.h"

USING_NS_CC;

class mapManager : public Node
{
public:
    virtual bool init();//��ʼ�����������ڳ�������ʱ����
    void update(float dt);//���º�����ÿ֡����һ��
    CREATE_FUNC(mapManager);//����һ��mapManager����

    bool isCollision(Vec2 position);

private:
      // ��ͼ����
      Size visibleSize;
      Size mapSize;
      Vec2 spritePos; // ������������
      Vec2 spritePosChange; // ������������ͼ�������
      Size tileSize; // ��ͼ���С

      TMXTiledMap* map_00_00; // ��
      TMXTiledMap* map_00_01; // ��
      TMXTiledMap* map_01_00; // ��
      TMXTiledMap* map_00_10; // ��
      TMXTiledMap* map_10_00; // ��
      TMXTiledMap* map_10_01; // ����
      TMXTiledMap* map_01_01; // ����
      TMXTiledMap* map_10_10; // ����
      TMXTiledMap* map_01_10; // ����

      int initialMapMiddleX;
      int mapMiddleX;
      int initialMapMiddleY;
      int mapMiddleY;

      void MapCreate(TMXTiledMap*& map,int i,int j, Vec2 middlePos);
      void MapReset(Vec2 middlePos);
};

#endif 
