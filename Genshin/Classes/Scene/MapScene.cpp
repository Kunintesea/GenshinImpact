#include"MapScene.h"
#include"HelloWorldScene.h"

Scene* MapScene::createScene()
{
      return MapScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
      printf("Error while loading: %s\n", filename);
      printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
      // 场景初始化
      if (!Scene::init()) { return false; }
      visibleSize = Director::getInstance()->getVisibleSize();
      origin = Director::getInstance()->getVisibleOrigin();

      // 获取 Player 坐标
      Vec2 playerPosition = Director::getInstance()->getRunningScene()->getChildByName("Me")->getPosition();
      // 获取更新 Player 坐标的函数
      auto helloWorld = static_cast<HelloWorld*>(Director::getInstance()->getRunningScene());
      NewPositionCallback = [helloWorld](const Vec2& position) {
            helloWorld->set_New_Teleport_position(position);
            };
      NewPositionCallback(Vec2::ZERO);
      // 获取地图块大小
      float tiledSize = ((mapManager*)Director::getInstance()->getRunningScene()->getChildByName("mapManager"))->getTileSize();

      // 导入大地图
      mainMap = Sprite::create("map//main-map.png");
      // 人物相对于地图的位置
      AnchorPos = Vec2(Vec2(
            1280.0 / 4800 + playerPosition.x / (600.0f * tiledSize),
            2240.0f / 3840 + playerPosition.y / (480.0f * tiledSize)));

      // 设置地图锚点与位置
      auto temp = mainMap->getContentSize();
      mainMap->setAnchorPoint(AnchorPos);
      mainMap->setTag(1);
      this->setPosition(visibleSize / 2);
      this->addChild(mainMap, 0);

      // 设置地图左下角位置
      mapLeftDownPos = -Vec2(AnchorPos * mainMap->getContentSize());
      mapLeftDownPosMove = Vec2::ZERO;

      // 导入角色头像
      Head = Sprite::create("Me//Saber//head.png");
      // Head->setPosition(visibleSize / 2)
      Head->setPosition(mapLeftDownPos + AnchorPos * mainMap->getContentSize());
      this->addChild(Head, 1);

      // 导入传送锚点
      Teleport_Waypoint_1 = Sprite::create("map//Teleport Waypoint.png");
      Teleport_Waypoint_selected_1 = Sprite::create("map//Teleport Waypoint_selected.png");
      Teleport_Waypoint_1->setPosition(mapLeftDownPos + 
            Vec2(1338.0f / 4800, 1 - 1344.0/3840) * mainMap->getContentSize());
      Teleport_Waypoint_selected_1->setPosition(mapLeftDownPos +
            Vec2(1338.0f / 4800, 1 - 1344.0 / 3840) * mainMap->getContentSize());
      Teleport_Waypoint_1->setTag(11);
      Teleport_Waypoint_selected_1->setVisible(false);
      this->addChild(Teleport_Waypoint_1, 1);
      this->addChild(Teleport_Waypoint_selected_1, 1);

      Teleport_Waypoint_2 = Sprite::create("map//Teleport Waypoint.png");
      Teleport_Waypoint_selected_2 = Sprite::create("map//Teleport Waypoint_selected.png");
      Teleport_Waypoint_2->setPosition(mapLeftDownPos + 
	    Vec2(1562.0f/4800, 1 - 2824.0f/3840) * mainMap->getContentSize());
      Teleport_Waypoint_selected_2->setPosition(mapLeftDownPos +
            Vec2(1562.0f / 4800, 1 - 2824.0f / 3840) * mainMap->getContentSize());
      Teleport_Waypoint_2->setTag(12);
      Teleport_Waypoint_selected_2->setVisible(false);
      this->addChild(Teleport_Waypoint_2, 1);
      this->addChild(Teleport_Waypoint_selected_2, 1);

      Teleport_Waypoint_3 = Sprite::create("map//Teleport Waypoint.png");
      Teleport_Waypoint_selected_3 = Sprite::create("map//Teleport Waypoint_selected.png");
      Teleport_Waypoint_3->setPosition(mapLeftDownPos +
            Vec2(3626.0f / 4800, 1- 2688.0f / 3840) * mainMap->getContentSize());
      Teleport_Waypoint_selected_3->setPosition(mapLeftDownPos +
            Vec2(3626.0f / 4800, 1 - 2688.0f / 3840) * mainMap->getContentSize());
      Teleport_Waypoint_3->setTag(13);
      Teleport_Waypoint_selected_3->setVisible(false);
      this->addChild(Teleport_Waypoint_3, 1);
      this->addChild(Teleport_Waypoint_selected_3, 1);

      Teleport_Waypoint_4 = Sprite::create("map//Teleport Waypoint.png");
      Teleport_Waypoint_selected_4 = Sprite::create("map//Teleport Waypoint_selected.png");
      Teleport_Waypoint_4->setPosition(mapLeftDownPos +
	    Vec2(3578.0f / 4800, 1 - 976.0f / 3840) * mainMap->getContentSize());
      Teleport_Waypoint_selected_4->setPosition(mapLeftDownPos +
	    Vec2(3578.0f / 4800, 1 - 976.0f / 3840) * mainMap->getContentSize());
      Teleport_Waypoint_4->setTag(14);
      Teleport_Waypoint_selected_4->setVisible(false);
      this->addChild(Teleport_Waypoint_4, 1);
      this->addChild(Teleport_Waypoint_selected_4, 1);

      // 导入传送界面
      Teleport_1 = Sprite::create("map//Teleport_1.png");
      Teleport_1->setAnchorPoint(Vec2(1.0f, 0.0f));
      Teleport_1->setPosition(Vec2(visibleSize.width / 2, - visibleSize.height / 2));
      Teleport_1->setScale(visibleSize.height / Teleport_1->getContentSize().height);
      Teleport_1->setVisible(false);
      this->addChild(Teleport_1, 2);

      Teleport_2 = Sprite::create("map//Teleport_2.png");
      Teleport_2->setAnchorPoint(Vec2(1.0f, 0.0f));
      Teleport_2->setPosition(Vec2(visibleSize.width / 2, - visibleSize.height / 2));
      Teleport_2->setScale(visibleSize.height / Teleport_2->getContentSize().height);
      Teleport_2->setVisible(false);
      this->addChild(Teleport_2, 2);

      Teleport_3 = Sprite::create("map//Teleport_3.png");
      Teleport_3->setAnchorPoint(Vec2(1.0f, 0.0f));
      Teleport_3->setPosition(Vec2(visibleSize.width / 2, - visibleSize.height / 2));
      Teleport_3->setScale(visibleSize.height / Teleport_3->getContentSize().height);
      Teleport_3->setVisible(false);
      this->addChild(Teleport_3, 2);
           
      Teleport_4 = Sprite::create("map//Teleport_4.png");
      Teleport_4->setAnchorPoint(Vec2(1.0f, 0.0f));
      Teleport_4->setPosition(Vec2(visibleSize.width / 2, - visibleSize.height / 2));
      Teleport_4->setScale(visibleSize.height / Teleport_4->getContentSize().height);
      Teleport_4->setVisible(false);
      this->addChild(Teleport_4, 2);

      // 导入传送选项
      Teleport_selected = Sprite::create("map//Teleport_selected.png");
      Teleport_selected->setPosition(Vec2(visibleSize.width / 2 - Teleport_1->getContentSize().width / 2, - visibleSize.height / 2 + Teleport_selected->getContentSize().height / 2 + 20));
      Teleport_non_selected = Sprite::create("map//Teleport_non_selected.png");
      Teleport_non_selected->setPosition(Vec2(visibleSize.width / 2 - Teleport_1->getContentSize().width / 2, - visibleSize.height / 2 + Teleport_non_selected->getContentSize().height / 2 + 20));
      Teleport_selected->setVisible(false);
      Teleport_non_selected->setVisible(false);
      Teleport_selected->setTag(21);
      Teleport_non_selected->setTag(22);
      this->addChild(Teleport_selected, 2);
      this->addChild(Teleport_non_selected, 2);


      // 导入地图关闭按键
      close = Sprite::create("map//close.png");
      close->setScale(0.25f);
      close->setAnchorPoint(Vec2(1, 1));
      close->setPosition(visibleSize / 2 - Size(20,20));
      close->setTag(2);
      close->setVisible(false);
      this->addChild(close, 2);

      // 鼠标触摸监听
      auto listener = EventListenerTouchOneByOne::create();
      listener->onTouchBegan = CC_CALLBACK_2(MapScene::onTouchBegan, this);
      listener->onTouchMoved = CC_CALLBACK_2(MapScene::onTouchMoved, this);
      listener->onTouchEnded = CC_CALLBACK_2(MapScene::onTouchEnded, this);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mainMap);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), close);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Teleport_Waypoint_1);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Teleport_Waypoint_2);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Teleport_Waypoint_3);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Teleport_Waypoint_4);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Teleport_selected);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), Teleport_non_selected);

      // 添加鼠标移动监听
      auto _mouseListener = EventListenerMouse::create();
      _mouseListener->onMouseMove = CC_CALLBACK_1(MapScene::onMouseMove, this);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, Teleport_non_selected);

      // 滚轮监听
      auto mouseListener = EventListenerMouse::create();
      mouseListener->onMouseScroll = CC_CALLBACK_1(MapScene::onMouseScroll, this);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, mainMap);

      // 键盘监听
      auto keyboardListener = EventListenerKeyboard::create();
      keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
                  if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||
                        keyCode == EventKeyboard::KeyCode::KEY_M) {
                        Director::getInstance()->popScene();
                  }
            };
      _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

      return true;
}

