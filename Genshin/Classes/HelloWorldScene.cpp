#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Scene\StartMenu.h"

#include "Player\Player.h"

USING_NS_CC;

std::map<EventKeyboard::KeyCode, bool> keyMap;//创建一个map，用来存储按键的状态



//创建一个场景
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

//打印有用的错误信息，而不是在文件不存在时发生段错误
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//初始化函数，会在场景创建时调用
bool HelloWorld::init()
{
	//首先调用基类的初始化函数
    if ( !Scene::init() )
    {
        return false;
    }
    
    //加一个调度器
    this->scheduleUpdate();//调度器，每帧调用一次update函数

	//获取屏幕分辨率大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
	//显示偏移，用于适配不同分辨率，原点
    Vec2 origin = Director::getInstance()->getVisibleOrigin();




	//读取背景图片grass，将其不断重复铺满整个屏幕
	auto background = Sprite::create("grass.png");//创建一个精灵，背景图片是grass
	if (background == nullptr)//如果背景图片为空，就会打印错误信息
	{
		problemLoading("'grass.png'");
	}
	else
	{
		//不断循环铺满整个屏幕
		for (int i = 0; i < visibleSize.width / background->getContentSize().width + 1; i++)
		{
			for (int j = 0; j < visibleSize.height / background->getContentSize().height + 1; j++)
			{
				auto bg = Sprite::create("grass.png");//创建一个精灵，背景图片是grass
				bg->setPosition(Vec2(i * bg->getContentSize().width, j * bg->getContentSize().height));//设置背景图片的位置
				this->addChild(bg, 0);//将背景图片添加到场景中
			}
		}
	}
	//再铺一个草皮到正中央
	auto bg = Sprite::create("grass.png");//创建一个精灵，背景图片是grass
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));//设置背景图片的位置
	//设置标签
	bg->setName("Center");
	this->addChild(bg, 0);//将背景图片添加到场景中










	//添加一个菜单项，点击关闭的按钮可以退出程序
	//添加一个“关闭”图标来退出程序。MenuItemImage表面这个按钮是一个图片按钮
	//在这里，create的参数分别是：两个图片，一个是正常状态下的图片，一个是选中状态下的图片；第三个参数是一个回调函数，表示点击这个按钮时会调用这个函数
    closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//如果closeItem为空或者宽度或者高度小于等于0，就会打印错误信息
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
	//否则，设置closeItem的位置。一个图像的位置以其正中心为原点，所以这里需要考虑图片自身的宽度和高度
    else
    {
	  closeItemInitialPosition 
		= Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 -80,
		      origin.y + closeItem->getContentSize().height / 2 + 80);
		closeItem->setPosition(closeItemInitialPosition);//设置位置
    }
    closeItem->setScale(5, 5);
	//创建一个菜单。如果Menu类型的对象比如MenuItemImage想要正常工作，必须要放在Menu中
	auto menu = Menu::create(closeItem, NULL);//创建一个菜单，里面放了一个按钮
	menu->setPosition(Vec2::ZERO);//设置菜单的位置，这里是原点
	this->addChild(menu, 1);//将菜单添加到场景中，1表示z轴的位置，z轴的位置越大，显示的优先级越高

	//创建一个精灵（这里只用来显示，当图片用），显示“HelloWorld”，图层设置为1
	Player * sprite = Player::create();
	
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
		//设置精灵的位置，这里是屏幕的中心
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		sprite->setName("Me");//设置标签
		//将精灵添加到场景中
        this->addChild(sprite, 0);

    }
	

    // 创建一个相机
      newCamera = newCamera::create();
      if (newCamera == nullptr) 
      {
	    problemLoading("Fail to get camera");
      }
      newCamera->bindPlayer(sprite);
      newCamera->setAnchorPoint(Vec2(0.5f, 0.5f));
      newCamera->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
      this->addChild(newCamera->getCamera());
      this->addChild(newCamera);
	
      return true;//返回true表示初始化成功
}

//更新函数，每帧调用一次
void HelloWorld::update(float dt)
{
      // log("closeItemInitialPosition : %f %f", closeItemInitialPosition.x, closeItemInitialPosition.y);
      // log("newCamera->getCameraPostionChange() : %f %f", newCamera->getCameraPostionChange().x, newCamera->getCameraPostionChange().y);
      closeItem->setPosition(closeItemInitialPosition + 
	    newCamera->getCameraPostionChange()

	   // Vec2(static_cast<int>(std::round(newCamera->getCameraPostionChange().x)), 
		  //static_cast<int>(std::round(newCamera->getCameraPostionChange().y)))
	    );
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->end();//关闭游戏场景并退出应用程序
	//跳转场景到StartMenu
	Director::getInstance()->replaceScene(StartMenu::createScene());

}
