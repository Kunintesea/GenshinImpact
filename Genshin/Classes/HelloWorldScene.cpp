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

	//创建一个菜单。如果Menu类型的对象比如MenuItemImage想要正常工作，必须要放在Menu中
	auto menu = Menu::create(closeItem, NULL);//创建一个菜单，里面放了一个按钮
	menu->setPosition(Vec2::ZERO);//设置菜单的位置，这里是原点
	this->addChild(menu, 1);//将菜单添加到场景中，1表示z轴的位置，z轴的位置越大，显示的优先级越高


	//初始化剑士
	sprite = Player::create();
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
		//设置精灵的位置，这里是屏幕的中心
	 // sprite->setPosition(Vec2::ZERO);
         sprite->setPosition(Vec2(500,500));
		sprite->setName("Me");//设置标签
		//将精灵添加到场景中
        this->addChild(sprite, 0);
	currentPlayer = sprite;
    }

    Size bodySize = sprite->getBody()->getContentSize();
    //初始化剑士
    playerInfo[0].name = "swordPlayer";
    playerInfo[0].weapon = "Me/Saber/Weapon/sword.png";

    //初始化弓箭手
    playerInfo[1].name = "bowPlayer";
    playerInfo[1].weapon = "Me/Saber/Weapon/bow1.png";




    //加一只地狱犬，在人物上方
    summonEnemy("HellDog", Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 3 + origin.y + 100));
    //加一只冰蝙蝠
    summonEnemy("Bat_Ice", Vec2(visibleSize.width / 3 + origin.x + 100, visibleSize.height / 3 + origin.y + 100));

    //加一只火蝙蝠
    summonEnemy("Bat_Fire", Vec2(visibleSize.width / 3 + origin.x + 200, visibleSize.height / 3 + origin.y + 100));

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
      //键盘事件监听：人物切换，1 -- 剑士，2 -- 弓箭手
      auto exchangeListener = EventListenerKeyboard::create();
      //按键按下时调用
      exchangeListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	    {
		  if (keyCode == EventKeyboard::KeyCode::KEY_1) //剑士
		  {
			this->storeInfo(sprite, 1);
			sprite->m_name = playerInfo[0].name;
			sprite->m_weapon->setTexture(playerInfo[0].weapon);
			sprite->m_body->stopAllActions();
		  }
		  else if (keyCode == EventKeyboard::KeyCode::KEY_2) //弓箭手
		  {
			this->storeInfo(sprite, 0);
			sprite->m_name = playerInfo[1].name;
			sprite->m_weapon->setTexture(playerInfo[1].weapon);
			sprite->m_body->stopAllActions();
		  }
	    };
      Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exchangeListener, sprite);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级



      return true;//返回true表示初始化成功
}

