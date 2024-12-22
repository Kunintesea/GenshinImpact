#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Scene\StartMenu.h"
#include "box/box.h"
#include "Player\Player.h"
#include "box/boxtest.h"

USING_NS_CC;

std::map<EventKeyboard::KeyCode, bool> keyMap;//����һ��map�������洢������״̬


//����һ������
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

//��ӡ���õĴ�����Ϣ�����������ļ�������ʱ�����δ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void HelloWorld::characterset()
{
      //������������
      for (int i = 0; i < 20; i++)
      {
	    if (enemygroup[i] != nullptr)
	    {
		  //��������һ��effects
      //����
		  Effects* effect = Effects::create();
		  //λ��
		  effect->setPosition(enemygroup[i]->getPosition());


		  //�󶨵�����
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

//��ʼ�����������ڳ�������ʱ����
bool HelloWorld::init()
{


      //��ӱ�������"D:\Github_Document\GenshinImpact\Genshin\Resources\Music\test.wav"����ѭ������
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/test.wav", true);


      //task_progress��task��ʼ��
      for (int i = 0; i < 20; i++)
      {
	    task_progress.push_back(0);
	    task.push_back("");
      }
      //��dialog_map���г�ʼ����npc1�ĵ�һ���Ի�Ϊ"you,get money to me!!!!!!"
      dialog_map["npc1"].push_back("you,get money to me!!!!!!");


	//���ȵ��û���ĳ�ʼ������
    if ( !Scene::init() )
    {
        return false;
    }
    
    //��һ��������
    this->scheduleUpdate();//��������ÿ֡����һ��update����

	//��ȡ��Ļ�ֱ��ʴ�С
    auto visibleSize = Director::getInstance()->getVisibleSize();
	//��ʾƫ�ƣ��������䲻ͬ�ֱ��ʣ�ԭ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // ��������
    chest1 = TreasureChest::create("box/chest_close.png", "box/chest_open.png");
    chest2 = TreasureChest::create("box/chest_close.png", "box/chest_open.png");

    chest1->setPosition(Vec2(500, 500));
    chest2->setPosition(Vec2(-500, -500));

    chest1->setScale(3.0f);
    chest2->setScale(3.0f);

    this->addChild(chest1);
    this->addChild(chest2);


    /*// ��������
    Treasurebox* chest111 = Treasurebox::create("box/chest_close.png", "box/chest_open.png");
    Treasurebox* chest222 = Treasurebox::create("box/chest_close.png", "box/chest_open.png");

    chest111->setPosition(Vec2(500, 500));
    chest222->setPosition(Vec2(-500, -500));

    chest111->setScale(3.0f);
    chest222->setScale(3.0f);

    this->addChild(chest111);
    this->addChild(chest222);
    */



    /* ��鱦��״̬
    //if (chest1->isOpen()) {
	    CCLOG("����1�Ǵ򿪵ģ�");
    }
    else {
	    CCLOG("����1�ǹرյģ�");
    }*/


	sprite = Player::create();
	//�鿴team�����������0�����ǽ�ʿ�������1�����ǹ�����

    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
		//���þ����λ�ã���������Ļ������
	    sprite->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 3 + origin.y));
		sprite->setName("Me");//���ñ�ǩ
		//��������ӵ�������
        this->addChild(sprite, 0);
	    currentPlayer = sprite;
    }

    Size bodySize = sprite->getBody()->getContentSize();
    //��ʼ����ʿ
    playerInfo[0].name = "swordPlayer";
    playerInfo[0].weapon = "Me/Saber/Weapon/sword.png";

    //��ʼ��������
    playerInfo[1].name = "bowPlayer";
    playerInfo[1].weapon = "Me/Saber/Weapon/bow1.png";
    //��ȡ����
    loadmessage();



    //��������ζ999
    //sprite->m_attack = 999;


    // ������ͼ������
    mapManager = mapManager::create();
    // ��ͼ������Ӧ���뾫�������޹�
    mapManager->setAnchorPoint(Vec2::ZERO);
    mapManager->setPosition(Vec2::ZERO);
    mapManager->setName("mapManager");
    this->addChild(mapManager, -1);
    currentdialogername = "npc1";
	
     // ����һ�����
	  myCamera = newCamera::create();
    if (myCamera == nullptr) { problemLoading("Fail to get camera"); }
    myCamera->setName("camera");//���ñ�ǩ
    myCamera->bindPlayer(sprite);

    this->addChild(myCamera->getCamera());
    this->addChild(myCamera);
    sprite->getCamera(myCamera);

	// ѩɽbossVec2(-18 * sizeWidth + 800, 18 * sizeWidth + 600)
	auto sizeWidth = -40 * mapManager->getTileSize();
	summonEnemy("HellDog", Vec2(-26 * sizeWidth + 800, 18 * sizeWidth + 600));
	//�����������жԻ�����
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
				//���ضԻ���
				myCamera->hidedialog();

				//�����Qin_1����Ҫ��������
				if (currentdialogername == "Qin_1")
				{
					task.push_back("Qin_wood");
					//�������
					task_progress.push_back(0);
				}
				//�����Katheryne,��Ҫ��������
				if (currentdialogername == "Katheryne")
				{
					task.push_back("snow");
					//�������
					task_progress.push_back(0);
				}
				

			}
		      //����map�еĶԻ�����ʾ�Ի���
		      myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
		      dialoging++;
		      //�������Ҫѡ���ʱ��
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
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oridinaryAttack, this);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�




      //��player���˺����ְ󶨵�����
      for (int i = 0; i < 20; i++)
      {
	    this->addChild(sprite->m_damage_label[i]);
	    this->addChild(sprite->m_element_label[i]);

	   
      }


      characterset();
      //�����¼������������л���1 -- ��ʿ��2 -- ������
      auto exchangeListener = EventListenerKeyboard::create();
      //��������ʱ����
      exchangeListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	    {
		  if (keyCode == EventKeyboard::KeyCode::KEY_1 && !sprite->isOnBoard) //��ʿ
		  {
			//���û�ڶԻ�
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
			      //����
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
				    //ǰ������������Ϊ��
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
				//�����Qin_wood��ӵ����������4��ľͷ
				//�������񣬲鿴�Ƿ���Qin_wood
				if (currentdialogername == "Qin_wood" && task.size() > 0)
				{
					for (int i = 0; i < task.size(); i++)
					{
						if (task[i] == "Qin_wood")
						{
							//���map storage��4��ľͷ
							if (storage["Wood"] >= 4)
							{
							      sprite->swordButtons[3].isEmpty = true;
								//�������
								storage["Wood"] -= 4;
								choose = 1;
								ischoose = false;
								//����
								currentdialogername = currentdialogername + "_" + to_string(choose);
								dialoging = 0;
								myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
								dialoging++;
							}
							else
							{
								//����δ���
								choose = 2;
								ischoose = false;
								//����
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
					//����
					currentdialogername = currentdialogername + "_" + to_string(choose);
					dialoging = 0;
					myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
					dialoging++;
				}

			     
			}

		  }
		  else if (keyCode == EventKeyboard::KeyCode::KEY_2 && !sprite->isOnBoard) //������
		  {
			//���û�ڶԻ�
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
			      //����
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
				    //ǰ������������Ϊ��
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
				//����
				currentdialogername = currentdialogername + "_" + to_string(choose);
				dialoging = 0;
				myCamera->setDialog(dialog_map[currentdialogername][dialoging], currentrealdialogername);
				dialoging++;

			}
		  }
		  //X�����洢
		  else if (keyCode == EventKeyboard::KeyCode::KEY_X)
		  {
			if (sprite->getIsDialog() == false)
			{
			      savemessage();
			}
		  }
		  //Z������ȡ
		  else if (keyCode == EventKeyboard::KeyCode::KEY_Z)
		  {
			if (sprite->getIsDialog() == false)
			{
			      loadmessage();
			}
		  }
	    };
      Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exchangeListener, sprite);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�


      return true;//����true��ʾ��ʼ���ɹ�
}

