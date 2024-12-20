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

      Vec2 AnchorPos;
      Vec2 playerPosition;
      Vec2 mapLeftDownPos;
      Vec2 mapLeftDownPosMove;
      std::function<void(const Vec2&)> NewPositionCallback;

      // ��������
      bool onTouchBegan(Touch* touch, Event* event);
      void onTouchMoved(Touch* touch, Event* event);
      void onTouchEnded(Touch* touch, Event* event);
      // ���ּ���
      void onMouseScroll(Event* event);
      void onMouseMove(Event* event);

      void recover(Vec2 touchLocation);
      void recover();
public:
      static cocos2d::Scene* createScene();
      virtual bool init();

      // �¼��ص�����
      void menuCloseCallback(cocos2d::Ref* scene);

      // ÿ֡���º���
      // void update(float delta);

      // implement the "static create()" method manually
      CREATE_FUNC(MapScene);

      // ���س˷��������ʹ���ܹ�ֱ������ Vec2 ����
      friend Vec2 operator*(const Vec2& lhs, const Size& rhs);
};


#endif // __MAPSCENE_SCENE_H__
