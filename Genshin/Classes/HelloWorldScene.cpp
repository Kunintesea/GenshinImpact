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

void HelloWorld::characterset()
{
	//遍历敌人数组
	for (int i = 0; i < 20; i++)
	{
		if (enemygroup[i] != nullptr)
		{
			//给它设置一个effects
            //创建
			Effects* effect = Effects::create();
			//位置
			effect->setPosition(enemygroup[i]->getPosition());


			//绑定到场景
			this->addChild(effect);
			effect->EffectsSize(enemygroup[i]->getNaming());
			enemygroup[i]->m_effect[0] = effect;
		}
		else
		{
			break;
		}
	}
}

//初始化函数，会在场景创建时调用
bool HelloWorld::init()
{

	////加入一个namesprite，看不见的，用于存储名字。使用时候通过tag获取，检索名字以赋值
	//Namesprite = Sprite::create();
	//this->addChild(Namesprite, 0);
	//Namesprite->setName("objectName");//默认名字
	////tag为0
	//Namesprite->setTag(99);


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
    sprite = Player::create();
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
		//加入到玩家数组
		for (int i = 0; i < 20; i++)
		{
			if (playergroup[i] == nullptr)
			{
				playergroup[i] = sprite;
				break;
			}
		}

    }


	//for (int i = 0; i < 5; i++)
	//{
	//	Enemy* enemy3 = Enemy::create();
	//	if (enemy3 == nullptr)
	//	{
	//		problemLoading("'HelloWorld.png'");
	//	}
	//	else
	//	{
	//		//设置精灵的位置，这里以玩家为中心，的一圈
	//		enemy3->setPosition(Vec2(visibleSize.width / 3 + origin.x + 22 + 22 * i, visibleSize.height / 3 + origin.y));


	//		enemy3->setName("Enemy");//设置标签
	//		//将精灵添加到场景中
	//		this->addChild(enemy3, 0);
	//		//加入到敌人数组
	//		for (int i = 0; i < 20; i++)
	//		{
	//			if (enemygroup[i] == nullptr)
	//			{
	//				enemygroup[i] = enemy3;
	//				if (i % 2 == 0)
	//				{
	//					enemy3->naming("Bat_Fire");//给敌人命名
	//					enemy3->initData();
	//					break;
	//				}
	//				else
	//				{
	//					enemy3->naming("Bat_Ice");//给敌人命名
	//					enemy3->initData();
	//					break;
	//				}
	//				
	//			}
	//		}
	//	}
	//}


	//加一只地狱犬，在人物上方
	Enemy* enemy2 = Enemy::create();
	if (enemy2 == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		//设置精灵的位置，这里以玩家为中心，的一圈
		enemy2->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 3 + origin.y + 22));
		enemy2->setName("Enemy");//设置标签
		//将精灵添加到场景中
		this->addChild(enemy2, 0);
		//加入到敌人数组
		for (int i = 0; i < 20; i++)
		{
			if (enemygroup[i] == nullptr)
			{
				enemygroup[i] = enemy2;
				enemy2->naming("HellDog");//给敌人命名
				enemy2->initData();
				break;
			}
		}
	}




	// 创建地图管理器
	mapManager = mapManager::create();
	// 地图的中心应该与精灵坐标无关
	mapManager->setAnchorPoint(Vec2::ZERO);
	mapManager->setPosition(Vec2::ZERO);
	mapManager->setName("mapManager");
	this->addChild(mapManager, -1);
	

    // 创建一个相机
      newCamera = newCamera::create();
	  if (newCamera == nullptr) { problemLoading("Fail to get camera"); }
	  newCamera->setName("camera");//设置标签
	  newCamera->bindPlayer(sprite);
	
      this->addChild(newCamera->getCamera());
      this->addChild(newCamera);
	  sprite->getCamera(newCamera);



	  //让player的伤害数字绑定到场景
	  for (int i = 0; i < 20; i++)
	  {
		  this->addChild(sprite->m_damage_label[i]);
		  this->addChild(sprite->m_element_label[i]);

		  //敌人也加进来，有几个敌人就加几个
		  for (int j = 0; j < 20; j++)
		  {
			  if (enemygroup[j] != nullptr)
			  {
				  this->addChild(enemygroup[j]->m_damage_label[i]);
				  this->addChild(enemygroup[j]->m_element_label[i]);
			  }
			  else
			  {
				  break;
			  }
		  }
	  }


	  characterset();
      return true;//返回true表示初始化成功
}