void HelloWorld::startDialog(string name)
{
      //��ʾ�Ի���
      myCamera->showdialog();
      //����Ϊ�Ի�״̬
      sprite->setIsDialog(true);
      //��ȡ�Ի�
      currentdialogername = name;
	  currentrealdialogername = name;
	  dialoging = 0;
	  //�������Qin��������������Qin,�������л�ΪQin_wood
	  //��task�в���
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
	  //�����Fisherman��������
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

//���º�����ÿ֡����һ��
void HelloWorld::update(float dt)
{
      /*auto visibleSize = Director::getInstance()->getVisibleSize();
      Vec2 origin = Director::getInstance()->getVisibleOrigin();
      dialogmenu->setPosition(Vec2(visibleSize.width / 3 + origin.x, 100));*/
      //����getCameraSpritePosition()��λ�ø���dialogmenu
      //dialogmenu->setPosition(newCamera->getCameraSpritePosition());


      
      Player* player = (Player*)this->getChildByName("Me");

      if (New_Teleport_position != Vec2::ZERO)
      {
	    sprite->setPosition(New_Teleport_position);
	    myCamera->bindPlayer(sprite);
	    sprite->clearKeyBoardState();
	    New_Teleport_position = Vec2::ZERO;
      }
      // ˢ�¹���
      refreshMonster();
	    //ÿһ֡��������û�д򵽵��ˣ��Լ�������û�д����
	//����Ƿ�򵽵��ˣ����������Ч�͵���
	    for (int j = 0; j < 20; j++)
	    {
		  if (currentPlayer->m_effect[j] != nullptr)
		  {
			////����effect�ǲ��ǿ�
			//if (currentPlayer->m_effect[j]->effect == nullptr)
			//{
			//	currentPlayer->m_effect[j] = nullptr;
			//	break;
			//}

			//��������
			for (int k = 0; k < 20; k++)
			{
			      if (enemygroup[k] != nullptr)
			      {
				    //�������
				    if (!enemygroup[k]->isDead && PlayerAttack(currentPlayer->m_effect[j], enemygroup[k]) && currentPlayer->m_effect_index[j][k] > 0)
				    {
					  //���������֣�����ǵ���Ȯ
					  if (enemygroup[k]->getNaming() == "HellDog")
					  {
						if (enemygroup[k]->get1CD() <= 0)
						{
						      enemygroup[k]->skillQ();
						      enemygroup[k]->set1CD();
						      //break;

						}

					  }

					  //�����������
					  currentPlayer->m_mp += 10;
					  if (currentPlayer->m_mp > currentPlayer->m_mp)
					  {
						currentPlayer->m_mp = currentPlayer->m_max_mp;
					  }

					  //��Ӧλ�ü�����1
					  currentPlayer->m_effect_index[j][k] -= 1;

					  //�Ե��˵���Hurt��������ֵΪ������������Ϊeffect�����damage_type
					  enemygroup[k]->hurt(int(currentPlayer->getAttack() * currentPlayer->m_effect[j]->damage_rate), currentPlayer->m_effect[j]->damage_type, true);
					  //���������
					  if (enemygroup[k]->isDead)
					  {

							//exp����
						currentPlayer->m_exp += enemygroup[k]->getGainExp();
						//���ս��Ʒ
						//����storage������оͼ�1��û�оʹ���
						if (storage.find(enemygroup[k]->getNaming()) != storage.end())
						{
							storage[enemygroup[k]->getNaming()] += 1;
						}
						else
						{
							storage[enemygroup[k]->getNaming()] = 1;
						}


						//���䲻�ɼ���3���ɾ��
						enemygroup[k]->setVisible(false);

						//�ڵ㽻����������ڵ�ŵ�enemygroup_delete
						for (int l = 0; l < 20; l++)
						{
						      if (enemygroup_delete[l] == nullptr)
						      {
							    enemygroup_delete[l] = enemygroup[k];
							    //ɾ��
							    enemygroup[k] = nullptr;
							    break;
						      }
						}


						//�ú���Ľڵ���ǰ��
						for (int l = k; l < 18; l++)
						{
						      if (enemygroup[l + 1] != nullptr)
						      {
							    enemygroup[l] = enemygroup[l + 1];
							    enemygroup[l + 1] = nullptr;
							    //��Ӧλ�ü�����1
							    currentPlayer->m_effect_index[j][l] = currentPlayer->m_effect_index[j][l + 1];
						      }
						      else
						      {
							    break;
						      }

						}

						//5���ɾ��enemygroup_delete�еĽڵ�
						for (int l = 0; l < 20; l++)
						{
						      if (enemygroup_delete[l] != nullptr)
						      {
							    enemygroup_delete[l]->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=] {this->removeChild(enemygroup_delete[l]); }), nullptr));//��ʱ5���ɾ��
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
			//������Ч���������Ƿ�����
			for (int j = 0; j < 20; j++)
			{
			      if (enemygroup[i]->m_effect[j] != nullptr)
			      {
				    //�������
				    if (PlayerAttack(enemygroup[i]->m_effect[j], currentPlayer) && enemygroup[i]->m_effect_index[j][0] > 0)
				    {
					  //��Ӧλ�ü�����1
					  enemygroup[i]->m_effect_index[j][0] -= 1;
					  //����ҵ���Hurt��������ֵΪ������������Ϊeffect�����damage_type
					  currentPlayer->hurt(int(enemygroup[i]->getAttack() * enemygroup[i]->m_effect[j]->damage_rate), enemygroup[i]->m_effect[j]->damage_type, true);
				    }
			      }
			      else
			      {
				    break;
			      }
			}


			//������ң�ֻҪ��ҿ������ˣ����˾�����������ߣ�leisure=false��
			//�������ڵ��˵Ĺ�����Χ(500)��
			if (currentPlayer->getPosition().distance(enemygroup[i]->getPosition()) < 1000)
			{
			      //���������������
			      enemygroup[i]->leisure = false;
			      //����ǵ���Ȯ
			      if (enemygroup[i]->getNaming() == "HellDog")
			      {
				    //1����û��ȴ�Ļ��ͷ�1����
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
      //ֻҪ��һ��Ϊ�վͷ���
      if (me == nullptr || other == nullptr)
      {
	    return false;
      }


	    //��ȡ�Ŵ���
	    float c = me->effect->getScaleX();

	    //getContentSize()ֻ�ܻ�ȡͼƬ��ԭʼ��С�����ͼƬ�������ˣ����������ȡ�Ĵ�С������ǰ�Ĵ�С�����Ҫ��getContentSize().width*getScaleX()����ȡ���ź�Ĵ�С
	    other->m_bodyRect = Rect(other->getPositionX() - other->getBody()->getContentSize().width / 2, other->getPositionY() - other->getBody()->getContentSize().height / 2, other->getBody()->getContentSize().width * other->getBody()->getScaleX(), other->getBody()->getContentSize().height * other->getBody()->getScaleY());

	    me->effectRect = Rect(me->getPositionX() - me->effect->getContentSize().width / 2, me->getPositionY() - me->effect->getContentSize().height / 2, me->effect->getContentSize().width * me->effect->getScaleX(), me->effect->getContentSize().height * me->effect->getScaleY());


	    //��ȡ��Ҿ����Ŀ�꾫��İ�Χ��
	    Rect playerRect = me->effectRect;
	    //����m_body�İ�Χ��
	    Rect targetRect = other->m_bodyRect;

	    ////��Ӧλ�û��������α��ڵ���
	    //DrawNode* drawNode = DrawNode::create();
	    //drawNode->drawRect(Vec2(playerRect.getMinX(), playerRect.getMinY()), Vec2(playerRect.getMaxX(), playerRect.getMaxY()), Color4F(1, 0, 0, 1));
	    //this->addChild(drawNode, 1000);

	    //DrawNode* drawNode2 = DrawNode::create();
	    //drawNode2->drawRect(Vec2(targetRect.getMinX(), targetRect.getMinY()), Vec2(targetRect.getMaxX(), targetRect.getMaxY()), Color4F(1, 0, 0, 1));
	    //this->addChild(drawNode2, 1000);





	    // �����������İ�Χ���Ƿ��ཻ
	    if (playerRect.intersectsRect(targetRect))
	    {

		  return true;
	    }

	    return false;
      }




void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->end();//�ر���Ϸ�������˳�Ӧ�ó���
	//��ת������StartMenu
	Director::getInstance()->replaceScene(StartMenu::createScene());

}
void HelloWorld::storeInfo(Player* sprite, int tag)
{
      //0 -- �ӽ�ʿ�л�Ϊ�����֣�Ҫ���潣ʿ����Ϣ
      //1 -- �ӹ������л�Ϊսʿ��Ҫ���湭���ֵ���Ϣ
      for (int i = 0; i < 8; i++)
      {
	    playerInfo[tag].element[i] = sprite->m_element[i];
      }
      playerInfo[tag].shield = sprite->m_shield;
      playerInfo[tag].hp = sprite->m_hp;
      playerInfo[tag].max_hp = sprite->m_max_hp;
      playerInfo[tag].mp = sprite->m_mp;
      playerInfo[tag].max_mp = sprite->m_max_mp;
      //����
      playerInfo[tag].exp = sprite->m_exp;
      playerInfo[tag].max_exp = sprite->m_max_exp;

      for (int i = 0; i < 8; i++)
      {
	    playerInfo[tag].isElement[i] = sprite->m_isElement[i];
      }
      playerInfo[tag].defense_origin = sprite->m_defense_origin;
      playerInfo[tag].defense = sprite->m_defense;
      playerInfo[tag].level = sprite->level;
      //״̬
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
	// ��ȡ���ӳߴ�
	auto tileSize = mapManager->getTileSize();
	//ˢ�¹���
	for (int i = 0; i < 40; ++i) {
	std:pair<int, int> pos1(std::floor(sprite->getPosition().x / tileSize) + -20 + i, std::floor(sprite->getPosition().y / tileSize));
		// ��ˢ�µ㣬�Ҹõ�δˢ�¹�����
		if (mapManager->isRefreshMonster(sprite->getPosition() + Vec2((-20 + i) * tileSize, -20 * tileSize)) && monsterRefreshState.find(pos1) == monsterRefreshState.end())
		{
			// ����ˢ�µ��ٻ�����
			summonEnemy("Bat_Fire", Vec2(sprite->getPosition() + Vec2((-20 + i) * tileSize, -20 * tileSize)));
			// ��Ǹ�ˢ�µ���ˢ�¹���
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
      //���������ٻ�����
      Enemy* enemy = Enemy::create();
      if (enemy == nullptr)
      {
	    problemLoading("'Enemy'");
      }
      else
      {
	    //���þ����λ��
	    enemy->setPosition(Vec2(position.x, position.y));
	    enemy->setName("Enemy");//���ñ�ǩ
	    this->addChild(enemy, 0);
	    //���뵽��������
	    for (int i = 0; i < 20; i++)
	    {
		  if (enemygroup[i] == nullptr)
		  {
			enemygroup[i] = enemy;
			enemy->naming(name);//����������
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

//�ļ��洢
void HelloWorld::initmessage(const char* pName)
{
      rapidjson::Document oWriteDoc;
      oWriteDoc.SetObject();
      rapidjson::Document::AllocatorType& allocator = oWriteDoc.GetAllocator();
      rapidjson::Value oArray(rapidjson::kArrayType);

      rapidjson::StringBuffer oBuffer;
      rapidjson::Writer<rapidjson::StringBuffer> oWriter(oBuffer);
      oWriteDoc.Accept(oWriter);

      //д��
      FILE* pFile = fopen(pName, "wb+");
      if (pFile == NULL)
      {
	    log("Open File '%s' Failed.", pName);
	    return;
      }

      fputs(oBuffer.GetString(), pFile);
      fclose(pFile);

}


//�洢������ݵ����ص�json�ļ�
void HelloWorld::savemessage()
{
      //����һ��json����
      rapidjson::Document document;
      //���ö��������
      document.SetObject();
      //����һ��json����
      rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
      //����һ��json����
      rapidjson::Value object1(rapidjson::kObjectType);
      //����һ��json����
      rapidjson::Value object2(rapidjson::kObjectType);


      document.AddMember("swordPlayer", object1, allocator);
      document.AddMember("bowPlayer", object2, allocator);
      //����һ��json����
      rapidjson::Value& player1 = document["swordPlayer"];
      //����һ��json����
      rapidjson::Value& player2 = document["bowPlayer"];
      //�ȼ�⵱ǰ��������ĸ�
      string name = currentPlayer->m_name;
      if (name == "swordPlayer")
      {
	    document.AddMember("swordPlayer", object1, allocator);//���һ������,����ΪPlayer
	    player1.AddMember("name", "swordPlayer", allocator);
	    player1.AddMember("exp", currentPlayer->m_exp, allocator);
	    player1.AddMember("max_exp", currentPlayer->m_max_exp, allocator);
	    player1.AddMember("hp", currentPlayer->m_hp, allocator);
	    player1.AddMember("max_hp", currentPlayer->m_max_hp, allocator);
	    //����
	    player1.AddMember("shield", currentPlayer->m_shield, allocator);
	    //Ԫ������
	    player1.AddMember("mp", currentPlayer->m_mp, allocator);
	    player1.AddMember("max_mp", currentPlayer->m_max_mp, allocator);
	    //����
	    player1.AddMember("defense_origin", currentPlayer->m_defense_origin, allocator);
	    player1.AddMember("defense", currentPlayer->m_defense, allocator);
	    //�ȼ�
	    player1.AddMember("level", currentPlayer->level, allocator);
	    //�����ȴʱ��
	    player1.AddMember("max_E_CD", currentPlayer->m_max_E_CD, allocator);
	    player1.AddMember("max_Q_CD", currentPlayer->m_max_Q_CD, allocator);
	    //��������
	    player1.AddMember("base_attack", currentPlayer->base_attack, allocator);
	    player1.AddMember("base_defense", currentPlayer->base_defense, allocator);
	    player1.AddMember("base_hp", currentPlayer->base_hp, allocator);
	    //��������
	    player1.AddMember("extra_attack", currentPlayer->extra_attack, allocator);
	    player1.AddMember("extra_defense", currentPlayer->extra_defense, allocator);
	    player1.AddMember("extra_hp", currentPlayer->extra_hp, allocator);
      }
      else if (name == "bowPlayer")
      {
	    document.AddMember("bowPlayer", object2, allocator);//���һ������,����ΪPlayer
	    player2.AddMember("name", "bowPlayer", allocator);
	    player2.AddMember("exp", currentPlayer->m_exp, allocator);
	    player2.AddMember("max_exp", currentPlayer->m_max_exp, allocator);
	    player2.AddMember("hp", currentPlayer->m_hp, allocator);
	    player2.AddMember("max_hp", currentPlayer->m_max_hp, allocator);
	    //����
	    player2.AddMember("shield", currentPlayer->m_shield, allocator);
	    //Ԫ������
	    player2.AddMember("mp", currentPlayer->m_mp, allocator);
	    player2.AddMember("max_mp", currentPlayer->m_max_mp, allocator);
	    //����
	    player2.AddMember("defense_origin", currentPlayer->m_defense_origin, allocator);
	    player2.AddMember("defense", currentPlayer->m_defense, allocator);
	    //�ȼ�
	    player2.AddMember("level", currentPlayer->level, allocator);
	    //�����ȴʱ��
	    player2.AddMember("max_E_CD", currentPlayer->m_max_E_CD, allocator);
	    player2.AddMember("max_Q_CD", currentPlayer->m_max_Q_CD, allocator);
	    //��������
	    player2.AddMember("base_attack", currentPlayer->base_attack, allocator);
	    player2.AddMember("base_defense", currentPlayer->base_defense, allocator);
	    player2.AddMember("base_hp", currentPlayer->base_hp, allocator);
	    //��������
	    player2.AddMember("extra_attack", currentPlayer->extra_attack, allocator);
	    player2.AddMember("extra_defense", currentPlayer->extra_defense, allocator);
	    player2.AddMember("extra_hp", currentPlayer->extra_hp, allocator);
      }





      //���������swordPlayer
      for (int i = 0; i < 2; i++)
      {
	    if (playerInfo[i].name == "swordPlayer" && name != "swordPlayer")
	    {
		  //���ö��������
		  document.AddMember("swordPlayer", object1, allocator);//���һ������,����ΪPlayer

		  player1.AddMember("name", "swordPlayer", allocator);
		  player1.AddMember("exp", playerInfo[i].exp, allocator);
		  player1.AddMember("max_exp", playerInfo[i].max_exp, allocator);
		  player1.AddMember("hp", playerInfo[i].hp, allocator);
		  player1.AddMember("max_hp", playerInfo[i].max_hp, allocator);
		  //����
		  player1.AddMember("shield", playerInfo[i].shield, allocator);
		  //Ԫ������
		  player1.AddMember("mp", playerInfo[i].mp, allocator);
		  player1.AddMember("max_mp", playerInfo[i].max_mp, allocator);
		  //����
		  player1.AddMember("defense_origin", playerInfo[i].defense_origin, allocator);
		  player1.AddMember("defense", playerInfo[i].defense, allocator);
		  //�ȼ�
		  player1.AddMember("level", playerInfo[i].level, allocator);
		  //�����ȴʱ��
		  player1.AddMember("max_E_CD", playerInfo[i].max_E_CD, allocator);
		  player1.AddMember("max_Q_CD", playerInfo[i].max_Q_CD, allocator);

		  //��������
		  player1.AddMember("base_attack", playerInfo[i].base_attack, allocator);
		  player1.AddMember("base_defense", playerInfo[i].base_defense, allocator);
		  player1.AddMember("base_hp", playerInfo[i].base_hp, allocator);
		  //��������
		  player1.AddMember("extra_attack", playerInfo[i].extra_attack, allocator);
		  player1.AddMember("extra_defense", playerInfo[i].extra_defense, allocator);
		  player1.AddMember("extra_hp", playerInfo[i].extra_hp, allocator);




	    }
	    else if (playerInfo[i].name == "bowPlayer" && name != "bowPlayer")
	    {
		  //���ö��������
		  document.AddMember("bowPlayer", object2, allocator);//���һ������,����ΪPlayer
		  player2.AddMember("name", "bowPlayer", allocator);
		  player2.AddMember("exp", playerInfo[i].exp, allocator);
		  player2.AddMember("max_exp", playerInfo[i].max_exp, allocator);
		  player2.AddMember("hp", playerInfo[i].hp, allocator);
		  player2.AddMember("max_hp", playerInfo[i].max_hp, allocator);
		  //����
		  player2.AddMember("shield", playerInfo[i].shield, allocator);
		  //Ԫ������
		  player2.AddMember("mp", playerInfo[i].mp, allocator);
		  player2.AddMember("max_mp", playerInfo[i].max_mp, allocator);
		  //����
		  player2.AddMember("defense_origin", playerInfo[i].defense_origin, allocator);
		  player2.AddMember("defense", playerInfo[i].defense, allocator);
		  //�ȼ�
		  player2.AddMember("level", playerInfo[i].level, allocator);
		  //�����ȴʱ��
		  player2.AddMember("max_E_CD", playerInfo[i].max_E_CD, allocator);
		  player2.AddMember("max_Q_CD", playerInfo[i].max_Q_CD, allocator);

		  //��������
		  player2.AddMember("base_attack", playerInfo[i].base_attack, allocator);
		  player2.AddMember("base_defense", playerInfo[i].base_defense, allocator);
		  player2.AddMember("base_hp", playerInfo[i].base_hp, allocator);
		  //��������
		  player2.AddMember("extra_attack", playerInfo[i].extra_attack, allocator);
		  player2.AddMember("extra_defense", playerInfo[i].extra_defense, allocator);
		  player2.AddMember("extra_hp", playerInfo[i].extra_hp, allocator);
	    }



      }


      //�洢������
		      //���Data/PlayerData.json�Ƿ����
		      //����һ��json�ļ���
      rapidjson::StringBuffer buffer;
      //��json����д��json�ļ���
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      document.Accept(writer);
      //����һ���ļ���


      //������û��Path�µ�PlayerData.json�ļ�
      //��ȡ��ǰ·��
      char* path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
      //path�ص���һ��Ŀ¼��Data�ļ��е�PlayerData.json�ļ�
      path = _fullpath(NULL, "..\\Data\\PlayerData.json", 0);

      //���ļ�
      FILE* file = fopen(path, "wb");



      //����ļ�������
      if (file)
      {
	    //��json�ļ���д���ļ�
	    fputs(buffer.GetString(), file);
	    //�ر��ļ���
	    fclose(file);
      }
      //����ļ��������ڣ�����initmessage����
      else
      {
	    initmessage(path);
	    //�ٴδ��ļ�
	    FILE* file = fopen(path, "wb+");
	    //��json�ļ���д���ļ�
	    fputs(buffer.GetString(), file);
	    //�ر��ļ���
	    fclose(file);


      }



      //����һ��json����
      rapidjson::Document document1;
      //���ö��������
      document1.SetObject();
      document1.AddMember("team", team, allocator);
      document1.AddMember("isFog1Enabled000", isFog1Enabled000, allocator);
      document1.AddMember("isFog2Enabled000", isFog2Enabled000, allocator);
      document1.AddMember("isFog3Enabled000", isFog3Enabled000, allocator);
      document1.AddMember("isFog4Enabled000", isFog4Enabled000, allocator);
      //�洢������
      rapidjson::StringBuffer buffer1;
      //��json����д��json�ļ���
      rapidjson::Writer<rapidjson::StringBuffer> writer1(buffer1);
      document1.Accept(writer1);

      path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
      path = _fullpath(NULL, "..\\Data\\team.json", 0);
      //����ļ�������
      file = fopen(path, "wb");
      if (file)
      {
	    //��json�ļ���д���ļ�
	    fputs(buffer1.GetString(), file);
	    //�ر��ļ���
	    fclose(file);
      }
      //����ļ��������ڣ�����initmessage����
      else
      {
	    initmessage(path);
	    //�ٴδ��ļ�
	    file = fopen(path, "wb+");
	    //��json�ļ���д���ļ�
	    fputs(buffer1.GetString(), file);
	    //�ر��ļ���
	    fclose(file);
      }




	  //����һ��json����
	  rapidjson::Document document4;
	  //���ö��������
	  document4.SetObject();
	  //�洢map���͵�storage
	  rapidjson::Value object22(rapidjson::kObjectType);
	  for (auto iter = storage.begin(); iter != storage.end(); iter++)
	  {
		  //����һ��json����
		  rapidjson::Value key(rapidjson::kStringType);
		  //���ö��������
		  key.SetString(iter->first.c_str(), iter->first.size(), allocator);
		  //����һ��json����
		  rapidjson::Value value(rapidjson::kNumberType);
		  //���ö��������
		  value.SetInt(iter->second);
		  //��ӵ�object��
		  object22.AddMember(key, value, allocator);
	  }
	  //��ӵ�document4��
	  document4.AddMember("storage", object22, allocator);


	  //�洢������
	  rapidjson::StringBuffer buffer4;
	  //��json����д��json�ļ���
	  rapidjson::Writer<rapidjson::StringBuffer> writer4(buffer4);
	  document4.Accept(writer4);

	  path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
	  path = _fullpath(NULL, "..\\Data\\storage.json", 0);
	  //����ļ�������
	  file = fopen(path, "wb");
	  if (file)
	  {
		  //��json�ļ���д���ļ�
		  fputs(buffer4.GetString(), file);
		  //�ر��ļ���
		  fclose(file);
	  }
	  //����ļ��������ڣ�����initmessage����
	  else
	  {
		  initmessage(path);
		  //�ٴδ��ļ�
		  file = fopen(path, "wb+");
		  //��json�ļ���д���ļ�
		  fputs(buffer4.GetString(), file);
		  //�ر��ļ���
		  fclose(file);
	  }






      //������task
      //����һ��json����
      rapidjson::Document document2;
      //���ö��������
      document2.SetObject();
      //�洢����vector,һ������������task,һ�����������task_progress
      rapidjson::Value array(rapidjson::kArrayType);
      rapidjson::Value array2(rapidjson::kArrayType);
      //�洢
      for (int i = 0; i < task.size(); i++)
      {
	    //����һ��json����
	    rapidjson::Value object(rapidjson::kStringType);
	    //���ö��������
	    object.SetString(task[i].c_str(), task[i].size(), allocator);
	    //��ӵ�array��
	    array.PushBack(object, allocator);
      }
      for (int i = 0; i < task_progress.size(); i++)
      {
	    //����һ��json����
	    rapidjson::Value object(rapidjson::kNumberType);
	    //���ö��������
	    object.SetInt(task_progress[i]);
	    //��ӵ�array2��
	    array2.PushBack(object, allocator);
      }
      //��ӵ�document2��
      document2.AddMember("task", array, allocator);
      document2.AddMember("task_progress", array2, allocator);


      ////�洢dialog_map��ֵ�ͼ�����string
      //rapidjson::Value object(rapidjson::kObjectType);
      //for (auto iter = dialog_map.begin(); iter != dialog_map.end(); iter++)
      //{
      //	//����һ��json����
      //	rapidjson::Value key(rapidjson::kStringType);
      //	//���ö��������
      //	key.SetString(iter->first.c_str(), iter->first.size(), allocator);
      //	//����һ��json����
      //	rapidjson::Value value(rapidjson::kStringType);
      //	//���ö��������
      //	value.SetString(iter->second.c_str(), iter->second.size(), allocator);
      //	//��ӵ�object��
      //	object.AddMember(key, value, allocator);
      //}
      ////��ӵ�document2��
      //document2.AddMember("dialog_map", object, allocator);
      //�洢dialog_map��ֵ��string���͵�vector������string
      rapidjson::Value object(rapidjson::kObjectType);
      for (auto iter = dialog_map.begin(); iter != dialog_map.end(); iter++)
      {
	    //����һ��json����
	    rapidjson::Value key(rapidjson::kStringType);
	    //���ö��������
	    key.SetString(iter->first.c_str(), iter->first.size(), allocator);
	    //����һ��json����
	    rapidjson::Value array(rapidjson::kArrayType);
	    for (int i = 0; i < iter->second.size(); i++)
	    {
		  //����һ��json����
		  rapidjson::Value value(rapidjson::kStringType);
		  //���ö��������
		  value.SetString(iter->second[i].c_str(), iter->second[i].size(), allocator);
		  //��ӵ�array��
		  array.PushBack(value, allocator);
	    }
	    //��ӵ�object��
	    object.AddMember(key, array, allocator);
      }
      //��ӵ�document2��
      document2.AddMember("dialog_map", object, allocator);


      //�洢������
      rapidjson::StringBuffer buffer2;
      //��json����д��json�ļ���
      rapidjson::Writer<rapidjson::StringBuffer> writer2(buffer2);
      document2.Accept(writer2);

      path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
      path = _fullpath(NULL, "..\\Data\\plot.json", 0);
      //����ļ�������
      file = fopen(path, "wb");
      if (file)
      {
	    //��json�ļ���д���ļ�
	    fputs(buffer2.GetString(), file);
	    //�ر��ļ���
	    fclose(file);
      }
      //����ļ��������ڣ�����initmessage����
      else
      {
	    initmessage(path);
	    //�ٴδ��ļ�
	    file = fopen(path, "wb+");
	    //��json�ļ���д���ļ�
	    fputs(buffer2.GetString(), file);
	    //�ر��ļ���
	    fclose(file);
      }




}


//��ȡ����json�ļ��е��������
void HelloWorld::loadmessage()
{
      char* path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
      //path�ص���һ��Ŀ¼��Data�ļ��е�PlayerData.json�ļ�
      path = _fullpath(NULL, "..\\Data\\PlayerData.json", 0);

      //���ļ���û�оʹ���
      FILE* file = fopen(path, "rb");
      //����ļ�������
      if (file)
      {
	    string strContent = FileUtils::getInstance()->getStringFromFile(path);//��ȡ�ļ�
	    //����һ��json����
	    rapidjson::Document document;
	    //����json����
	    document.Parse<0>(strContent.c_str());
	    //��ȡ���ݲ��Ҹ�ֵ�����
	    if (document.HasMember("swordPlayer"))
	    {
		  //��ȡ���ݸ�ֵ��playerInfo�ж�Ӧ�ı���
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

		  //��������
		  playerInfo[0].base_attack = document["swordPlayer"]["base_attack"].GetInt();
		  playerInfo[0].base_defense = document["swordPlayer"]["base_defense"].GetFloat();
		  playerInfo[0].base_hp = document["swordPlayer"]["base_hp"].GetInt();
		  //��������
		  playerInfo[0].extra_attack = document["swordPlayer"]["extra_attack"].GetInt();
		  playerInfo[0].extra_defense = document["swordPlayer"]["extra_defense"].GetFloat();
		  playerInfo[0].extra_hp = document["swordPlayer"]["extra_hp"].GetInt();

		  //��ҵĹ��������㹫ʽ��base_attack*1.1*level+extra_attack
		  //��ҵķ��������㹫ʽ��base_defense*1.1*level+extra_defense
		  //��ҵ�����ֵ���㹫ʽ��base_hp*1.1*level+extra_hp
		  playerInfo[0].attack = int(double(playerInfo[0].base_attack) * 1.1 * double(playerInfo[0].level) + playerInfo[0].extra_attack);
		  playerInfo[0].defense = float(double(playerInfo[0].base_defense) * 1.1 * double(playerInfo[0].level) + playerInfo[0].extra_defense);
		  playerInfo[0].max_hp = int(double(playerInfo[0].base_hp) * 1.1 * double(playerInfo[0].level) + playerInfo[0].extra_hp);



	    }
	    if (document.HasMember("bowPlayer"))
	    {
		  //��ȡ���ݸ�ֵ��playerInfo�ж�Ӧ�ı���
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

		  //��������
		  playerInfo[1].base_attack = document["bowPlayer"]["base_attack"].GetInt();
		  playerInfo[1].base_defense = document["bowPlayer"]["base_defense"].GetFloat();
		  playerInfo[1].base_hp = document["bowPlayer"]["base_hp"].GetInt();
		  //��������
		  playerInfo[1].extra_attack = document["bowPlayer"]["extra_attack"].GetInt();
		  playerInfo[1].extra_defense = document["bowPlayer"]["extra_defense"].GetFloat();
		  playerInfo[1].extra_hp = document["bowPlayer"]["extra_hp"].GetInt();

		  //��ҵĹ��������㹫ʽ��base_attack*1.1*level+extra_attack
		  //��ҵķ��������㹫ʽ��base_defense*1.1*level+extra_defense
		  //��ҵ�����ֵ���㹫ʽ��base_hp*1.1*level+extra_hp
		  playerInfo[1].attack = int(double(playerInfo[1].base_attack) * 1.1 * double(playerInfo[1].level) + playerInfo[1].extra_attack);
		  playerInfo[1].defense = float(double(playerInfo[1].base_defense) * 1.1 * double(playerInfo[1].level) + playerInfo[1].extra_defense);
		  playerInfo[1].max_hp = int(double(playerInfo[1].base_hp) * 1.1 * double(playerInfo[1].level) + playerInfo[1].extra_hp);
	    }


      }
      else
      {
	    initmessage(path);

      }
      //�����Ϣ�ȵ�

      path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
      //path�ص���һ��Ŀ¼��Data�ļ��е�PlayerData.json�ļ�
      path = _fullpath(NULL, "..\\Data\\team.json", 0);
      file = fopen(path, "rb");
      //����ļ�������
      if (file)
      {
	    string strContent = FileUtils::getInstance()->getStringFromFile(path);//��ȡ�ļ�
	    //����һ��json����
	    rapidjson::Document document1;
	    //����json����
	    document1.Parse<0>(strContent.c_str());
	    //��ȡ���ݲ��Ҹ�ֵ�����
	    if (document1.HasMember("team"))
	    {
		  //��ȡ���ݸ�ֵ��playerInfo�ж�Ӧ�ı���
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
	    //�ѵ�ǰ�����滻Ϊ��ʿ������
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
	    //������
	    sprite->m_attack = playerInfo[0].attack;


	    for (int i = 0; i < 8; i++)
	    {
		  sprite->m_element[i] = playerInfo[0].element[i];
		  sprite->m_isElement[i] = playerInfo[0].isElement[i];
		  sprite->m_immune[i] = playerInfo[0].immune[i];
	    }
	    for (int i = 0; i < 99; i++)
	    {
		  //ǰ������������Ϊ��
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
	    //������
	    sprite->m_attack = playerInfo[1].attack;
	    for (int i = 0; i < 8; i++)
	    {
		  sprite->m_element[i] = playerInfo[1].element[i];
		  sprite->m_isElement[i] = playerInfo[1].isElement[i];
		  sprite->m_immune[i] = playerInfo[1].immune[i];
	    }
	    for (int i = 0; i < 99; i++)
	    {
		  //ǰ������������Ϊ��
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


      //path�ص���һ��Ŀ¼��Data�ļ��е�PlayerData.json�ļ�
      path = _fullpath(NULL, "..\\Data\\plot.json", 0);
      file = fopen(path, "rb");
      //����ļ�������
      if (file)
      {
	    string strContent = FileUtils::getInstance()->getStringFromFile(path);//��ȡ�ļ�
	    //����һ��json����
	    rapidjson::Document document2;
	    //����json����
	    document2.Parse<0>(strContent.c_str());
	    //��ȡ���ݲ��Ҹ�ֵ�����
	    if (document2.HasMember("task"))
	    {
		  //��ȡ���ݸ�ֵ��vector task
		  //��ÿһ����и�ֵ
		  for (int i = 0; i < document2["task"].Size(); i++)
		  {
			task.push_back(document2["task"][i].GetString());
		  }
		  //��ȡ���ݸ�ֵ��vector task_progress
		  //��ÿһ����и�ֵ
		  for (int i = 0; i < document2["task_progress"].Size(); i++)
		  {
			task_progress.push_back(document2["task_progress"][i].GetInt());
		  }
		  //��ȡ���ݸ�ֵ��dialog_map
		  //��ÿһ����и�ֵ
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





	  path = _getcwd(NULL, 0);//_getcwd�ڿ�direct.h��
	  //path�ص���һ��Ŀ¼��Data�ļ��е�PlayerData.json�ļ�
	  path = _fullpath(NULL, "..\\Data\\storage.json", 0);
	  file = fopen(path, "rb");
	  //����ļ�������
	  if (file)
	  {
		  string strContent = FileUtils::getInstance()->getStringFromFile(path);//��ȡ�ļ�
		  //����һ��json����
		  rapidjson::Document document3;
		  //����json����
		  document3.Parse<0>(strContent.c_str());
		  //��ȡ���ݲ��Ҹ�ֵ��storage
		  if (document3.HasMember("storage"))
		  {
			  //��ȡ���ݸ�ֵ��map storage
			  //��ÿһ����и�ֵ
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

