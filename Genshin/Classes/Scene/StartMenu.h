#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

class StartMenu : public cocos2d::Scene
{
private:
      char pauseTime; // 简单变量，用于控制动画临时暂停
      char loading;

      Size visibleSize;
      Vec2 origin;

      Sprite* backGround1;
      Sprite* backGround2;
      Sprite* backGround3;
      Sprite* backGround4;
      //Sprite* backGround5; // 放登录信息等画面，但是暂时不设置

      Vector<SpriteFrame*> loginSceneAnimation;
      int isLoginSceneAnimation;
      Vector<SpriteFrame*> loginAnimation;
      int isLoginAnimation;

      void initialLoginIamge(Sprite* background, bool tag);
public:
      static cocos2d::Scene* createScene();
      virtual bool init();

      // 事件回调函数
      void menuCloseCallback(cocos2d::Ref* scene);
      bool enterGame(Touch* touch, Event* event);

      // 每帧更新函数
      void update(float delta);

      // implement the "static create()" method manually
      CREATE_FUNC(StartMenu);
};

class SpriteFadeInOut {
public:
      // 实现了精灵的淡入淡出效果
      static bool fadeIn(Sprite* sprite, GLbyte rate);
      static bool fadeOut(Sprite* sprite, GLbyte rate);
};


#endif // __HELLOWORLD_SCENE_H__