//更新函数，每帧调用一次
void HelloWorld::update(float dt)
{
	//让player每秒掉血
	Player* player = (Player*)this->getChildByName("Me");
	//每一帧检测玩家有没有打到敌人，以及敌人有没有打到玩家
	//玩家是否打到敌人，传入玩家特效和敌人
	for (int i = 0; i < 20; i++)
	{
		if (playergroup[i] != nullptr)
		{
			//搜索特效
			for (int j = 0; j < 20; j++)
			{
				if (playergroup[i]->m_effect[j] != nullptr)
				{
					//搜索敌人
					for (int k = 0; k < 20; k++)
					{
						if (enemygroup[k] != nullptr)
						{
							//如果打到了
							if (!enemygroup[k]->isDead && PlayerAttack(playergroup[i]->m_effect[j], enemygroup[k]) && playergroup[i]->m_effect_index[j][k] >0)
							{
								//对应位置计数减1
								playergroup[i]->m_effect_index[j][k] -= 1;

								//对敌人调用Hurt函数，数值为攻击力，类型为effect里面的damage_type
								enemygroup[k]->hurt(int(playergroup[i]->getAttack() * playergroup[i]->m_effect[j]->damage_rate), playergroup[i]->m_effect[j]->damage_type, true);
								//如果打死了
								if (enemygroup[k]->isDead)
								{
									//玩家能量增加
									//playergroup[i]->getmp() += 10;


									//让其不可见，5秒后删除
									enemygroup[k]->setVisible(false);

									//节点交换，把这个节点放到enemygroup_delete
									for (int l = 0; l < 20; l++)
									{
										if (enemygroup_delete[l] == nullptr)
										{
											enemygroup_delete[l] = enemygroup[k];
											//删除
											enemygroup[k] = nullptr;
											break;
										}
									}
									

									//让后面的节点往前移
									for (int l = k; l < 19; l++)
									{
										if (enemygroup[l + 1] != nullptr)
										{
											enemygroup[l] = enemygroup[l + 1];
										}
										else
										{
											break;
										}

									}

									//5秒后删除enemygroup_delete中的节点
									for (int l = 0; l < 20; l++)
									{
										if (enemygroup_delete[l] != nullptr)
										{
											enemygroup_delete[l]->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([=] {this->removeChild(enemygroup_delete[l]); }), nullptr));//延时5秒后删除
											enemygroup_delete[l] = nullptr;
										}
										else
										{
											break;
										}
									}

								}

							}
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}

	
	for (int i = 0; i < 20; i++)
	{
		if (enemygroup[i] != nullptr)
		{
			//搜索特效，检测敌人是否打到玩家
			for (int j = 0; j < 20; j++)
			{
				if (enemygroup[i]->m_effect[j] != nullptr)
				{
					//搜索玩家
					for (int k = 0; k < 20; k++)
					{
						if (playergroup[k] != nullptr)
						{
							//如果打到了
							if (!enemygroup[k]->isDead &&PlayerAttack(enemygroup[i]->m_effect[j], playergroup[k]) && enemygroup[i]->m_effect_index[j][k] >0)
							{
								//对应位置计数减1
								enemygroup[i]->m_effect_index[j][k] -= 1;
								//对玩家调用Hurt函数，数值为攻击力，类型为effect里面的damage_type
								playergroup[k]->hurt(int(enemygroup[i]->getAttack()*enemygroup[i]->m_effect[j]->damage_rate), enemygroup[i]->m_effect[j]->damage_type, true);
							}
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}


			//检索玩家，只要玩家靠近敌人，敌人就往玩家身上走（leisure=false）
			for (int j = 0; j < 20; j++)
			{
				if (playergroup[j] != nullptr)
				{
					//如果玩家在敌人的攻击范围(500)内
					if (playergroup[j]->getPosition().distance(enemygroup[i]->getPosition()) < 700)
					{
						//敌人往玩家身上走
						enemygroup[i]->leisure = false;
					}
					else if (playergroup[j]->getPosition().distance(enemygroup[i]->getPosition()) > 1500)
					{
						enemygroup[i]->leisure = true;
						break;
					}
				}
				else
				{
					break;
				}
			}

		}
		else
		{
			break;
		}
	}






	
}
bool HelloWorld::PlayerAttack(Effects* me, BasePlayer* other)
{
	////设定other的m_bodyRect的包围盒，由other->m_body的位置和大小决定。坐标用整个类的，大小用m_body的
	//other->m_bodyRect = Rect(other->getPositionX() - other->getBody()->getContentSize().width / 2, other->getPositionY() - other->getBody()->getContentSize().height / 2, other->getBody()->getContentSize().width, other->getBody()->getContentSize().height);
	//float a = other->getBody()->getContentSize().width;
	////包围盒的大小等于effect的大小。位置则用整个类的坐标
	//me->effectRect = Rect(me->getPositionX()- me->effect->getContentSize().width/2, me->getPositionY() - me->effect->getContentSize().height/2, me->effect->getContentSize().width, me->effect->getContentSize().height);
	//float b = me->effect->getContentSize().width;

	//获取放大倍数
	float c = me->effect->getScaleX();

	//getContentSize()只能获取图片的原始大小，如果图片被缩放了，这个函数获取的大小是缩放前的大小。因此要用getContentSize().width*getScaleX()来获取缩放后的大小
	other->m_bodyRect = Rect(other->getPositionX() - other->getBody()->getContentSize().width / 2, other->getPositionY() - other->getBody()->getContentSize().height / 2, other->getBody()->getContentSize().width * other->getBody()->getScaleX(), other->getBody()->getContentSize().height * other->getBody()->getScaleY());

	me->effectRect = Rect(me->getPositionX() - me->effect->getContentSize().width / 2, me->getPositionY() - me->effect->getContentSize().height / 2, me->effect->getContentSize().width * me->effect->getScaleX(), me->effect->getContentSize().height * me->effect->getScaleY());


	//获取玩家精灵和目标精灵的包围盒
	Rect playerRect = me->effectRect;
	//等于m_body的包围盒
	Rect targetRect = other->m_bodyRect;

	////对应位置画两个矩形便于调试
	//DrawNode* drawNode = DrawNode::create();
	//drawNode->drawRect(Vec2(playerRect.getMinX(), playerRect.getMinY()), Vec2(playerRect.getMaxX(), playerRect.getMaxY()), Color4F(1, 0, 0, 1));
	//this->addChild(drawNode, 1000);

	//DrawNode* drawNode2 = DrawNode::create();
	//drawNode2->drawRect(Vec2(targetRect.getMinX(), targetRect.getMinY()), Vec2(targetRect.getMaxX(), targetRect.getMaxY()), Color4F(1, 0, 0, 1));
	//this->addChild(drawNode2, 1000);





	// 检测两个精灵的包围盒是否相交
	if (playerRect.intersectsRect(targetRect))
	{

		return true;
	}

	return false;
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->end();//关闭游戏场景并退出应用程序
	//跳转场景到StartMenu
	Director::getInstance()->replaceScene(StartMenu::createScene());

}
