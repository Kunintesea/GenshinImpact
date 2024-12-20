#ifndef __MAPMANAGER_NODE_H__
#define __MAPMANAGER_NODE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "newCamera.h"

USING_NS_CC;

// 定义瓦片位置的结构体
struct TilePos {
      int x, y;
      TilePos(int _x, int _y) : x(_x), y(_y) {}

      bool operator<(const TilePos& other) const {
            if (x != other.x) return x < other.x;
            return y < other.y;
      }
};

class mapManager : public Node
{
public:
    virtual bool init();//初始化函数，会在场景创建时调用
    void update(float dt);//更新函数，每帧调用一次
    CREATE_FUNC(mapManager);//创建一个mapManager对象
    float getTileSize() { return tileSize.width; }

    bool isCollision(Vec2 position);
    int isInteract(Vec2 position);
    std::set<int> isInteraction(Vec2 Position);

    int getBackgroundTag(Vec2 position);
private:
      // 地图参数
      Size visibleSize;
      Size mapSize;
      Vec2 spritePos; // 相机精灵的坐标
      Vec2 spritePosChange; // 相机相对于中心图块的坐标
      Size tileSize; // 地图块大小
      // 存储当前透明的物体瓦片集合
      std::set<TilePos> currentTransparentTiles;

      // 方向数组，用于BFS
      const int dx[4] = { -1, 1, 0, 0 };
      const int dy[4] = { 0, 0, -1, 1 };

      // 检查坐标是否在有效范围内
      bool isValidPosition(int x, int y) {
            return x >= 0 && x < 120 && y >= 0 && y < 120;
      }

      // BFS寻找相邻的透明瓦片
      std::set<TilePos> findConnectedTiles(int startX, int startY);
      void setTilesOpacity(const std::set<TilePos>& tiles, GLubyte opacity);

      void isInteract(int tiledPositionX, int tiledPositionY, std::set<int>& interaction);


      TMXTiledMap* map; 
      TMXLayer* toFadeLayer;

      int initialMapMiddleX;
      int mapMiddleX;
      int initialMapMiddleY;
      int mapMiddleY;

      void MapCreate(TMXTiledMap*& map, Vec2 middlePos);
};

#endif 
