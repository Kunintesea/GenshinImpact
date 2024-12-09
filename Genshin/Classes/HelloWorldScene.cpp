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

	// 地图
	map = TMXTiledMap::create("map1//map-un.tmx");
	// map->setScale(0.1f);
	this->addChild(map, 0);

	//添加一个菜单项，点击关闭的按钮可以退出程序
	//添加一个“关闭”图标来退出程序。MenuItemImage表面这个按钮是一个图片按钮
	//在这里，create的参数分别是：两个图片，一个是正常状态下的图片，一个是选中状态下的图片；第三个参数是一个回调函数，表示点击这个按钮时会调用这个函数
    auto closeItem = MenuItemImage::create(
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
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;//visibleSize.width是屏幕的宽度,origin.x是原点的x坐标，getContentSize().width是closeItem的宽度
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));//设置位置
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
		sprite->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 3 + origin.y));
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
	
      this->addChild(newCamera->getCamera());
      this->addChild(newCamera);
	  sprite->getCamera(newCamera);



	  //让player的伤害数字绑定到场景
	  for (int i = 0; i < 20; i++)
	  {
		  this->addChild(sprite->m_damage_label[i]);
		  this->addChild(sprite->m_element_label[i]);
	  }




      return true;//返回true表示初始化成功
}

//更新函数，每帧调用一次
void HelloWorld::update(float dt)
{
	//让player每秒掉血
	Player* player = (Player*)this->getChildByName("Me");


	
}





void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->end();//关闭游戏场景并退出应用程序
	//跳转场景到StartMenu
	Director::getInstance()->replaceScene(StartMenu::createScene());

}