// 鼠标触摸监听
bool MapScene::onTouchBegan(Touch* touch, Event* event){
      Vec2 touchLocation = touch->getLocation() - visibleSize / 2;
      auto target = (event->getCurrentTarget());
      Rect targetRect(
            target->getPositionX() - target->getContentSize().width / 2,
            target->getPositionY() - target->getContentSize().height / 2,
            target->getContentSize().width,
            target->getContentSize().height
      );

      recover(touchLocation);

      if (target->getTag() == 2) {
            if (targetRect.containsPoint(touchLocation)) {
                  //点击到了关闭
                  log("Get the close!");
                  return true;
            }
      }
      else {
            //点击到了地图
            log("Get the Map!");
            return true;
      }
      return false;
}
void MapScene::onTouchMoved(Touch* touch, Event* event){
      Vec2 moveVec = touch->getDelta();
      auto target = (event->getCurrentTarget());
      if (target->getTag() == 1) {
            Vec2 oldSpritePos = target->getPosition();
            Vec2 newSpritePos = oldSpritePos + moveVec;
            // 限制地图移动范围
            if (newSpritePos.x <= - visibleSize.width / 2 - mapLeftDownPos.x && 
                  newSpritePos.x >= visibleSize.width / 2 - (mainMap->getContentSize().width + mapLeftDownPos.x))
            {
                  mapLeftDownPosMove += Vec2(moveVec.x, 0);
                  mainMap->setPosition(mainMap->getPosition() + Vec2(moveVec.x, 0));
                  Head->setPosition(Head->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_1->setPosition(Teleport_Waypoint_1->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_selected_1->setPosition(Teleport_Waypoint_selected_1->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_2->setPosition(Teleport_Waypoint_2->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_selected_2->setPosition(Teleport_Waypoint_selected_2->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_3->setPosition(Teleport_Waypoint_3->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_selected_3->setPosition(Teleport_Waypoint_selected_3->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_4->setPosition(Teleport_Waypoint_4->getPosition() + Vec2(moveVec.x, 0));
                  Teleport_Waypoint_selected_4->setPosition(Teleport_Waypoint_selected_4->getPosition() + Vec2(moveVec.x, 0));
            }
            if (newSpritePos.y <= - visibleSize.height / 2 - mapLeftDownPos.y && 
		  newSpritePos.y >= visibleSize.height / 2 - (mainMap->getContentSize().height + mapLeftDownPos.y))
	    {
                  mapLeftDownPosMove += Vec2(0, moveVec.y);
		  mainMap->setPosition(mainMap->getPosition() + Vec2(0, moveVec.y));
		  Head->setPosition(Head->getPosition() + Vec2(0, moveVec.y));
                  Teleport_Waypoint_1->setPosition(Teleport_Waypoint_1->getPosition() + Vec2(0, moveVec.y));
                  Teleport_Waypoint_selected_1->setPosition(Teleport_Waypoint_selected_1->getPosition() + Vec2(0, moveVec.y));
                  Teleport_Waypoint_2->setPosition(Teleport_Waypoint_2->getPosition() + Vec2(0, moveVec.y));
                  Teleport_Waypoint_selected_2->setPosition(Teleport_Waypoint_selected_2->getPosition() + Vec2(0, moveVec.y));
	          Teleport_Waypoint_3->setPosition(Teleport_Waypoint_3->getPosition() + Vec2(0, moveVec.y));
                  Teleport_Waypoint_selected_3->setPosition(Teleport_Waypoint_selected_3->getPosition() + Vec2(0, moveVec.y));
		  Teleport_Waypoint_4->setPosition(Teleport_Waypoint_4->getPosition() + Vec2(0, moveVec.y));
		  Teleport_Waypoint_selected_4->setPosition(Teleport_Waypoint_selected_4->getPosition() + Vec2(0, moveVec.y));

            }
      }
}
void MapScene::onTouchEnded(Touch* touch, Event* event){
      Vec2 touchLocation = touch->getLocation() - visibleSize / 2;            
      Vec2 moveVec = touch->getLocation();
      auto target = (event->getCurrentTarget());
      Rect targetRect(
            target->getPositionX() - target->getContentSize().width / 2,
            target->getPositionY() - target->getContentSize().height / 2,
            target->getContentSize().width,
            target->getContentSize().height
      );

      // 点击到了关闭
      if (target->getTag() == 2 && close->isVisible()) {
            if (targetRect.containsPoint(touchLocation)) {
		  // 点击到了关闭
		  log("Get the Sprite!");
                  recover();
		  return;
	    }
      }
      
      // 点击到了传送锚点
      if (target->getTag() == 11) {
            if (targetRect.containsPoint(touchLocation))
                  // 点击到了传送锚点1
            {
                  log("Get the Teleport Waypoint 1!");
                  Teleport_Waypoint_selected_1->setVisible(true);
                  Teleport_Waypoint_selected_1->runAction(ScaleBy::create(0.1f, 0.9f, 0.9f));
                  close->setVisible(true);
                  Teleport_1->setVisible(true);
                  Teleport_non_selected->setVisible(true);
                  return;
            }
      }
      else if (target->getTag() == 12) {
            if (targetRect.containsPoint(touchLocation)) {
                  // 点击到了传送锚点2
                  log("Get the Teleport Waypoint 2!");
                  Teleport_Waypoint_selected_2->setVisible(true);
                  Teleport_Waypoint_selected_2->runAction(ScaleBy::create(0.1f, 0.9f, 0.9f));
                  close->setVisible(true);
                  Teleport_2->setVisible(true);
                  Teleport_non_selected->setVisible(true);
                  return;
            }
      }
      else if (target->getTag() == 13) {
            if (targetRect.containsPoint(touchLocation)) {
                  // 点击到了传送锚点3
                  log("Get the Teleport Waypoint 3!");
                  Teleport_Waypoint_selected_3->setVisible(true);
                  Teleport_Waypoint_selected_3->runAction(ScaleBy::create(0.1f, 0.9f, 0.9f));
                  close->setVisible(true);
                  Teleport_3->setVisible(true);
                  Teleport_non_selected->setVisible(true);
                  return;
            }
      }
      else if (target->getTag() == 14) {
            if (targetRect.containsPoint(touchLocation)) {
                  // 点击到了传送锚点4
                  log("Get the Teleport Waypoint 4!");
                  Teleport_Waypoint_selected_4->setVisible(true);
                  Teleport_Waypoint_selected_4->runAction(ScaleBy::create(0.1f, 0.9f, 0.9f));
                  close->setVisible(true);
                  Teleport_4->setVisible(true);
                  Teleport_non_selected->setVisible(true);
                  return;
            }
      }
      else if (target->getTag() == 22)
      {
            if (targetRect.containsPoint(touchLocation)) {
                  // 点击到了传送选项
                  if (Teleport_1->isVisible()){
                        log("Get the Teleport Option!");
                        NewPositionCallback(Vec2(233, 916));
                        Director::getInstance()->popScene();
                  }
                  else if (Teleport_2->isVisible()) {
			log("Get the Teleport Option!");
			//NewPositionCallback(Vec2(1560.0f, 2820.0f));
			Director::getInstance()->popScene();
		  }
		  else if (Teleport_3->isVisible()) {
			log("Get the Teleport Option!");
			//NewPositionCallback(Vec2(3620.0f, 2680.0f));
			Director::getInstance()->popScene();
		  }
                  else if (Teleport_4->isVisible()) {
                        log("Get the Teleport Option!");
                        //NewPositionCallback(Vec2(3580.0f, 980.0f));
                        Director::getInstance()->popScene();
                  }
            }
      }
}
void MapScene::onMouseMove(Event* event) {
      EventMouse* mousePosition = dynamic_cast<EventMouse*>(event);
      Vec2 touchLocation = Vec2(mousePosition->getCursorX(), mousePosition->getCursorY()) - visibleSize / 2;
      auto target = (event->getCurrentTarget());
      Rect targetRect(
            target->getPositionX() - target->getContentSize().width / 2,
            target->getPositionY() - target->getContentSize().height / 2,
            target->getContentSize().width,
            target->getContentSize().height
      );
      // 仅仅在传送选项可见时才进行判断
      if (Teleport_1->isVisible() || Teleport_2->isVisible() || Teleport_3->isVisible() || Teleport_4->isVisible()) {
            if (targetRect.containsPoint(touchLocation)) {
                  // 点击到了传送选项1
                  log("Get the Teleport Option 1!");
                  Teleport_selected->setVisible(true);
                  Teleport_non_selected->setVisible(false);
                  NewPositionCallback(Vec2(600.0f, 480.0f));
            }
            else
            {
                  Teleport_selected->setVisible(false);
                  Teleport_non_selected->setVisible(true);
            }
      }
}
void MapScene::onMouseScroll(Event* event){
      EventMouse* mouseevent = (EventMouse*)event;
      float scrollY = mouseevent->getScrollY();

      // 获取当前缩放比例
      float currentScale = mainMap->getScale();

      // 根据滚轮滚动方向调整缩放比例
      float newScale = currentScale - scrollY * 0.02f;

      // 限制缩放比例的范围
      newScale = std::max(0.8f, std::min(newScale, 1.25f));

      // 设置新的缩放比例
      mainMap->setScale(newScale);
      Head->setScale(newScale);

      // 重新计算左下角位置
      // mapLeftDownPos = - AnchorPos * mainMap->getContentSize() * (newScale);

      // 重新计算传送锚点位置
      Teleport_Waypoint_1->setScale(newScale);
      Teleport_Waypoint_1->setPosition(mapLeftDownPos * (newScale)+ mapLeftDownPosMove +
            Vec2(1338.0f / 4800, 1 - 1344.0 / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_selected_1->setScale(newScale);
      Teleport_Waypoint_selected_1->setPosition(mapLeftDownPos * (newScale) + mapLeftDownPosMove +
	    Vec2(1338.0f / 4800, 1 - 1344.0 / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_2->setScale(newScale);
      Teleport_Waypoint_2->setPosition(mapLeftDownPos * (newScale) + mapLeftDownPosMove +
	    Vec2(1562.0f / 4800, 1 - 2824.0f / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_selected_2->setScale(newScale);
      Teleport_Waypoint_selected_2->setPosition(mapLeftDownPos * (newScale)+ mapLeftDownPosMove +
            Vec2(1562.0f / 4800, 1 - 2824.0f / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_3->setScale(newScale);
      Teleport_Waypoint_3->setPosition(mapLeftDownPos * (newScale)+ mapLeftDownPosMove +
	    Vec2(3626.0f / 4800, 1 - 2688.0f / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_selected_3->setScale(newScale);
      Teleport_Waypoint_selected_3->setPosition(mapLeftDownPos * (newScale)+ mapLeftDownPosMove +
	    Vec2(3626.0f / 4800, 1 - 2688.0f / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_4->setScale(newScale);
      Teleport_Waypoint_4->setPosition(mapLeftDownPos * (newScale)+ mapLeftDownPosMove +
            Vec2(3578.0f / 4800, 1 - 976.0f / 3840) * mainMap->getContentSize() * newScale);
      Teleport_Waypoint_selected_4->setScale(newScale);
      Teleport_Waypoint_selected_4->setPosition(mapLeftDownPos * (newScale)+ mapLeftDownPosMove +
	    Vec2(3578.0f / 4800, 1 - 976.0f / 3840) * mainMap->getContentSize() * newScale);
}

void MapScene::recover(Vec2 touchLocation) {
      // 恢复传送锚点的大小
      if (Teleport_Waypoint_selected_1->isVisible()
            && touchLocation.x < visibleSize.width / 2 - Teleport_1->getContentSize().width)
      {
            Teleport_Waypoint_selected_1->setVisible(false);
            Teleport_Waypoint_selected_1->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_1->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
      if (Teleport_Waypoint_selected_2->isVisible()
            && touchLocation.x < visibleSize.width / 2 - Teleport_2->getContentSize().width)
      {
            Teleport_Waypoint_selected_2->setVisible(false);
            Teleport_Waypoint_selected_2->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_2->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
      if (Teleport_Waypoint_selected_3->isVisible()
            && touchLocation.x < visibleSize.width / 2 - Teleport_3->getContentSize().width)
      {
            Teleport_Waypoint_selected_3->setVisible(false);
            Teleport_Waypoint_selected_3->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_3->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
      if (Teleport_Waypoint_selected_4->isVisible()
           && touchLocation.x < visibleSize.width / 2 - Teleport_4->getContentSize().width)
      {
            Teleport_Waypoint_selected_4->setVisible(false);
            Teleport_Waypoint_selected_4->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_4->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
}

void MapScene::recover() {
      // 恢复传送锚点的大小
      if (Teleport_Waypoint_selected_1->isVisible())
      {
            Teleport_Waypoint_selected_1->setVisible(false);
            Teleport_Waypoint_selected_1->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_1->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
      if (Teleport_Waypoint_selected_2->isVisible())
      {
            Teleport_Waypoint_selected_2->setVisible(false);
            Teleport_Waypoint_selected_2->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_2->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
      if (Teleport_Waypoint_selected_3->isVisible())
      {
            Teleport_Waypoint_selected_3->setVisible(false);
            Teleport_Waypoint_selected_3->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_3->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
      if (Teleport_Waypoint_selected_4->isVisible())
      {
            Teleport_Waypoint_selected_4->setVisible(false);
            Teleport_Waypoint_selected_4->setScale(1 / 0.9f);
            close->setVisible(false);
            Teleport_4->setVisible(false);
            Teleport_non_selected->setVisible(false);
            Teleport_selected->setVisible(false);
      }
}