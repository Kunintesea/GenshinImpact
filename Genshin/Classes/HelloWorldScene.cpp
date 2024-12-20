#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Scene\StartMenu.h"

#include "Player\Player.h"

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
      ////����һ��namesprite���������ģ����ڴ洢���֡�ʹ��ʱ��ͨ��tag��ȡ�����������Ը�ֵ
      //Namesprite = Sprite::create();
      //this->addChild(Namesprite, 0);
      //Namesprite->setName("objectName");//Ĭ������
      ////tagΪ0
      //Namesprite->setTag(99);


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

	//���һ���˵������رյİ�ť�����˳�����
	//���һ�����رա�ͼ�����˳�����MenuItemImage���������ť��һ��ͼƬ��ť
	//�����create�Ĳ����ֱ��ǣ�����ͼƬ��һ��������״̬�µ�ͼƬ��һ����ѡ��״̬�µ�ͼƬ��������������һ���ص���������ʾ��������ťʱ������������
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//���closeItemΪ�ջ��߿�Ȼ��߸߶�С�ڵ���0���ͻ��ӡ������Ϣ
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
	//��������closeItem��λ�á�һ��ͼ���λ������������Ϊԭ�㣬����������Ҫ����ͼƬ����Ŀ�Ⱥ͸߶�
    else
    {
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;//visibleSize.width����Ļ�Ŀ��,origin.x��ԭ���x���꣬getContentSize().width��closeItem�Ŀ��
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));//����λ��
    }

	//����һ���˵������Menu���͵Ķ������MenuItemImage��Ҫ��������������Ҫ����Menu��
	auto menu = Menu::create(closeItem, NULL);//����һ���˵����������һ����ť
	menu->setPosition(Vec2::ZERO);//���ò˵���λ�ã�������ԭ��
	this->addChild(menu, 1);//���˵���ӵ������У�1��ʾz���λ�ã�z���λ��Խ����ʾ�����ȼ�Խ��


	//��ʼ����ʿ
	sprite = Player::create();
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
		//���þ����λ�ã���������Ļ������
	 // sprite->setPosition(Vec2::ZERO);
         sprite->setPosition(Vec2(500,500));
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




    //��һֻ����Ȯ���������Ϸ�
    summonEnemy("HellDog", Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 3 + origin.y + 100));
    //��һֻ������
    summonEnemy("Bat_Ice", Vec2(visibleSize.width / 3 + origin.x + 100, visibleSize.height / 3 + origin.y + 100));

    //��һֻ������
    summonEnemy("Bat_Fire", Vec2(visibleSize.width / 3 + origin.x + 200, visibleSize.height / 3 + origin.y + 100));

    // ������ͼ������
    mapManager = mapManager::create();
    // ��ͼ������Ӧ���뾫�������޹�
    mapManager->setAnchorPoint(Vec2::ZERO);
    mapManager->setPosition(Vec2::ZERO);
    mapManager->setName("mapManager");
    this->addChild(mapManager, -1);
	
    // ����һ�����
      newCamera = newCamera::create();
      if (newCamera == nullptr) { problemLoading("Fail to get camera"); }
      newCamera->setName("camera");//���ñ�ǩ
      newCamera->bindPlayer(sprite);
      this->addChild(newCamera->getCamera());
      this->addChild(newCamera);
      sprite->getCamera(newCamera);

      //��player���˺����ְ󶨵�����
      for (int i = 0; i < 20; i++)
      {
	    this->addChild(sprite->m_damage_label[i]);
	    this->addChild(sprite->m_element_label[i]);

	    //����Ҳ�ӽ������м������˾ͼӼ���
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
      //�����¼������������л���1 -- ��ʿ��2 -- ������
      auto exchangeListener = EventListenerKeyboard::create();
      //��������ʱ����
      exchangeListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	    {
		  if (keyCode == EventKeyboard::KeyCode::KEY_1) //��ʿ
		  {
			this->storeInfo(sprite, 1);
			sprite->m_name = playerInfo[0].name;
			sprite->m_weapon->setTexture(playerInfo[0].weapon);
			sprite->m_body->stopAllActions();
		  }
		  else if (keyCode == EventKeyboard::KeyCode::KEY_2) //������
		  {
			this->storeInfo(sprite, 0);
			sprite->m_name = playerInfo[1].name;
			sprite->m_weapon->setTexture(playerInfo[1].weapon);
			sprite->m_body->stopAllActions();
		  }
	    };
      Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exchangeListener, sprite);//�Ѽ��������뵽�¼��ַ����У��������������󶨵Ķ�����������ȼ��趨Ϊ��������ȼ�



      return true;//����true��ʾ��ʼ���ɹ�
}

//���º�����ÿ֡����һ��
void HelloWorld::update(float dt)
{
      //��playerÿ���Ѫ
      Player* player = (Player*)this->getChildByName("Me");

      if (New_Teleport_position != Vec2::ZERO)
      {
	    sprite->setPosition(New_Teleport_position);
	    newCamera->bindPlayer(sprite);
	    New_Teleport_position = Vec2::ZERO;
      }
	    //ÿһ֡��������û�д򵽵��ˣ��Լ�������û�д����
	//����Ƿ�򵽵��ˣ����������Ч�͵���
	    for (int j = 0; j < 20; j++)
	    {
		  if (currentPlayer->m_effect[j] != nullptr)
		  {
			//��������
			for (int k = 0; k < 20; k++)
			{
			      if (enemygroup[k] != nullptr)
			      {
				    //�������
				    if (!enemygroup[k]->isDead && PlayerAttack(currentPlayer->m_effect[j], enemygroup[k]) && currentPlayer->m_effect_index[j][k] > 0)
				    {
					  //��Ӧλ�ü�����1
					  currentPlayer->m_effect_index[j][k] -= 1;

					  //�Ե��˵���Hurt��������ֵΪ������������Ϊeffect�����damage_type
					  enemygroup[k]->hurt(int(currentPlayer->getAttack() * currentPlayer->m_effect[j]->damage_rate), currentPlayer->m_effect[j]->damage_type, true);
					  //���������
					  if (enemygroup[k]->isDead)
					  {
						//�����������
						//currentPlayer->getmp() += 10;


						//���䲻�ɼ���5���ɾ��
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

						//5���ɾ��enemygroup_delete�еĽڵ�
						for (int l = 0; l < 20; l++)
						{
						      if (enemygroup_delete[l] != nullptr)
						      {
							    enemygroup_delete[l]->runAction(Sequence::create(DelayTime::create(5), CallFunc::create([=] {this->removeChild(enemygroup_delete[l]); }), nullptr));//��ʱ5���ɾ��
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
      //���������ٻ�����
      Enemy* enemy = Enemy::create();
      if (enemy == nullptr)
      {
	    problemLoading("'HelloWorld.png'");
      }
      else
      {
	    //���þ����λ�ã����������Ϊ���ģ���һȦ
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
			break;
		  }
	    }
      }
}
