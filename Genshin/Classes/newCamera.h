#ifndef __NEWCAMERA_NODE_H__
#define __NEWCAMERA_NODE_H__

#include "cocos2d.h"
#include "Player/Player.h"

USING_NS_CC;

class newCamera : public Node
{
public:
      friend class Player;
      virtual bool init();//初始化函数，会在场景创建时调用
      void update(float dt);//更新函数，每帧调用一次
      CREATE_FUNC(newCamera);//创建一个Player对象
      // 设置个方向的移动
      void moveSet(int x, int y, float delta);
      // 设置绑定角色
      void bindPlayer(Player* player);
      Camera* getCamera() { return camera; }
private:
      // 相机本身
      Camera* camera;
      // 绑定的角色
      Player* player;
      // 相机移动相关参数
      Vec2 cameraMove;
      Vec2 cameraBackMove;
      const float cameraOffsetTime = 0.3;
      const bool isFollowedDynamicly = true;
      int maxOffSet;
};

#endif 