//更新函数，每帧调用一次
void HelloWorld::update(float dt)
{
      //让player每秒掉血
      Player* player = (Player*)this->getChildByName("Me");

      if (New_Teleport_position != Vec2::ZERO)
      {
	    sprite->setPosition(New_Teleport_position);
	    newCamera->bindPlayer(sprite);
	    New_Teleport_position = Vec2::ZERO;
      }
	    //每一帧检测玩家有没有打到敌人，以及敌人有没有打到玩家
	//玩家是否打到敌人，传入玩家特效和敌人
	    for (int j = 0; j < 20; j++)
	    {
		  if (currentPlayer->m_effect[j] != nullptr)
		  {
			//搜索敌人
			for (int k = 0; k < 20; k++)
			{
			      if (enemygroup[k] != nullptr)
			      {
				    //如果打到了
				    if (!enemygroup[k]->isDead && PlayerAttack(currentPlayer->m_effect[j], enemygroup[k]) && currentPlayer->m_effect_index[j][k] > 0)
				    {
					  //对应位置计数减1
					  currentPlayer->m_effect_index[j][k] -= 1;

					  //对敌人调用Hurt函数，数值为攻击力，类型为effect里面的damage_type
					  enemygroup[k]->hurt(int(currentPlayer->getAttack() * currentPlayer->m_effect[j]->damage_rate), currentPlayer->m_effect[j]->damage_type, true);
					  //如果打死了
					  if (enemygroup[k]->isDead)
					  {
						//玩家能量增加
						//currentPlayer->getmp() += 10;


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


	    for (int i = 0; i < 20; i++)
	    {
		  if (enemygroup[i] != nullptr)
		  {
			//搜索特效，检测敌人是否打到玩家
			for (int j = 0; j < 20; j++)
			{
			      if (enemygroup[i]->m_effect[j] != nullptr)
			      {
				    //如果打到了
				    if (PlayerAttack(enemygroup[i]->m_effect[j], currentPlayer) && enemygroup[i]->m_effect_index[j][0] > 0)
				    {
					  //对应位置计数减1
					  enemygroup[i]->m_effect_index[j][0] -= 1;
					  //对玩家调用Hurt函数，数值为攻击力，类型为effect里面的damage_type
					  currentPlayer->hurt(int(enemygroup[i]->getAttack() * enemygroup[i]->m_effect[j]->damage_rate), enemygroup[i]->m_effect[j]->damage_type, true);
				    }
			      }
			      else
			      {
				    break;
			      }
			}


			//检索玩家，只要玩家靠近敌人，敌人就往玩家身上走（leisure=false）
			//如果玩家在敌人的攻击范围(500)内
			if (currentPlayer->getPosition().distance(enemygroup[i]->getPosition()) < 1000)
			{
			      //敌人往玩家身上走
			      enemygroup[i]->leisure = false;
			      //如果是地狱犬
			      if (enemygroup[i]->getNaming() == "HellDog")
			      {
				    //1技能没冷却的话就放1技能
				    //if (enemygroup[i]->)
			      }

			}
			else if (currentPlayer->getPosition().distance(enemygroup[i]->getPosition()) > 2000)
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
bool HelloWorld::PlayerAttack(Effects* me, BasePlayer* other)
      {


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
void HelloWorld::storeInfo(Player* sprite, int tag)
{
      //0 -- 从剑士切换为弓箭手，要储存剑士的信息
      //1 -- 从弓箭手切换为战士，要储存弓箭手的信息
      for (int i = 0; i < 8; i++)
      {
	    playerInfo[tag].element[i] = sprite->m_element[i];
      }
      playerInfo[tag].shield = sprite->m_shield;
      playerInfo[tag].hp = sprite->m_hp;
      playerInfo[tag].max_hp = sprite->m_max_hp;
      playerInfo[tag].mp = sprite->m_mp;
      playerInfo[tag].max_mp = sprite->m_max_mp;
      for (int i = 0; i < 8; i++)
      {
	    playerInfo[tag].isElement[i] = sprite->m_isElement[i];
      }
      playerInfo[tag].defense_origin = sprite->m_defense_origin;
      playerInfo[tag].defense = sprite->m_defense;
      playerInfo[tag].level = sprite->level;

      playerInfo[tag].superconductivity = sprite->m_superconductivity;
      playerInfo[tag].E_CD = sprite->m_E_CD;
      playerInfo[tag].Q_CD = sprite->m_Q_CD;
      playerInfo[tag].max_E_CD = sprite->m_max_E_CD;
      playerInfo[tag].max_Q_CD = sprite->m_max_Q_CD;

      for (int i = 0; i < 2; i++)
      {
	    playerInfo[tag].element_sprite[i] = sprite->m_element_sprite[i];
	    playerInfo[tag].element_sprite_type[i] = sprite->m_element_sprite_type[i];
      }

      for (int i = 0; i < 8; i++)
      {
	    playerInfo[tag].immune[i] = sprite->m_immune[i];
      }

      for (int i = 0; i < 99; i++)
      {
	    playerInfo[tag].statement[i] = sprite->m_statement[i];
	    playerInfo[tag].statement_time[i] = sprite->m_statement_time[i];
      }
}




void HelloWorld::summonEnemy(std::string name, Vec2 position)
{
      //根据名字召唤敌人
      Enemy* enemy = Enemy::create();
      if (enemy == nullptr)
      {
	    problemLoading("'HelloWorld.png'");
      }
      else
      {
	    //设置精灵的位置，这里以玩家为中心，的一圈
	    enemy->setPosition(Vec2(position.x, position.y));
	    enemy->setName("Enemy");//设置标签
	    this->addChild(enemy, 0);
	    //加入到敌人数组
	    for (int i = 0; i < 20; i++)
	    {
		  if (enemygroup[i] == nullptr)
		  {
			enemygroup[i] = enemy;
			enemy->naming(name);//给敌人命名
			enemy->initData();
			break;
		  }
	    }
      }
}
