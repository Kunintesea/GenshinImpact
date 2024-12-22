#ifndef __MAPSCENE_SCENE_H__
#define __MAPSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "mapManager\mapManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

class MapScene : public cocos2d::Scene
{
private:
      Size visibleSize;
      Vec2 origin;
      float tiledSize;

      Sprite* Head;
      Sprite* mainMap;
      Sprite* close;

      Sprite* Teleport_Waypoint_1;
      Sprite* Teleport_Waypoint_selected_1;
      Sprite* Teleport_Waypoint_2;
      Sprite* Teleport_Waypoint_selected_2;
      Sprite* Teleport_Waypoint_3;
      Sprite* Teleport_Waypoint_selected_3;
      Sprite* Teleport_Waypoint_4;
      Sprite* Teleport_Waypoint_selected_4;

      Sprite* Teleport_1;
      Sprite* Teleport_2;
      Sprite* Teleport_3;
      Sprite* Teleport_4;

      Sprite* Teleport_selected;
      Sprite* Teleport_non_selected;

      Sprite* fogOverlay1; // 迷雾覆盖层
      Sprite* fogOverlay2;
      Sprite* fogOverlay3;
      Sprite* fogOverlay4;


      Vec2 AnchorPos;
      Vec2 playerPosition;
      Vec2 mapLeftDownPos;
      Vec2 mapLeftDownPosMove;

      std::function<void(const Vec2&)> NewPositionCallback;
      std::function<bool(int i)> getFogCallBack;
      std::function<void(int i)> setFogCallBack;

      // 触摸监听
      bool onTouchBegan(Touch* touch, Event* event);
      void onTouchMoved(Touch* touch, Event* event);
      void onTouchEnded(Touch* touch, Event* event);
      // 滚轮监听
      void onMouseScroll(Event* event);
      void onMouseMove(Event* event);

      void recover(Vec2 touchLocation);
      void recover();
public:
      static cocos2d::Scene* createScene();
      virtual bool init();


      Vec2 getposition1() { return Teleport_Waypoint_1->getPosition(); }
      Vec2 getposition2() { return Teleport_Waypoint_2->getPosition(); }
      Vec2 getposition3() { return Teleport_Waypoint_3->getPosition(); }
      Vec2 getposition4() { return Teleport_Waypoint_4->getPosition(); }

      float gettiledSize() { return tiledSize; }

      // 事件回调函数
      void menuCloseCallback(cocos2d::Ref* scene);

      // 每帧更新函数
      void update(float delta);

      // implement the "static create()" method manually
      CREATE_FUNC(MapScene);


      //virtual void update(float delta) override;
      void toggleFog1();
      void toggleFog2();
      void toggleFog3();
      void toggleFog4();

      // 重载乘法运算符，使其能够直接用于 Vec2 类型
      friend Vec2 operator*(const Vec2& lhs, const Size& rhs);
};


#endif // __MAPSCENE_SCENE_H__
