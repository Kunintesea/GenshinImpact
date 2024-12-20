#ifndef __MAPMANAGER_NODE_H__
#define __MAPMANAGER_NODE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "newCamera.h"

USING_NS_CC;

// ������Ƭλ�õĽṹ��
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
    virtual bool init();//��ʼ�����������ڳ�������ʱ����
    void update(float dt);//���º�����ÿ֡����һ��
    CREATE_FUNC(mapManager);//����һ��mapManager����
    float getTileSize() { return tileSize.width; }

    bool isCollision(Vec2 position);
    int isInteract(Vec2 position);
    std::set<int> isInteraction(Vec2 Position);

    int getBackgroundTag(Vec2 position);
private:
      // ��ͼ����
      Size visibleSize;
      Size mapSize;
      Vec2 spritePos; // ������������
      Vec2 spritePosChange; // ������������ͼ�������
      Size tileSize; // ��ͼ���С
      // �洢��ǰ͸����������Ƭ����
      std::set<TilePos> currentTransparentTiles;

      // �������飬����BFS
      const int dx[4] = { -1, 1, 0, 0 };
      const int dy[4] = { 0, 0, -1, 1 };

      // ��������Ƿ�����Ч��Χ��
      bool isValidPosition(int x, int y) {
            return x >= 0 && x < 120 && y >= 0 && y < 120;
      }

      // BFSѰ�����ڵ�͸����Ƭ
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
