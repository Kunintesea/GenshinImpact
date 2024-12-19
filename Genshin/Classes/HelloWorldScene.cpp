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
	closeItem->setScale(5, 5);
	//����һ���˵������Menu���͵Ķ������MenuItemImage��Ҫ��������������Ҫ����Menu��
	auto menu = Menu::create(closeItem, NULL);//����һ���˵����������һ����ť
	menu->setPosition(Vec2::ZERO);//���ò˵���λ�ã�������ԭ��
	this->addChild(menu, 1);//���˵���ӵ������У�1��ʾz���λ�ã�z���λ��Խ����ʾ�����ȼ�Խ��



	//����һ�����飨����ֻ������ʾ����ͼƬ�ã�����ʾ��HelloWorld����ͼ������Ϊ1
    sprite = Player::create();
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
		//���뵽�������
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
	//		//���þ����λ�ã����������Ϊ���ģ���һȦ
	//		enemy3->setPosition(Vec2(visibleSize.width / 3 + origin.x + 22 + 22 * i, visibleSize.height / 3 + origin.y));


	//		enemy3->setName("Enemy");//���ñ�ǩ
	//		//��������ӵ�������
	//		this->addChild(enemy3, 0);
	//		//���뵽��������
	//		for (int i = 0; i < 20; i++)
	//		{
	//			if (enemygroup[i] == nullptr)
	//			{
	//				enemygroup[i] = enemy3;
	//				if (i % 2 == 0)
	//				{
	//					enemy3->naming("Bat_Fire");//����������
	//					enemy3->initData();
	//					break;
	//				}
	//				else
	//				{
	//					enemy3->naming("Bat_Ice");//����������
	//					enemy3->initData();
	//					break;
	//				}
	//				
	//			}
	//		}
	//	}
	//}


	//��һֻ����Ȯ���������Ϸ�
	Enemy* enemy2 = Enemy::create();
	if (enemy2 == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		//���þ����λ�ã����������Ϊ���ģ���һȦ
		enemy2->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 3 + origin.y + 22));
		enemy2->setName("Enemy");//���ñ�ǩ
		//��������ӵ�������
		this->addChild(enemy2, 0);
		//���뵽��������
		for (int i = 0; i < 20; i++)
		{
			if (enemygroup[i] == nullptr)
			{
				enemygroup[i] = enemy2;
				enemy2->naming("HellDog");//����������
				enemy2->initData();
				break;
			}
		}
	}




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
      return true;//����true��ʾ��ʼ���ɹ�
}

//���º�����ÿ֡����һ��
void HelloWorld::update(float dt)
{
	//��playerÿ���Ѫ
	Player* player = (Player*)this->getChildByName("Me");
	//ÿһ֡��������û�д򵽵��ˣ��Լ�������û�д����
	//����Ƿ�򵽵��ˣ����������Ч�͵���
	for (int i = 0; i < 20; i++)
	{
		if (playergroup[i] != nullptr)
		{
			//������Ч
			for (int j = 0; j < 20; j++)
			{
				if (playergroup[i]->m_effect[j] != nullptr)
				{
					//��������
					for (int k = 0; k < 20; k++)
					{
						if (enemygroup[k] != nullptr)
						{
							//�������
							if (!enemygroup[k]->isDead && PlayerAttack(playergroup[i]->m_effect[j], enemygroup[k]) && playergroup[i]->m_effect_index[j][k] >0)
							{
								//��Ӧλ�ü�����1
								playergroup[i]->m_effect_index[j][k] -= 1;

								//�Ե��˵���Hurt��������ֵΪ������������Ϊeffect�����damage_type
								enemygroup[k]->hurt(int(playergroup[i]->getAttack() * playergroup[i]->m_effect[j]->damage_rate), playergroup[i]->m_effect[j]->damage_type, true);
								//���������
								if (enemygroup[k]->isDead)
								{
									//�����������
									//playergroup[i]->getmp() += 10;


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
					for (int k = 0; k < 20; k++)
					{
						if (playergroup[k] != nullptr)
						{
							//�������
							if (!enemygroup[k]->isDead &&PlayerAttack(enemygroup[i]->m_effect[j], playergroup[k]) && enemygroup[i]->m_effect_index[j][k] >0)
							{
								//��Ӧλ�ü�����1
								enemygroup[i]->m_effect_index[j][k] -= 1;
								//����ҵ���Hurt��������ֵΪ������������Ϊeffect�����damage_type
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


			//������ң�ֻҪ��ҿ������ˣ����˾�����������ߣ�leisure=false��
			for (int j = 0; j < 20; j++)
			{
				if (playergroup[j] != nullptr)
				{
					//�������ڵ��˵Ĺ�����Χ(500)��
					if (playergroup[j]->getPosition().distance(enemygroup[i]->getPosition()) < 700)
					{
						//���������������
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
	////�趨other��m_bodyRect�İ�Χ�У���other->m_body��λ�úʹ�С������������������ģ���С��m_body��
	//other->m_bodyRect = Rect(other->getPositionX() - other->getBody()->getContentSize().width / 2, other->getPositionY() - other->getBody()->getContentSize().height / 2, other->getBody()->getContentSize().width, other->getBody()->getContentSize().height);
	//float a = other->getBody()->getContentSize().width;
	////��Χ�еĴ�С����effect�Ĵ�С��λ�����������������
	//me->effectRect = Rect(me->getPositionX()- me->effect->getContentSize().width/2, me->getPositionY() - me->effect->getContentSize().height/2, me->effect->getContentSize().width, me->effect->getContentSize().height);
	//float b = me->effect->getContentSize().width;

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
