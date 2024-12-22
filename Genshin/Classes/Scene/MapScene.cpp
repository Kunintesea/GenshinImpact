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
      // ������ʼ��
      if (!Scene::init()) { return false; }
      visibleSize = Director::getInstance()->getVisibleSize();
      origin = Director::getInstance()->getVisibleOrigin();

      // ��ȡ Player ����
      Vec2 playerPosition = Director::getInstance()->getRunningScene()->getChildByName("Me")->getPosition();
      tiledSize = ((mapManager*)Director::getInstance()->getRunningScene()->getChildByName("mapManager"))->getTileSize();
      // ��ȡ���� Player ����ĺ���
      auto helloWorld = static_cast<HelloWorld*>(Director::getInstance()->getRunningScene());
      NewPositionCallback = [helloWorld](const Vec2& position) {
            helloWorld->set_New_Teleport_position(position);
            };
      setFogCallBack = [helloWorld](int i) {
            helloWorld->setFogEnabled(i);
            };
      getFogCallBack = [helloWorld](int i) {
            return helloWorld->getFogEnabled(i);
            };

      NewPositionCallback(Vec2::ZERO);
      // ��ȡ��ͼ���С
      float tiledSize = ((mapManager*)Director::getInstance()->getRunningScene()->getChildByName("mapManager"))->getTileSize();

      // ������ͼ
      mainMap = Sprite::create("map//main-map.png");
      // ��������ڵ�ͼ��λ��
      AnchorPos = Vec2(Vec2(
            1280.0 / 4800 + playerPosition.x / (600.0f * tiledSize),
            2240.0f / 3840 + playerPosition.y / (480.0f * tiledSize)));

      // ���õ�ͼê����λ��
      auto temp = mainMap->getContentSize();
      mainMap->setAnchorPoint(AnchorPos);
      mainMap->setTag(1);
      this->setPosition(visibleSize / 2);
      this->addChild(mainMap, 0);

      // ���õ�ͼ���½�λ��
      mapLeftDownPos = -Vec2(AnchorPos * mainMap->getContentSize());
      mapLeftDownPosMove = Vec2::ZERO;

      // �����ɫͷ��
      Head = Sprite::create("Me//Saber//head.png");
      // Head->setPosition(visibleSize / 2)
      Head->setPosition(mapLeftDownPos + AnchorPos * mainMap->getContentSize());
      this->addChild(Head, 1);

      // ���봫��ê��
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
      
      
      // ��ʼ�������ǲ�
      fogOverlay1 = Sprite::create("map//fog.png"); // �滻Ϊ����ͼƬ·��
      fogOverlay1->setContentSize(mainMap->getContentSize() / 2);
      fogOverlay1->setPosition(Teleport_Waypoint_1->getPosition());
      fogOverlay1->setOpacity(250); // ����͸���ȣ�0~255��
      Teleport_Waypoint_1->addChild(fogOverlay1, 2); // ���������ǲ�Ĳ㼶���ڵ�ͼ
      //isFog1Enabled = false;

      fogOverlay2 = Sprite::create("map//fog.png"); // �滻Ϊ����ͼƬ·��
      fogOverlay2->setContentSize(mainMap->getContentSize() / 1.5);
      fogOverlay2->setPosition(Teleport_Waypoint_2->getPosition() / 3.5);
      fogOverlay2->setOpacity(250); // ����͸���ȣ�0~255��
      Teleport_Waypoint_2->addChild(fogOverlay2, 2); // ���������ǲ�Ĳ㼶���ڵ�ͼ
      //isFog2Enabled = false;

      fogOverlay3 = Sprite::create("map//fog.png"); // �滻Ϊ����ͼƬ·��
      fogOverlay3->setContentSize(mainMap->getContentSize() / 2);
      fogOverlay3->setPosition(Teleport_Waypoint_3->getPosition() / 4.5);
      fogOverlay3->setOpacity(250); // ����͸���ȣ�0~255��
      Teleport_Waypoint_3->addChild(fogOverlay3, 2); // ���������ǲ�Ĳ㼶���ڵ�ͼ
      //isFog3Enabled = false;

      fogOverlay4 = Sprite::create("map//fog.png"); // �滻Ϊ����ͼƬ·��
      fogOverlay4->setContentSize(mainMap->getContentSize() / 1.5);
      fogOverlay4->setPosition(Teleport_Waypoint_4->getPosition() / 4);
      fogOverlay4->setOpacity(250); // ����͸���ȣ�0~255��
      Teleport_Waypoint_4->addChild(fogOverlay4, 2); // ���������ǲ�Ĳ㼶���ڵ�ͼ
      //isFog4Enabled = false;
      // ���봫�ͽ���
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

      // ���봫��ѡ��
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


      this->scheduleUpdate();

      // �����ͼ�رհ���
      close = Sprite::create("map//close.png");
      close->setScale(0.25f);
      close->setAnchorPoint(Vec2(1, 1));
      close->setPosition(visibleSize / 2 - Size(20,20));
      close->setTag(2);
      close->setVisible(false);
      this->addChild(close, 2);

      // ��괥������
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

      // �������ƶ�����
      auto _mouseListener = EventListenerMouse::create();
      _mouseListener->onMouseMove = CC_CALLBACK_1(MapScene::onMouseMove, this);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, Teleport_non_selected);

      // ���ּ���
      auto mouseListener = EventListenerMouse::create();
      mouseListener->onMouseScroll = CC_CALLBACK_1(MapScene::onMouseScroll, this);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, mainMap);

      // ���̼���
      auto keyboardListener = EventListenerKeyboard::create();
      keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
                  if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||
                        keyCode == EventKeyboard::KeyCode::KEY_M) {
                        Director::getInstance()->popScene();
                  }
            };
      _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

      keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
            if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||
                  keyCode == EventKeyboard::KeyCode::KEY_M) {
                  Director::getInstance()->popScene();
            }
            //else if (keyCode == EventKeyboard::KeyCode::KEY_F) { // ��F���л�����
            //      toggleFog1();
            //}
            };

      return true;
}

