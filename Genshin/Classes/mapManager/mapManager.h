#ifndef __MAPMANAGER_NODE_H__
#define __MAPMANAGER_NODE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "newCamera.h"

USING_NS_CC;

class mapManager : public Node
{
public:
    virtual bool init();//初始化函数，会在场景创建时调用
    void update(float dt);//更新函数，每帧调用一次
    CREATE_FUNC(mapManager);//创建一个mapManager对象

    bool isCollision(Vec2 position);

private:
      // 地图参数
      Size visibleSize;
      Size mapSize;
      Vec2 spritePos; // 相机精灵的坐标
      Vec2 spritePosChange; // 相机相对于中心图块的坐标
      Size tileSize; // 地图块大小

      TMXTiledMap* map_00_00; // 中
      TMXTiledMap* map_00_01; // 左
      TMXTiledMap* map_01_00; // 下
      TMXTiledMap* map_00_10; // 右
      TMXTiledMap* map_10_00; // 上
      TMXTiledMap* map_10_01; // 左上
      TMXTiledMap* map_01_01; // 左下
      TMXTiledMap* map_10_10; // 右上
      TMXTiledMap* map_01_10; // 右下

      int initialMapMiddleX;
      int mapMiddleX;
      int initialMapMiddleY;
      int mapMiddleY;

      void MapCreate(TMXTiledMap*& map,int i,int j, Vec2 middlePos);
      void MapReset(Vec2 middlePos);
};

#endif 
