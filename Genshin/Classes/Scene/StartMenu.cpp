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
      // 场景初始化
      if (!Scene::init()) { return false; }
      visibleSize = Director::getInstance()->getVisibleSize();
      origin = Director::getInstance()->getVisibleOrigin();
      loading = 0;

      // 依次导入背景图层
      backGround1 = Sprite::create("Login//LoginAnimation_1_01.png");
      initialLoginIamge(backGround1, true);
      addChild(backGround1, 1);
      backGround2 = Sprite::create("Login//LoginAnimation_1_02.png");
      initialLoginIamge(backGround2, true);
      addChild(backGround2, 2);
      backGround3 = Sprite::create("Login//LoginAnimation_2_00.png");
      initialLoginIamge(backGround3, true);
      addChild(backGround3, 3);
      backGround4 = Sprite::create("Login//LoginAnimation_3_00.png");
      initialLoginIamge(backGround4, false);
      addChild(backGround4, 4);

      // 调度器和计时器
      pauseTime = 0;
      scheduleUpdate();

      // 加载动画帧
      isLoginSceneAnimation = 0;
      isLoginAnimation = 0;
      Size size = backGround3->getContentSize();
      for (int i = 0; i <= 48; ++i) {
	    char initial[40];
	    sprintf(initial, "Login//LoginAnimation_2_%02d.png", i);
	    auto frame = SpriteFrame::create(initial, Rect(0, 0, size.width, size.height));
	    loginSceneAnimation.pushBack(frame);
      }
      for (int i = 0; i <= 10; ++i) {
	    char initial[40];
	    sprintf(initial, "Login//LoginAnimation_3_%02d.png", i);
	    auto frame = SpriteFrame::create(initial, Rect(0, 0, size.width, size.height));
	    loginAnimation.pushBack(frame);
      }

      // 点击任意处开始游戏
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

// 设置背景
void StartMenu::initialLoginIamge(Sprite* background, bool tag)
{
      // 设置背景图片的位置
      background->setAnchorPoint(Vec2(0.5, 1));
      background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
      // 设置背景图片的大小
      Size size = background->getContentSize();
      float scaleX = visibleSize.width / size.width;
      float scaleY = visibleSize.height / size.height;
      float scaleTimes = (scaleX < scaleY ? scaleX : scaleY);
      background->setScale(scaleTimes, scaleTimes);
      // 设置背景图片不可见
      background->setVisible(false);
      background->setTag(0);

      if (!tag)
      {
	    return; // 如果是最后一张背景，不需要设置透明度
      }

      // 将背景透明度设置为0，实现渐入
      background->setOpacity(0);
}

void StartMenu::update(float delta)
{
      // 渐入渐出动画1
      if (backGround1->getTag() == 0) {
	    backGround1->setVisible(true);
	    SpriteFadeInOut::fadeIn(backGround1, 4);
	    return;
      }
      if (pauseTime < 60) // 显示图片1  60帧
      {
	    ++pauseTime;
	    return;
      }
      if (backGround1->getTag() == 1) {
	    SpriteFadeInOut::fadeOut(backGround1, 4);
	    return;
      }
      // 渐入渐出动画2
      if (backGround2->getTag() == 0) {
	    backGround1->setVisible(false);
	    backGround2->setVisible(true);
	    SpriteFadeInOut::fadeIn(backGround2, 4);
	    return;
      }
      if (pauseTime < 120) // 显示图片2  60帧
      {
	    ++pauseTime;
	    return;
      }
      if (backGround2->getTag() == 1) {
	    SpriteFadeInOut::fadeOut(backGround2, 4);
	    return;
      }
      // 渐入渐出动画3
      if (backGround3->getTag() == 0) {
	    backGround2->setVisible(false);
	    backGround3->setVisible(true);
	    isLoginSceneAnimation = 1;
	    SpriteFadeInOut::fadeIn(backGround3, 40);
	    return;
      }

      // 开始播放动画
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
      // 检查精灵是否存在，避免潜在的空指针错误
      if (!sprite)
	    return false;

      sprite->setVisible(true); // 显示精灵
      auto opacity = sprite->getOpacity();
      if (opacity < 180) {
	    opacity = std::min(opacity + rate * 2, 255); // 防止溢出
	    sprite->setOpacity(opacity);
	    log("Fade In (Fast) Successfuly");
      }
      if (opacity < 200) {
	    opacity = std::min(opacity + rate, 255); // 防止溢出
	    sprite->setOpacity(opacity);
	    log("Fade In Successfuly");
      }
      else if (opacity < 255)
      {
	    opacity = std::min(opacity + rate / 2, 255); // 防止溢出
	    sprite->setOpacity(opacity);
	    log("Fade In (Slow) Successfuly");
      }
      else {
	    sprite->setTag(1); // 设置标签为1
	    return true; // 渐入完成
      }
      return false;
}

bool SpriteFadeInOut::fadeOut(Sprite* sprite, GLbyte rate) {
      // 检查精灵是否存在
      if (!sprite)
	    return false;

      auto opacity = sprite->getOpacity();
      if (opacity > 75) {
	    opacity = std::max(opacity - rate * 2, 0); // 防止溢出
	    sprite->setOpacity(opacity);
	    log("Fade Out (Fast) Successfuly");
      }
      if (opacity > 55) {
	    opacity = std::max(opacity - rate, 0); // 防止溢出
	    sprite->setOpacity(opacity);
	    log("Fade Out Successfuly");
      }
      else if (opacity > 0)
      {
	    opacity = std::max(opacity - rate / 2, 0); // 防止溢出
	    sprite->setOpacity(opacity);
	    log("Fade Out (Slow) Successfuly");
      }
      else {
	    sprite->setTag(2); // 设置标签为2
	    return true; // 渐出完成
      }
      return false;
}