// ��괥������
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
                  //������˹ر�
                  log("Get the close!");
                  return true;
            }
      }
      else {
            //������˵�ͼ
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
            // ���Ƶ�ͼ�ƶ���Χ
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

      // ������˹ر�
      if (target->getTag() == 2 && close->isVisible()) {
            if (targetRect.containsPoint(touchLocation)) {
		  // ������˹ر�
		  log("Get the Sprite!");
                  recover();
		  return;
	    }
      }
      
      // ������˴���ê��
      if (target->getTag() == 11) {
            if (targetRect.containsPoint(touchLocation))
                  // ������˴���ê��1
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
                  // ������˴���ê��2
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
                  // ������˴���ê��3
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
                  // ������˴���ê��4
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
                  // ������˴���ѡ��
                  if (Teleport_1->isVisible()){
                        log("Get the Teleport Option!");
                        NewPositionCallback(Vec2(7.5313f, 29.6080f)*tiledSize);
                        Director::getInstance()->popScene();
                  }
                  else if (Teleport_2->isVisible()) {
			log("Get the Teleport Option!");
			NewPositionCallback(Vec2(34.1026f, -153.1133f) * tiledSize);
			Director::getInstance()->popScene();
		  }
		  else if (Teleport_3->isVisible()) {
			log("Get the Teleport Option!");
			NewPositionCallback(Vec2(294.7156f, -136.0031f) * tiledSize);
			Director::getInstance()->popScene();
		  }
                  else if (Teleport_4->isVisible()) {
                        log("Get the Teleport Option!");
                        NewPositionCallback(Vec2(289.301f, 77.8734) * tiledSize);
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
      // �����ڴ���ѡ��ɼ�ʱ�Ž����ж�
      if (Teleport_1->isVisible() || Teleport_2->isVisible() || Teleport_3->isVisible() || Teleport_4->isVisible()) {
            if (targetRect.containsPoint(touchLocation)) {
                  // ������˴���ѡ��1
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

      // ��ȡ��ǰ���ű���
      float currentScale = mainMap->getScale();

      // ���ݹ��ֹ�������������ű���
      float newScale = currentScale - scrollY * 0.02f;

      // �������ű����ķ�Χ
      newScale = std::max(0.8f, std::min(newScale, 1.25f));

      // �����µ����ű���
      mainMap->setScale(newScale);
      Head->setScale(newScale);

      // ���¼������½�λ��
      // mapLeftDownPos = - AnchorPos * mainMap->getContentSize() * (newScale);

      // ���¼��㴫��ê��λ��
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
void MapScene::update(float delta) {
      //log("Get the close!");
      if (fogOverlay1 && !getFogCallBack(1)) {
            fogOverlay1->setVisible(false); // ����״̬��������
      }
      if (fogOverlay2 && !getFogCallBack(2)) {
            fogOverlay2->setVisible(false); // ����״̬��������
      }
      if (fogOverlay3 && !getFogCallBack(3)) {
            fogOverlay3->setVisible(false); // ����״̬��������
      }
      if (fogOverlay4 && !getFogCallBack(4)) {
            fogOverlay4->setVisible(false); // ����״̬��������
      }
}


void MapScene::toggleFog1() {
      log("drddddddddddddd1111111111111111");
      setFogCallBack(1);
}

void MapScene::toggleFog2() {
      log("drddddddddddddd222222222222211");
      setFogCallBack(2);
}

void MapScene::toggleFog3() {
      log("ddddddddddddddd33333333333333");
      setFogCallBack(3);
}

void MapScene::toggleFog4() {
      log("dddddddddddddddd44444444444444");
      setFogCallBack(4);
}



void MapScene::recover(Vec2 touchLocation) {
      // �ָ�����ê��Ĵ�С
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
      // �ָ�����ê��Ĵ�С
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