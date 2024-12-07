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
    virtual bool init();//初始化函数，会在场景创建时调用
    void update(float dt);//更新函数，每帧调用一次
    CREATE_FUNC(newCamera);//创建一个Player对象
    // 设置个方向的移动
    void moveSet(int x, int y, float delta);
    // 设置绑定角色
    void bindPlayer(Player* player);


    // 返回待加入世界的相机（初始化用）
    Camera* getCamera() { return camera; }
    // 返回相机相对于世界（0，0）的偏移量
    Vec2 getCameraPostionChange() { return cameraSprite->getPosition() + initialOffset; }
private:
      // 初始化相机偏移量
      Vec2 initialOffset;
    // 相机精灵
      Sprite* cameraSprite;
    // 世界大小
      Size visibleSize;
      Vec2 origin;
    // 相机本身
      Camera* camera;
    // 绑定的角色
      Player* player;
    // 相机移动相关参数
      Vec2 cameraMove;
      Vec2 cameraBackMove;
      const float cameraOffsetTime = 0.3f;
      const bool isFollowedDynamicly = true;
      int maxOffSet;
};

#endif 
