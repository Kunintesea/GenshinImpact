#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Scene\StartMenu.h"
#include "box/box.h"
#include "Player\Player.h"
#include "box/boxtest.h"

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


      //添加背景音乐"D:\Github_Document\GenshinImpact\Genshin\Resources\Music\test.wav"并且循环播放
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/test.wav", true);


      //task_progress和task初始化
      for (int i = 0; i < 20; i++)
      {
	    task_progress.push_back(0);
	    task.push_back("");
      }
      //对dialog_map进行初始化，npc1的第一个对话为"you,get money to me!!!!!!"
      dialog_map["npc1"].push_back("you,get money to me!!!!!!");


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


    // 创建宝箱
    chest1 = TreasureChest::create("box/chest_close.png", "box/chest_open.png");
    chest2 = TreasureChest::create("box/chest_close.png", "box/chest_open.png");

    chest1->setPosition(Vec2(500, 500));
    chest2->setPosition(Vec2(-500, -500));

    chest1->setScale(3.0f);
    chest2->setScale(3.0f);

    this->addChild(chest1);
    this->addChild(chest2);


    /*// 创建宝箱
    Treasurebox* chest111 = Treasurebox::create("box/chest_close.png", "box/chest_open.png");
    Treasurebox* chest222 = Treasurebox::create("box/chest_close.png", "box/chest_open.png");

    chest111->setPosition(Vec2(500, 500));
    chest222->setPosition(Vec2(-500, -500));

    chest111->setScale(3.0f);
    chest222->setScale(3.0f);

    this->addChild(chest111);
    this->addChild(chest222);
    */



    /* 检查宝箱状态
    //if (chest1->isOpen()) {
	    CCLOG("宝箱1是打开的！");
    }
    else {
	    CCLOG("宝箱1是关闭的！");
    }*/


	sprite = Player::create();
	//查看team的数，如果是0，就是剑士，如果是1，就是弓箭手

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
	    currentPlayer = sprite;
    }

    Size bodySize = sprite->getBody()->getContentSize();
    //初始化剑士
    playerInfo[0].name = "swordPlayer";
    playerInfo[0].weapon = "Me/Saber/Weapon/sword.png";

    //初始化弓箭手
    playerInfo[1].name = "bowPlayer";
    playerInfo[1].weapon = "Me/Saber/Weapon/bow1.png";
    //读取数据
    loadmessage();



    //攻击力调味999
    //sprite->m_attack = 999;


    // 创建地图管理器
    mapManager = mapManager::create();
    // 地图的中心应该与精灵坐标无关
    mapManager->setAnchorPoint(Vec2::ZERO);
    mapManager->setPosition(Vec2::ZERO);
    mapManager->setName("mapManager");
    this->addChild(mapManager, -1);
    currentdialogername = "npc1";
	
     // 创建一个相机
	  myCamera = newCamera::create();
    if (myCamera == nullptr) { problemLoading("Fail to get camera"); }
    myCamera->setName("camera");//设置标签
    myCamera->bindPlayer(sprite);

    this->addChild(myCamera->getCamera());
    this->addChild(myCamera);
    sprite->getCamera(myCamera);

	// 雪山bossVec2(-18 * sizeWidth + 800, 18 * sizeWidth + 600)
	auto sizeWidth = -40 * mapManager->getTileSize();
	summonEnemy("HellDog", Vec2(-26 * sizeWidth + 800, 18 * sizeWidth + 600));
	//对鼠标左键进行对话监听
    auto oridinaryAttack = EventListenerMouse::create();
    oridinaryAttack->onMouseDown = [this](Event* event)
	  {
		auto mouseAttack = static_cast<EventMouse*>(event);
		if (!ischoose && mouseAttack->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT && sprite->getIsDialog())
		{
			if (dialoging == dialog_map[currentdialogername].size())
			{
				sprite->setIsDialog(false);
				dialoging = 0;
				//隐藏对话框
				myCamera->hidedialog();

				//如果是Qin_1，就要加入任务
				if (currentdialogername == "Qin_1")
				{
					task.push_back("Qin_wood");
					//任务进度
					task_progress.push_back(0);
				}
				//如果是Katheryne,就要加入任务
				if (currentdialogername == "Katheryne")
				{
					task.push_back("snow");
					//任务进度
					task_progress.push_back(0);
				}
				

			}
		      //根据map中的对话，显示对话框
		      myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
		      dialoging++;
		      //如果到了要选择的时候
		      if (currentdialogername =="npc1" && dialoging == 3)
		      {
			      ischoose = true;
		      }
			  else if (currentdialogername == "Qin" && dialoging == 4)
			  {
				  ischoose = true;
			  }
			  else if (currentdialogername == "Qin_wood" && dialoging == 2)
			  {
				  ischoose = true;
			  }
		}
	  };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oridinaryAttack, this);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级




      //让player的伤害数字绑定到场景
      for (int i = 0; i < 20; i++)
      {
	    this->addChild(sprite->m_damage_label[i]);
	    this->addChild(sprite->m_element_label[i]);

	   
      }


      characterset();
      //键盘事件监听：人物切换，1 -- 剑士，2 -- 弓箭手
      auto exchangeListener = EventListenerKeyboard::create();
      //按键按下时调用
      exchangeListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	    {
		  if (keyCode == EventKeyboard::KeyCode::KEY_1 && !sprite->isOnBoard) //剑士
		  {
			//如果没在对话
			if (sprite->getIsDialog() == false)
			{
			      team = 0;
			      this->storeInfo(sprite, 1);
			      sprite->m_name = playerInfo[0].name;
			      sprite->m_weapon->setTexture(playerInfo[0].weapon);
			      sprite->m_hp = playerInfo[0].hp;
			      sprite->m_max_hp = playerInfo[0].max_hp;
			      sprite->m_mp = playerInfo[0].mp;
			      sprite->m_max_mp = playerInfo[0].max_mp;
			      sprite->m_defense = playerInfo[0].defense;
			      sprite->m_defense_origin = playerInfo[0].defense;
			      sprite->level = playerInfo[0].level;
			      sprite->m_superconductivity = playerInfo[0].superconductivity;
			      sprite->m_E_CD = playerInfo[0].E_CD;
			      sprite->m_Q_CD = playerInfo[0].Q_CD;
			      sprite->m_max_E_CD = playerInfo[0].max_E_CD;
			      sprite->m_max_Q_CD = playerInfo[0].max_Q_CD;
			      //经验
			      sprite->m_exp = playerInfo[0].exp;
			      sprite->m_max_exp = playerInfo[0].max_exp;


			      for (int i = 0; i < 8; i++)
			      {
				    sprite->m_element[i] = playerInfo[0].element[i];
				    sprite->m_isElement[i] = playerInfo[0].isElement[i];
				    sprite->m_immune[i] = playerInfo[0].immune[i];
			      }
			      for (int i = 0; i < 99; i++)
			      {
				    //前提是两个都不为空
				    if (playerInfo[0].statement[i].name != "" && sprite->m_statement[i].name != "")
				    {
					  sprite->m_statement[i] = playerInfo[0].statement[i];
					  sprite->m_statement_time[i] = playerInfo[0].statement_time[i];
				    }
				    else
				    {
					  break;
				    }
			      }


			      sprite->m_body->stopAllActions();
			}
			else if (ischoose)
			{
				//如果是Qin_wood且拥有任务且有4个木头
				//遍历任务，查看是否有Qin_wood
				if (currentdialogername == "Qin_wood" && task.size() > 0)
				{
					for (int i = 0; i < task.size(); i++)
					{
						if (task[i] == "Qin_wood")
						{
							//如果map storage有4个木头
							if (storage["Wood"] >= 4)
							{
							      sprite->swordButtons[3].isEmpty = true;
								//任务完成
								storage["Wood"] -= 4;
								choose = 1;
								ischoose = false;
								//索引
								currentdialogername = currentdialogername + "_" + to_string(choose);
								dialoging = 0;
								myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
								dialoging++;
							}
							else
							{
								//任务未完成
								choose = 2;
								ischoose = false;
								//索引
								currentdialogername = currentdialogername + "_" + to_string(choose);
								dialoging = 0;
								myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
								dialoging++;
							}
						}
					}
				}

				else
				{
					choose = 1;
					ischoose = false;
					//索引
					currentdialogername = currentdialogername + "_" + to_string(choose);
					dialoging = 0;
					myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
					dialoging++;
				}

			     
			}

		  }
		  else if (keyCode == EventKeyboard::KeyCode::KEY_2 && !sprite->isOnBoard) //弓箭手
		  {
			//如果没在对话
			if (sprite->getIsDialog() == false)
			{
			      team = 1;
			      this->storeInfo(sprite, 0);
			      sprite->m_name = playerInfo[1].name;
			      sprite->m_weapon->setTexture(playerInfo[1].weapon);
			      sprite->m_hp = playerInfo[1].hp;
			      sprite->m_max_hp = playerInfo[1].max_hp;
			      sprite->m_mp = playerInfo[1].mp;
			      sprite->m_max_mp = playerInfo[1].max_mp;
			      sprite->m_defense = playerInfo[1].defense;
			      sprite->m_defense_origin = playerInfo[1].defense;
			      sprite->level = playerInfo[1].level;
			      sprite->m_superconductivity = playerInfo[1].superconductivity;
			      sprite->m_E_CD = playerInfo[1].E_CD;
			      sprite->m_Q_CD = playerInfo[1].Q_CD;
			      sprite->m_max_E_CD = playerInfo[1].max_E_CD;
			      sprite->m_max_Q_CD = playerInfo[1].max_Q_CD;
			      //经验
			      sprite->m_exp = playerInfo[1].exp;
			      sprite->m_max_exp = playerInfo[1].max_exp;

			      for (int i = 0; i < 8; i++)
			      {
				    sprite->m_element[i] = playerInfo[1].element[i];
				    sprite->m_isElement[i] = playerInfo[1].isElement[i];
				    sprite->m_immune[i] = playerInfo[1].immune[i];
			      }
			      for (int i = 0; i < 99; i++)
			      {
				    //前提是两个都不为空
				    if (playerInfo[1].statement[i].name != "" && sprite->m_statement[i].name != "")
				    {
					  sprite->m_statement[i] = playerInfo[1].statement[i];
					  sprite->m_statement_time[i] = playerInfo[1].statement_time[i];
				    }
				    else
				    {
					  break;
				    }
			      }

			      sprite->m_body->stopAllActions();
			}
			else if (ischoose)
			{
				choose = 2;
				ischoose = false;
				//索引
				currentdialogername = currentdialogername + "_" + to_string(choose);
				dialoging = 0;
				myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
				dialoging++;

			}
		  }
		  //X按键存储
		  else if (keyCode == EventKeyboard::KeyCode::KEY_X)
		  {
			if (sprite->getIsDialog() == false)
			{
			      savemessage();
			}
		  }
		  //Z按键读取
		  else if (keyCode == EventKeyboard::KeyCode::KEY_Z)
		  {
			if (sprite->getIsDialog() == false)
			{
			      loadmessage();
			}
		  }
	    };
      Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exchangeListener, sprite);//把监听器加入到事件分发器中，传入监听器与其绑定的对象。这里的优先级设定为精灵的优先级


      return true;//返回true表示初始化成功
}

