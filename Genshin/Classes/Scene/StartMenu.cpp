#include"StartMenu.h"
#include"HelloWorldScene.h"

Scene* StartMenu::createScene()
{
      return StartMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
      printf("Error while loading: %s\n", filename);
      printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
      // ������ʼ��
      if (!Scene::init()) { return false; }
      visibleSize = Director::getInstance()->getVisibleSize();
      origin = Director::getInstance()->getVisibleOrigin();
      loading = 0;
      // ���ε��뱳��ͼ��
      backGround1 = Sprite::create("Scene//StartMenu//LoginAnimation_1_01.png");
      initialLoginIamge(backGround1, true);
      addChild(backGround1, 1);
      backGround2 = Sprite::create("Scene/StartMenu/LoginAnimation_1_02.png");
      initialLoginIamge(backGround2, true);
      addChild(backGround2, 2);
      backGround3 = Sprite::create("Scene/StartMenu/LoginAnimation_2_00.png");
      initialLoginIamge(backGround3, true);
      addChild(backGround3, 3);
      backGround4 = Sprite::create("Scene/StartMenu/LoginAnimation_3_00.png");
      initialLoginIamge(backGround4, false);
      addChild(backGround4, 4);

      // �������ͼ�ʱ��
      pauseTime = 0;
      scheduleUpdate();

      // ���ض���֡
      isLoginSceneAnimation = 0;
      isLoginAnimation = 0;
      Size size = backGround3->getContentSize();
      for (int i = 0; i <= 48; ++i) {
	    char initial[40];
	    sprintf(initial, "Scene/StartMenu/LoginAnimation_2_%02d.png", i);
	    auto frame = SpriteFrame::create(initial, Rect(0, 0, size.width, size.height));
	    loginSceneAnimation.pushBack(frame);
      }
      for (int i = 0; i <= 10; ++i) {
	    char initial[40];
	    sprintf(initial, "Scene/StartMenu/LoginAnimation_3_%02d.png", i);
	    auto frame = SpriteFrame::create(initial, Rect(0, 0, size.width, size.height));
	    loginAnimation.pushBack(frame);
      }

      // ������⴦��ʼ��Ϸ
      auto listener = EventListenerTouchOneByOne::create();
      listener->onTouchBegan = CC_CALLBACK_2(StartMenu::enterGame, this);
      _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

      return true;
}


void StartMenu::menuCloseCallback(Ref* scene)
{
      Director::getInstance()->end();
}
bool StartMenu::enterGame(Touch* touch, Event* event)
{
      log("1");
      if (isLoginSceneAnimation == 2)
	    isLoginAnimation = 1;
      return true;
}

// ���ñ���
void StartMenu::initialLoginIamge(Sprite* background, bool tag)
{
      // ���ñ���ͼƬ��λ��
      background->setAnchorPoint(Vec2(0.5, 1));
      background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
      // ���ñ���ͼƬ�Ĵ�С
      Size size = background->getContentSize();
      float scaleX = visibleSize.width / size.width;
      float scaleY = visibleSize.height / size.height;
      float scaleTimes = (scaleX < scaleY ? scaleX : scaleY);
      background->setScale(scaleTimes, scaleTimes);
      // ���ñ���ͼƬ���ɼ�
      background->setVisible(false);
      background->setTag(0);

      if (!tag)
      {
	    return; // ��������һ�ű���������Ҫ����͸����
      }

      // ������͸��������Ϊ0��ʵ�ֽ���
      background->setOpacity(0);
}

void StartMenu::update(float delta)
{
      // ���뽥������1
      if (backGround1->getTag() == 0) {
	    backGround1->setVisible(true);
	    SpriteFadeInOut::fadeIn(backGround1, 4);
	    return;
      }
      if (pauseTime < 60) // ��ʾͼƬ1  60֡
      {
	    ++pauseTime;
	    return;
      }
      if (backGround1->getTag() == 1) {
	    SpriteFadeInOut::fadeOut(backGround1, 4);
	    return;
      }
      // ���뽥������2
      if (backGround2->getTag() == 0) {
	    backGround1->setVisible(false);
	    backGround2->setVisible(true);
	    SpriteFadeInOut::fadeIn(backGround2, 4);
	    return;
      }
      if (pauseTime < 120) // ��ʾͼƬ2  60֡
      {
	    ++pauseTime;
	    return;
      }
      if (backGround2->getTag() == 1) {
	    SpriteFadeInOut::fadeOut(backGround2, 4);
	    return;
      }
      // ���뽥������3
      if (backGround3->getTag() == 0) {
	    backGround2->setVisible(false);
	    backGround3->setVisible(true);
	    isLoginSceneAnimation = 1;
	    SpriteFadeInOut::fadeIn(backGround3, 40);
	    return;
      }

      // ��ʼ���Ŷ���
      if (isLoginSceneAnimation == 1)
      {
	    backGround3->runAction(Animate::create(Animation::createWithSpriteFrames(loginSceneAnimation, 0.05f)));
	    isLoginSceneAnimation = 2;
	    return;
      }
      if (isLoginAnimation == 1)
      {
	    backGround3->setVisible(false);
	    backGround4->setVisible(true);
	    backGround4->runAction(Animate::create(Animation::createWithSpriteFrames(loginAnimation, 0.05f)));
	    isLoginAnimation = 2;
	    return;
      }
      if (isLoginAnimation == 2) {
	    ++loading;
      }
      if (loading > 30) {
	    Director::getInstance()->replaceScene(HelloWorld::createScene());
      }
}
bool SpriteFadeInOut::fadeIn(Sprite* sprite, GLbyte rate) {
      // ��龫���Ƿ���ڣ�����Ǳ�ڵĿ�ָ�����
      if (!sprite)
	    return false;

      sprite->setVisible(true); // ��ʾ����
      auto opacity = sprite->getOpacity();
      if (opacity < 180) {
	    opacity = std::min(opacity + rate * 2, 255); // ��ֹ���
	    sprite->setOpacity(opacity);
	    log("Fade In (Fast) Successfuly");
      }
      if (opacity < 200) {
	    opacity = std::min(opacity + rate, 255); // ��ֹ���
	    sprite->setOpacity(opacity);
	    log("Fade In Successfuly");
      }
      else if (opacity < 255)
      {
	    opacity = std::min(opacity + rate / 2, 255); // ��ֹ���
	    sprite->setOpacity(opacity);
	    log("Fade In (Slow) Successfuly");
      }
      else {
	    sprite->setTag(1); // ���ñ�ǩΪ1
	    return true; // �������
      }
      return false;
}

bool SpriteFadeInOut::fadeOut(Sprite* sprite, GLbyte rate) {
      // ��龫���Ƿ����
      if (!sprite)
	    return false;

      auto opacity = sprite->getOpacity();
      if (opacity > 75) {
	    opacity = std::max(opacity - rate * 2, 0); // ��ֹ���
	    sprite->setOpacity(opacity);
	    log("Fade Out (Fast) Successfuly");
      }
      if (opacity > 55) {
	    opacity = std::max(opacity - rate, 0); // ��ֹ���
	    sprite->setOpacity(opacity);
	    log("Fade Out Successfuly");
      }
      else if (opacity > 0)
      {
	    opacity = std::max(opacity - rate / 2, 0); // ��ֹ���
	    sprite->setOpacity(opacity);
	    log("Fade Out (Slow) Successfuly");
      }
      else {
	    sprite->setTag(2); // ���ñ�ǩΪ2
	    return true; // �������
      }
      return false;
}