void HelloWorld::startDialog(string name)
{
      //显示对话框
      myCamera->showdialog();
      //设置为对话状态
      sprite->setIsDialog(true);
      //读取对话
      currentdialogername = name;
	  currentrealdialogername = name;
	  dialoging = 0;
	  //假设接了Qin的任务且名字是Qin,把名字切换为Qin_wood
	  //在task中查找
	  if (name == "Qin" && task.size() > 0)
	  {
		  for (int i = 0; i < task.size(); i++)
		  {
			  if (task[i] == "Qin_wood")
			  {
				  currentdialogername = "Qin_wood";
				  break;
			  }
		  }
	  }
	  //如果是Fisherman且有任务
	  if (currentdialogername == "Fisherman" && task.size() > 0)
	  {
		  for (int i = 0; i < task.size(); i++)
		  {
			  if (task[i] == "snow" && task_progress[i] == 0)
			  {
				  task_progress[i]++;
				  currentdialogername = "Fisherman_main";
			  }
		  }
	  }


      myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
      dialoging++;
}

//更新函数，每帧调用一次
void HelloWorld::update(float dt)
{
      /*auto visibleSize = Director::getInstance()->getVisibleSize();
      Vec2 origin = Director::getInstance()->getVisibleOrigin();
      dialogmenu->setPosition(Vec2(visibleSize.width / 3 + origin.x, 100));*/
      //跟着getCameraSpritePosition()的位置更新dialogmenu
      //dialogmenu->setPosition(newCamera->getCameraSpritePosition());


      
      Player* player = (Player*)this->getChildByName("Me");

      if (New_Teleport_position != Vec2::ZERO)
      {
	    sprite->setPosition(New_Teleport_position);
	    myCamera->bindPlayer(sprite);
	    sprite->clearKeyBoardState();
	    New_Teleport_position = Vec2::ZERO;
      }
      // 刷新怪物
      refreshMonster();
	    //每一帧检测玩家有没有打到敌人，以及敌人有没有打到玩家
	//玩家是否打到敌人，传入玩家特效和敌人
	    for (int j = 0; j < 20; j++)
	    {
		  if (currentPlayer->m_effect[j] != nullptr)
		  {
			////查找effect是不是空
			//if (currentPlayer->m_effect[j]->effect == nullptr)
			//{
			//	currentPlayer->m_effect[j] = nullptr;
			//	break;
			//}

			//搜索敌人
			for (int k = 0; k < 20; k++)
			{
			      if (enemygroup[k] != nullptr)
			      {
				    //如果打到了
				    if (!enemygroup[k]->isDead && PlayerAttack(currentPlayer->m_effect[j], enemygroup[k]) && currentPlayer->m_effect_index[j][k] > 0)
				    {
					  //检测敌人名字，如果是地狱犬
					  if (enemygroup[k]->getNaming() == "HellDog")
					  {
						if (enemygroup[k]->get1CD() <= 0)
						{
						      enemygroup[k]->skillQ();
						      enemygroup[k]->set1CD();
						      //break;

						}

					  }

					  //玩家能量增加
					  currentPlayer->m_mp += 10;
					  if (currentPlayer->m_mp > currentPlayer->m_mp)
					  {
						currentPlayer->m_mp = currentPlayer->m_max_mp;
					  }

					  //对应位置计数减1
					  currentPlayer->m_effect_index[j][k] -= 1;

					  //对敌人调用Hurt函数，数值为攻击力，类型为effect里面的damage_type
					  enemygroup[k]->hurt(int(currentPlayer->getAttack() * currentPlayer->m_effect[j]->damage_rate), currentPlayer->m_effect[j]->damage_type, true);
					  //如果打死了
					  if (enemygroup[k]->isDead)
					  {

							//exp增加
						currentPlayer->m_exp += enemygroup[k]->getGainExp();
						//获得战利品
						//搜索storage，如果有就加1，没有就创建
						if (storage.find(enemygroup[k]->getNaming()) != storage.end())
						{
							storage[enemygroup[k]->getNaming()] += 1;
						}
						else
						{
							storage[enemygroup[k]->getNaming()] = 1;
						}


						//让其不可见，3秒后删除
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
						for (int l = k; l < 18; l++)
						{
						      if (enemygroup[l + 1] != nullptr)
						      {
							    enemygroup[l] = enemygroup[l + 1];
							    enemygroup[l + 1] = nullptr;
							    //对应位置计数加1
							    currentPlayer->m_effect_index[j][l] = currentPlayer->m_effect_index[j][l + 1];
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
							    enemygroup_delete[l]->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=] {this->removeChild(enemygroup_delete[l]); }), nullptr));//延时5秒后删除
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
      //只要有一个为空就返回
      if (me == nullptr || other == nullptr)
      {
	    return false;
      }


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
      //经验
      playerInfo[tag].exp = sprite->m_exp;
      playerInfo[tag].max_exp = sprite->m_max_exp;

      for (int i = 0; i < 8; i++)
      {
	    playerInfo[tag].isElement[i] = sprite->m_isElement[i];
      }
      playerInfo[tag].defense_origin = sprite->m_defense_origin;
      playerInfo[tag].defense = sprite->m_defense;
      playerInfo[tag].level = sprite->level;
      //状态
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

void HelloWorld::refreshMonster()
{
	// 获取格子尺寸
	auto tileSize = mapManager->getTileSize();
	//刷新怪物
	for (int i = 0; i < 40; ++i) {
	std:pair<int, int> pos1(std::floor(sprite->getPosition().x / tileSize) + -20 + i, std::floor(sprite->getPosition().y / tileSize));
		// 有刷新点，且该点未刷新过怪物
		if (mapManager->isRefreshMonster(sprite->getPosition() + Vec2((-20 + i) * tileSize, -20 * tileSize)) && monsterRefreshState.find(pos1) == monsterRefreshState.end())
		{
			// 根据刷新点召唤怪物
			summonEnemy("Bat_Fire", Vec2(sprite->getPosition() + Vec2((-20 + i) * tileSize, -20 * tileSize)));
			// 标记该刷新点已刷新怪物
			monsterRefreshState.insert(pos1);
		}
		std::pair<int, int> pos2(std::floor(sprite->getPosition().x / tileSize) + -20 + i, std::floor(sprite->getPosition().y / tileSize));
		if (mapManager->isRefreshMonster(sprite->getPosition() + Vec2((-20 + i) * tileSize, 20 * tileSize)) && monsterRefreshState.find(pos2) == monsterRefreshState.end())
		{
			summonEnemy("Bat_Ice", Vec2(sprite->getPosition() + Vec2((-20 + i) * tileSize, 20 * tileSize)));
			monsterRefreshState.insert(pos2);
		}
		std::pair<int, int> pos3(std::floor(sprite->getPosition().x / tileSize) + 20, std::floor(sprite->getPosition().y / tileSize) + -20 + i);
		if (mapManager->isRefreshMonster(sprite->getPosition() + Vec2(-20 * tileSize, (-20 + i) * tileSize)) && monsterRefreshState.find(pos3) == monsterRefreshState.end())
		{
			summonEnemy("Bat_Fire", Vec2(sprite->getPosition() + Vec2(-20 * tileSize, (-20 + i) * tileSize)));
			monsterRefreshState.insert(pos3);
		}
		std::pair<int, int> pos4(std::floor(sprite->getPosition().x / tileSize) + 20, std::floor(sprite->getPosition().y / tileSize) + -20 + i);
		if (mapManager->isRefreshMonster(sprite->getPosition() + Vec2(20 * tileSize, (-20 + i) * tileSize)) && monsterRefreshState.find(pos4) == monsterRefreshState.end())
		{
			summonEnemy("Bat_Ice", Vec2(sprite->getPosition() + Vec2(20 * tileSize, (-20 + i) * tileSize)));
			monsterRefreshState.insert(pos4);
		}
	}
}

void HelloWorld::summonEnemy(std::string name, Vec2 position)
{
      //根据名字召唤敌人
      Enemy* enemy = Enemy::create();
      if (enemy == nullptr)
      {
	    problemLoading("'Enemy'");
      }
      else
      {
	    //设置精灵的位置
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

			for (int j = 0; j < 20; j++)
			{
				this->addChild(enemygroup[i]->m_damage_label[j]);
				this->addChild(enemygroup[i]->m_element_label[j]);
			}

			break;
		  }
	    }
      }
	  



}

//文件存储
void HelloWorld::initmessage(const char* pName)
{
      rapidjson::Document oWriteDoc;
      oWriteDoc.SetObject();
      rapidjson::Document::AllocatorType& allocator = oWriteDoc.GetAllocator();
      rapidjson::Value oArray(rapidjson::kArrayType);

      rapidjson::StringBuffer oBuffer;
      rapidjson::Writer<rapidjson::StringBuffer> oWriter(oBuffer);
      oWriteDoc.Accept(oWriter);

      //写入
      FILE* pFile = fopen(pName, "wb+");
      if (pFile == NULL)
      {
	    log("Open File '%s' Failed.", pName);
	    return;
      }

      fputs(oBuffer.GetString(), pFile);
      fclose(pFile);

}


//存储玩家数据到本地的json文件
void HelloWorld::savemessage()
{
      //创建一个json对象
      rapidjson::Document document;
      //设置对象的类型
      document.SetObject();
      //创建一个json对象
      rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
      //创建一个json对象
      rapidjson::Value object1(rapidjson::kObjectType);
      //创建一个json对象
      rapidjson::Value object2(rapidjson::kObjectType);


      document.AddMember("swordPlayer", object1, allocator);
      document.AddMember("bowPlayer", object2, allocator);
      //创建一个json对象
      rapidjson::Value& player1 = document["swordPlayer"];
      //创建一个json对象
      rapidjson::Value& player2 = document["bowPlayer"];
      //先检测当前的玩家是哪个
      string name = currentPlayer->m_name;
      if (name == "swordPlayer")
      {
	    document.AddMember("swordPlayer", object1, allocator);//添加一个对象,名字为Player
	    player1.AddMember("name", "swordPlayer", allocator);
	    player1.AddMember("exp", currentPlayer->m_exp, allocator);
	    player1.AddMember("max_exp", currentPlayer->m_max_exp, allocator);
	    player1.AddMember("hp", currentPlayer->m_hp, allocator);
	    player1.AddMember("max_hp", currentPlayer->m_max_hp, allocator);
	    //护盾
	    player1.AddMember("shield", currentPlayer->m_shield, allocator);
	    //元素能量
	    player1.AddMember("mp", currentPlayer->m_mp, allocator);
	    player1.AddMember("max_mp", currentPlayer->m_max_mp, allocator);
	    //防御
	    player1.AddMember("defense_origin", currentPlayer->m_defense_origin, allocator);
	    player1.AddMember("defense", currentPlayer->m_defense, allocator);
	    //等级
	    player1.AddMember("level", currentPlayer->level, allocator);
	    //最大冷却时间
	    player1.AddMember("max_E_CD", currentPlayer->m_max_E_CD, allocator);
	    player1.AddMember("max_Q_CD", currentPlayer->m_max_Q_CD, allocator);
	    //基础属性
	    player1.AddMember("base_attack", currentPlayer->base_attack, allocator);
	    player1.AddMember("base_defense", currentPlayer->base_defense, allocator);
	    player1.AddMember("base_hp", currentPlayer->base_hp, allocator);
	    //额外属性
	    player1.AddMember("extra_attack", currentPlayer->extra_attack, allocator);
	    player1.AddMember("extra_defense", currentPlayer->extra_defense, allocator);
	    player1.AddMember("extra_hp", currentPlayer->extra_hp, allocator);
      }
      else if (name == "bowPlayer")
      {
	    document.AddMember("bowPlayer", object2, allocator);//添加一个对象,名字为Player
	    player2.AddMember("name", "bowPlayer", allocator);
	    player2.AddMember("exp", currentPlayer->m_exp, allocator);
	    player2.AddMember("max_exp", currentPlayer->m_max_exp, allocator);
	    player2.AddMember("hp", currentPlayer->m_hp, allocator);
	    player2.AddMember("max_hp", currentPlayer->m_max_hp, allocator);
	    //护盾
	    player2.AddMember("shield", currentPlayer->m_shield, allocator);
	    //元素能量
	    player2.AddMember("mp", currentPlayer->m_mp, allocator);
	    player2.AddMember("max_mp", currentPlayer->m_max_mp, allocator);
	    //防御
	    player2.AddMember("defense_origin", currentPlayer->m_defense_origin, allocator);
	    player2.AddMember("defense", currentPlayer->m_defense, allocator);
	    //等级
	    player2.AddMember("level", currentPlayer->level, allocator);
	    //最大冷却时间
	    player2.AddMember("max_E_CD", currentPlayer->m_max_E_CD, allocator);
	    player2.AddMember("max_Q_CD", currentPlayer->m_max_Q_CD, allocator);
	    //基础属性
	    player2.AddMember("base_attack", currentPlayer->base_attack, allocator);
	    player2.AddMember("base_defense", currentPlayer->base_defense, allocator);
	    player2.AddMember("base_hp", currentPlayer->base_hp, allocator);
	    //额外属性
	    player2.AddMember("extra_attack", currentPlayer->extra_attack, allocator);
	    player2.AddMember("extra_defense", currentPlayer->extra_defense, allocator);
	    player2.AddMember("extra_hp", currentPlayer->extra_hp, allocator);
      }





      //如果名字是swordPlayer
      for (int i = 0; i < 2; i++)
      {
	    if (playerInfo[i].name == "swordPlayer" && name != "swordPlayer")
	    {
		  //设置对象的类型
		  document.AddMember("swordPlayer", object1, allocator);//添加一个对象,名字为Player

		  player1.AddMember("name", "swordPlayer", allocator);
		  player1.AddMember("exp", playerInfo[i].exp, allocator);
		  player1.AddMember("max_exp", playerInfo[i].max_exp, allocator);
		  player1.AddMember("hp", playerInfo[i].hp, allocator);
		  player1.AddMember("max_hp", playerInfo[i].max_hp, allocator);
		  //护盾
		  player1.AddMember("shield", playerInfo[i].shield, allocator);
		  //元素能量
		  player1.AddMember("mp", playerInfo[i].mp, allocator);
		  player1.AddMember("max_mp", playerInfo[i].max_mp, allocator);
		  //防御
		  player1.AddMember("defense_origin", playerInfo[i].defense_origin, allocator);
		  player1.AddMember("defense", playerInfo[i].defense, allocator);
		  //等级
		  player1.AddMember("level", playerInfo[i].level, allocator);
		  //最大冷却时间
		  player1.AddMember("max_E_CD", playerInfo[i].max_E_CD, allocator);
		  player1.AddMember("max_Q_CD", playerInfo[i].max_Q_CD, allocator);

		  //基础属性
		  player1.AddMember("base_attack", playerInfo[i].base_attack, allocator);
		  player1.AddMember("base_defense", playerInfo[i].base_defense, allocator);
		  player1.AddMember("base_hp", playerInfo[i].base_hp, allocator);
		  //额外属性
		  player1.AddMember("extra_attack", playerInfo[i].extra_attack, allocator);
		  player1.AddMember("extra_defense", playerInfo[i].extra_defense, allocator);
		  player1.AddMember("extra_hp", playerInfo[i].extra_hp, allocator);




	    }
	    else if (playerInfo[i].name == "bowPlayer" && name != "bowPlayer")
	    {
		  //设置对象的类型
		  document.AddMember("bowPlayer", object2, allocator);//添加一个对象,名字为Player
		  player2.AddMember("name", "bowPlayer", allocator);
		  player2.AddMember("exp", playerInfo[i].exp, allocator);
		  player2.AddMember("max_exp", playerInfo[i].max_exp, allocator);
		  player2.AddMember("hp", playerInfo[i].hp, allocator);
		  player2.AddMember("max_hp", playerInfo[i].max_hp, allocator);
		  //护盾
		  player2.AddMember("shield", playerInfo[i].shield, allocator);
		  //元素能量
		  player2.AddMember("mp", playerInfo[i].mp, allocator);
		  player2.AddMember("max_mp", playerInfo[i].max_mp, allocator);
		  //防御
		  player2.AddMember("defense_origin", playerInfo[i].defense_origin, allocator);
		  player2.AddMember("defense", playerInfo[i].defense, allocator);
		  //等级
		  player2.AddMember("level", playerInfo[i].level, allocator);
		  //最大冷却时间
		  player2.AddMember("max_E_CD", playerInfo[i].max_E_CD, allocator);
		  player2.AddMember("max_Q_CD", playerInfo[i].max_Q_CD, allocator);

		  //基础属性
		  player2.AddMember("base_attack", playerInfo[i].base_attack, allocator);
		  player2.AddMember("base_defense", playerInfo[i].base_defense, allocator);
		  player2.AddMember("base_hp", playerInfo[i].base_hp, allocator);
		  //额外属性
		  player2.AddMember("extra_attack", playerInfo[i].extra_attack, allocator);
		  player2.AddMember("extra_defense", playerInfo[i].extra_defense, allocator);
		  player2.AddMember("extra_hp", playerInfo[i].extra_hp, allocator);
	    }



      }


      //存储到本地
		      //检测Data/PlayerData.json是否存在
		      //创建一个json文件流
      rapidjson::StringBuffer buffer;
      //将json对象写入json文件流
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      document.Accept(writer);
      //创建一个文件流


      //看看有没有Path下的PlayerData.json文件
      //获取当前路径
      char* path = _getcwd(NULL, 0);//_getcwd在库direct.h中
      //path回到上一级目录的Data文件夹的PlayerData.json文件
      path = _fullpath(NULL, "..\\Data\\PlayerData.json", 0);

      //打开文件
      FILE* file = fopen(path, "wb");



      //如果文件流存在
      if (file)
      {
	    //将json文件流写入文件
	    fputs(buffer.GetString(), file);
	    //关闭文件流
	    fclose(file);
      }
      //如果文件流不存在，调用initmessage函数
      else
      {
	    initmessage(path);
	    //再次打开文件
	    FILE* file = fopen(path, "wb+");
	    //将json文件流写入文件
	    fputs(buffer.GetString(), file);
	    //关闭文件流
	    fclose(file);


      }



      //创建一个json对象
      rapidjson::Document document1;
      //设置对象的类型
      document1.SetObject();
      document1.AddMember("team", team, allocator);
      document1.AddMember("isFog1Enabled000", isFog1Enabled000, allocator);
      document1.AddMember("isFog2Enabled000", isFog2Enabled000, allocator);
      document1.AddMember("isFog3Enabled000", isFog3Enabled000, allocator);
      document1.AddMember("isFog4Enabled000", isFog4Enabled000, allocator);
      //存储到本地
      rapidjson::StringBuffer buffer1;
      //将json对象写入json文件流
      rapidjson::Writer<rapidjson::StringBuffer> writer1(buffer1);
      document1.Accept(writer1);

      path = _getcwd(NULL, 0);//_getcwd在库direct.h中
      path = _fullpath(NULL, "..\\Data\\team.json", 0);
      //如果文件流存在
      file = fopen(path, "wb");
      if (file)
      {
	    //将json文件流写入文件
	    fputs(buffer1.GetString(), file);
	    //关闭文件流
	    fclose(file);
      }
      //如果文件流不存在，调用initmessage函数
      else
      {
	    initmessage(path);
	    //再次打开文件
	    file = fopen(path, "wb+");
	    //将json文件流写入文件
	    fputs(buffer1.GetString(), file);
	    //关闭文件流
	    fclose(file);
      }




	  //创建一个json对象
	  rapidjson::Document document4;
	  //设置对象的类型
	  document4.SetObject();
	  //存储map类型的storage
	  rapidjson::Value object22(rapidjson::kObjectType);
	  for (auto iter = storage.begin(); iter != storage.end(); iter++)
	  {
		  //创建一个json对象
		  rapidjson::Value key(rapidjson::kStringType);
		  //设置对象的类型
		  key.SetString(iter->first.c_str(), iter->first.size(), allocator);
		  //创建一个json对象
		  rapidjson::Value value(rapidjson::kNumberType);
		  //设置对象的类型
		  value.SetInt(iter->second);
		  //添加到object中
		  object22.AddMember(key, value, allocator);
	  }
	  //添加到document4中
	  document4.AddMember("storage", object22, allocator);


	  //存储到本地
	  rapidjson::StringBuffer buffer4;
	  //将json对象写入json文件流
	  rapidjson::Writer<rapidjson::StringBuffer> writer4(buffer4);
	  document4.Accept(writer4);

	  path = _getcwd(NULL, 0);//_getcwd在库direct.h中
	  path = _fullpath(NULL, "..\\Data\\storage.json", 0);
	  //如果文件流存在
	  file = fopen(path, "wb");
	  if (file)
	  {
		  //将json文件流写入文件
		  fputs(buffer4.GetString(), file);
		  //关闭文件流
		  fclose(file);
	  }
	  //如果文件流不存在，调用initmessage函数
	  else
	  {
		  initmessage(path);
		  //再次打开文件
		  file = fopen(path, "wb+");
		  //将json文件流写入文件
		  fputs(buffer4.GetString(), file);
		  //关闭文件流
		  fclose(file);
	  }






      //存任务task
      //创建一个json对象
      rapidjson::Document document2;
      //设置对象的类型
      document2.SetObject();
      //存储两个vector,一个是任务名字task,一个是任务进度task_progress
      rapidjson::Value array(rapidjson::kArrayType);
      rapidjson::Value array2(rapidjson::kArrayType);
      //存储
      for (int i = 0; i < task.size(); i++)
      {
	    //创建一个json对象
	    rapidjson::Value object(rapidjson::kStringType);
	    //设置对象的类型
	    object.SetString(task[i].c_str(), task[i].size(), allocator);
	    //添加到array中
	    array.PushBack(object, allocator);
      }
      for (int i = 0; i < task_progress.size(); i++)
      {
	    //创建一个json对象
	    rapidjson::Value object(rapidjson::kNumberType);
	    //设置对象的类型
	    object.SetInt(task_progress[i]);
	    //添加到array2中
	    array2.PushBack(object, allocator);
      }
      //添加到document2中
      document2.AddMember("task", array, allocator);
      document2.AddMember("task_progress", array2, allocator);


      ////存储dialog_map，值和键都是string
      //rapidjson::Value object(rapidjson::kObjectType);
      //for (auto iter = dialog_map.begin(); iter != dialog_map.end(); iter++)
      //{
      //	//创建一个json对象
      //	rapidjson::Value key(rapidjson::kStringType);
      //	//设置对象的类型
      //	key.SetString(iter->first.c_str(), iter->first.size(), allocator);
      //	//创建一个json对象
      //	rapidjson::Value value(rapidjson::kStringType);
      //	//设置对象的类型
      //	value.SetString(iter->second.c_str(), iter->second.size(), allocator);
      //	//添加到object中
      //	object.AddMember(key, value, allocator);
      //}
      ////添加到document2中
      //document2.AddMember("dialog_map", object, allocator);
      //存储dialog_map，值是string类型的vector，键是string
      rapidjson::Value object(rapidjson::kObjectType);
      for (auto iter = dialog_map.begin(); iter != dialog_map.end(); iter++)
      {
	    //创建一个json对象
	    rapidjson::Value key(rapidjson::kStringType);
	    //设置对象的类型
	    key.SetString(iter->first.c_str(), iter->first.size(), allocator);
	    //创建一个json对象
	    rapidjson::Value array(rapidjson::kArrayType);
	    for (int i = 0; i < iter->second.size(); i++)
	    {
		  //创建一个json对象
		  rapidjson::Value value(rapidjson::kStringType);
		  //设置对象的类型
		  value.SetString(iter->second[i].c_str(), iter->second[i].size(), allocator);
		  //添加到array中
		  array.PushBack(value, allocator);
	    }
	    //添加到object中
	    object.AddMember(key, array, allocator);
      }
      //添加到document2中
      document2.AddMember("dialog_map", object, allocator);


      //存储到本地
      rapidjson::StringBuffer buffer2;
      //将json对象写入json文件流
      rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
      document2.Accept(writer2);

      path = _getcwd(NULL, 0);//_getcwd在库direct.h中
      path = _fullpath(NULL, "..\\Data\\plot.json", 0);
      //如果文件流存在
      file = fopen(path, "wb");
      if (file)
      {
	    //将json文件流写入文件
	    fputs(buffer2.GetString(), file);
	    //关闭文件流
	    fclose(file);
      }
      //如果文件流不存在，调用initmessage函数
      else
      {
	    initmessage(path);
	    //再次打开文件
	    file = fopen(path, "wb+");
	    //将json文件流写入文件
	    fputs(buffer2.GetString(), file);
	    //关闭文件流
	    fclose(file);
      }




}


//读取本地json文件中的玩家数据
void HelloWorld::loadmessage()
{
      char* path = _getcwd(NULL, 0);//_getcwd在库direct.h中
      //path回到上一级目录的Data文件夹的PlayerData.json文件
      path = _fullpath(NULL, "..\\Data\\PlayerData.json", 0);

      //打开文件，没有就创建
      FILE* file = fopen(path, "rb");
      //如果文件流存在
      if (file)
      {
	    string strContent = FileUtils::getInstance()->getStringFromFile(path);//读取文件
	    //创建一个json对象
	    rapidjson::Document document;
	    //解析json对象
	    document.Parse<0>(strContent.c_str());
	    //读取数据并且赋值给玩家
	    if (document.HasMember("swordPlayer"))
	    {
		  //获取数据赋值给playerInfo中对应的变量
		  playerInfo[0].exp = document["swordPlayer"]["exp"].GetInt();
		  playerInfo[0].max_exp = document["swordPlayer"]["max_exp"].GetInt();
		  playerInfo[0].hp = document["swordPlayer"]["hp"].GetInt();
		  //playerInfo[0].max_hp = document["swordPlayer"]["max_hp"].GetInt();
		  playerInfo[0].shield = document["swordPlayer"]["shield"].GetInt();
		  playerInfo[0].mp = document["swordPlayer"]["mp"].GetInt();
		  playerInfo[0].max_mp = document["swordPlayer"]["max_mp"].GetInt();
		  //playerInfo[0].defense_origin = document["swordPlayer"]["defense_origin"].GetFloat();
		  //playerInfo[0].defense = document["swordPlayer"]["defense"].GetFloat();
		  playerInfo[0].level = document["swordPlayer"]["level"].GetInt();
		  playerInfo[0].max_E_CD = document["swordPlayer"]["max_E_CD"].GetFloat();
		  playerInfo[0].max_Q_CD = document["swordPlayer"]["max_Q_CD"].GetFloat();

		  //基础属性
		  playerInfo[0].base_attack = document["swordPlayer"]["base_attack"].GetInt();
		  playerInfo[0].base_defense = document["swordPlayer"]["base_defense"].GetFloat();
		  playerInfo[0].base_hp = document["swordPlayer"]["base_hp"].GetInt();
		  //额外属性
		  playerInfo[0].extra_attack = document["swordPlayer"]["extra_attack"].GetInt();
		  playerInfo[0].extra_defense = document["swordPlayer"]["extra_defense"].GetFloat();
		  playerInfo[0].extra_hp = document["swordPlayer"]["extra_hp"].GetInt();

		  //玩家的攻击力计算公式：base_attack*1.1*level+extra_attack
		  //玩家的防御力计算公式：base_defense*1.1*level+extra_defense
		  //玩家的生命值计算公式：base_hp*1.1*level+extra_hp
		  playerInfo[0].attack = int(double(playerInfo[0].base_attack) * 1.1 * double(playerInfo[0].level) + playerInfo[0].extra_attack);
		  playerInfo[0].defense = float(double(playerInfo[0].base_defense) * 1.1 * double(playerInfo[0].level) + playerInfo[0].extra_defense);
		  playerInfo[0].max_hp = int(double(playerInfo[0].base_hp) * 1.1 * double(playerInfo[0].level) + playerInfo[0].extra_hp);



	    }
	    if (document.HasMember("bowPlayer"))
	    {
		  //获取数据赋值给playerInfo中对应的变量
		  playerInfo[1].exp = document["bowPlayer"]["exp"].GetInt();
		  playerInfo[1].max_exp = document["bowPlayer"]["max_exp"].GetInt();
		  playerInfo[1].hp = document["bowPlayer"]["hp"].GetInt();
		  playerInfo[1].max_hp = document["bowPlayer"]["max_hp"].GetInt();
		  playerInfo[1].shield = document["bowPlayer"]["shield"].GetInt();
		  playerInfo[1].mp = document["bowPlayer"]["mp"].GetInt();
		  playerInfo[1].max_mp = document["bowPlayer"]["max_mp"].GetInt();
		  playerInfo[1].defense_origin = document["bowPlayer"]["defense_origin"].GetFloat();
		  playerInfo[1].defense = document["bowPlayer"]["defense"].GetFloat();
		  playerInfo[1].level = document["bowPlayer"]["level"].GetInt();
		  playerInfo[1].max_E_CD = document["bowPlayer"]["max_E_CD"].GetFloat();
		  playerInfo[1].max_Q_CD = document["bowPlayer"]["max_Q_CD"].GetFloat();

		  //基础属性
		  playerInfo[1].base_attack = document["bowPlayer"]["base_attack"].GetInt();
		  playerInfo[1].base_defense = document["bowPlayer"]["base_defense"].GetFloat();
		  playerInfo[1].base_hp = document["bowPlayer"]["base_hp"].GetInt();
		  //额外属性
		  playerInfo[1].extra_attack = document["bowPlayer"]["extra_attack"].GetInt();
		  playerInfo[1].extra_defense = document["bowPlayer"]["extra_defense"].GetFloat();
		  playerInfo[1].extra_hp = document["bowPlayer"]["extra_hp"].GetInt();

		  //玩家的攻击力计算公式：base_attack*1.1*level+extra_attack
		  //玩家的防御力计算公式：base_defense*1.1*level+extra_defense
		  //玩家的生命值计算公式：base_hp*1.1*level+extra_hp
		  playerInfo[1].attack = int(double(playerInfo[1].base_attack) * 1.1 * double(playerInfo[1].level) + playerInfo[1].extra_attack);
		  playerInfo[1].defense = float(double(playerInfo[1].base_defense) * 1.1 * double(playerInfo[1].level) + playerInfo[1].extra_defense);
		  playerInfo[1].max_hp = int(double(playerInfo[1].base_hp) * 1.1 * double(playerInfo[1].level) + playerInfo[1].extra_hp);
	    }


      }
      else
      {
	    initmessage(path);

      }
      //组队信息等等

      path = _getcwd(NULL, 0);//_getcwd在库direct.h中
      //path回到上一级目录的Data文件夹的PlayerData.json文件
      path = _fullpath(NULL, "..\\Data\\team.json", 0);
      file = fopen(path, "rb");
      //如果文件流存在
      if (file)
      {
	    string strContent = FileUtils::getInstance()->getStringFromFile(path);//读取文件
	    //创建一个json对象
	    rapidjson::Document document1;
	    //解析json对象
	    document1.Parse<0>(strContent.c_str());
	    //读取数据并且赋值给玩家
	    if (document1.HasMember("team"))
	    {
		  //获取数据赋值给playerInfo中对应的变量
		  team = document1["team"].GetInt();

		  isFog1Enabled000 = document1["isFog1Enabled000"].GetBool();
		  isFog2Enabled000 = document1["isFog2Enabled000"].GetBool();
		  isFog3Enabled000 = document1["isFog3Enabled000"].GetBool();
		  isFog4Enabled000 = document1["isFog4Enabled000"].GetBool();
	    }
      }
      else
      {
	    initmessage(path);
      }
      if (team == 0)
      {
	    //把当前数据替换为剑士的数据
	    sprite->m_name = playerInfo[0].name;
	    sprite->m_weapon->setTexture(playerInfo[0].weapon);
	    sprite->m_hp = playerInfo[0].hp;
	    sprite->m_max_hp = playerInfo[0].max_hp;
	    sprite->m_mp = playerInfo[0].mp;
	    sprite->m_max_mp = playerInfo[0].max_mp;
	    sprite->m_defense = playerInfo[0].defense;
	    sprite->m_defense_origin = playerInfo[0].defense;
	    sprite->level = playerInfo[0].level;
	    sprite->m_superconductivity = playerInfo[0].superconductivity;
	    sprite->m_E_CD = playerInfo[0].E_CD;
	    sprite->m_Q_CD = playerInfo[0].Q_CD;
	    sprite->m_max_E_CD = playerInfo[0].max_E_CD;
	    sprite->m_max_Q_CD = playerInfo[0].max_Q_CD;
	    //攻击力
	    sprite->m_attack = playerInfo[0].attack;


	    for (int i = 0; i < 8; i++)
	    {
		  sprite->m_element[i] = playerInfo[0].element[i];
		  sprite->m_isElement[i] = playerInfo[0].isElement[i];
		  sprite->m_immune[i] = playerInfo[0].immune[i];
	    }
	    for (int i = 0; i < 99; i++)
	    {
		  //前提是两个都不为空
		  if (playerInfo[0].statement[i].name != "" && sprite->m_statement[i].name != "")
		  {
			sprite->m_statement[i] = playerInfo[0].statement[i];
			sprite->m_statement_time[i] = playerInfo[0].statement_time[i];
		  }
		  else
		  {
			break;
		  }
	    }

      }
      else if (team == 1)
      {
	    this->storeInfo(sprite, 0);
	    sprite->m_name = playerInfo[1].name;
	    sprite->m_weapon->setTexture(playerInfo[1].weapon);
	    sprite->m_hp = playerInfo[1].hp;
	    sprite->m_max_hp = playerInfo[1].max_hp;
	    sprite->m_mp = playerInfo[1].mp;
	    sprite->m_max_mp = playerInfo[1].max_mp;
	    sprite->m_defense = playerInfo[1].defense;
	    sprite->m_defense_origin = playerInfo[1].defense;
	    sprite->level = playerInfo[1].level;
	    sprite->m_superconductivity = playerInfo[1].superconductivity;
	    sprite->m_E_CD = playerInfo[1].E_CD;
	    sprite->m_Q_CD = playerInfo[1].Q_CD;
	    sprite->m_max_E_CD = playerInfo[1].max_E_CD;
	    sprite->m_max_Q_CD = playerInfo[1].max_Q_CD;
	    //攻击力
	    sprite->m_attack = playerInfo[1].attack;
	    for (int i = 0; i < 8; i++)
	    {
		  sprite->m_element[i] = playerInfo[1].element[i];
		  sprite->m_isElement[i] = playerInfo[1].isElement[i];
		  sprite->m_immune[i] = playerInfo[1].immune[i];
	    }
	    for (int i = 0; i < 99; i++)
	    {
		  //前提是两个都不为空
		  if (playerInfo[1].statement[i].name != "" && sprite->m_statement[i].name != "")
		  {
			sprite->m_statement[i] = playerInfo[1].statement[i];
			sprite->m_statement_time[i] = playerInfo[1].statement_time[i];
		  }
		  else
		  {
			break;
		  }
	    }
      }


      //path回到上一级目录的Data文件夹的PlayerData.json文件
      path = _fullpath(NULL, "..\\Data\\plot.json", 0);
      file = fopen(path, "rb");
      //如果文件流存在
      if (file)
      {
	    string strContent = FileUtils::getInstance()->getStringFromFile(path);//读取文件
	    //创建一个json对象
	    rapidjson::Document document2;
	    //解析json对象
	    document2.Parse<0>(strContent.c_str());
	    //读取数据并且赋值给玩家
	    if (document2.HasMember("task"))
	    {
		  //获取数据赋值给vector task
		  //对每一项进行赋值
		  for (int i = 0; i < document2["task"].Size(); i++)
		  {
			task.push_back(document2["task"][i].GetString());
		  }
		  //获取数据赋值给vector task_progress
		  //对每一项进行赋值
		  for (int i = 0; i < document2["task_progress"].Size(); i++)
		  {
			task_progress.push_back(document2["task_progress"][i].GetInt());
		  }
		  //获取数据赋值给dialog_map
		  //对每一项进行赋值
		  for (auto iter = document2["dialog_map"].MemberBegin(); iter != document2["dialog_map"].MemberEnd(); iter++)
		  {
			vector<string> temp;
			for (int i = 0; i < iter->value.Size(); i++)
			{
			      temp.push_back(iter->value[i].GetString());
			}
			dialog_map[iter->name.GetString()] = temp;
		  }


	    }
      }
      else
      {
	    initmessage(path);
      }





	  path = _getcwd(NULL, 0);//_getcwd在库direct.h中
	  //path回到上一级目录的Data文件夹的PlayerData.json文件
	  path = _fullpath(NULL, "..\\Data\\storage.json", 0);
	  file = fopen(path, "rb");
	  //如果文件流存在
	  if (file)
	  {
		  string strContent = FileUtils::getInstance()->getStringFromFile(path);//读取文件
		  //创建一个json对象
		  rapidjson::Document document3;
		  //解析json对象
		  document3.Parse<0>(strContent.c_str());
		  //读取数据并且赋值给storage
		  if (document3.HasMember("storage"))
		  {
			  //获取数据赋值给map storage
			  //对每一项进行赋值
			  for (auto iter = document3["storage"].MemberBegin(); iter != document3["storage"].MemberEnd(); iter++)
			  {
				  storage[iter->name.GetString()] = iter->value.GetInt();
			  }
		  }
	  }
	  else
	  {
		  initmessage(path);
	  }

}

