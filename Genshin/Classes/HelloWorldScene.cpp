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

//��ʼ�����������ڳ�������ʱ����
bool HelloWorld::init()
{
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



	//����һ�����飨����ֻ������ʾ����ͼƬ�ã�����ʾ��HelloWorld����ͼ������Ϊ1
      sprite = Player::create();
	
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
		//���þ����λ�ã���������Ļ������
	 // sprite->setPosition(Vec2::ZERO);
         sprite->setPosition(Vec2(visibleSize.width/3, visibleSize.height/3));
		sprite->setName("Me");//���ñ�ǩ
		//��������ӵ�������
        this->addChild(sprite, 0);
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
      }
	
      return true;//����true��ʾ��ʼ���ɹ�
}

//���º�����ÿ֡����һ��
void HelloWorld::update(float dt)
{
      //��playerÿ���Ѫ
      Player* player = (Player*)this->getChildByName("Me");

     // if (++a == 120)
     // {
	    //sprite->setPosition(1500, 1500);
	    //newCamera->bindPlayer(sprite);
     // }
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->end();//�ر���Ϸ�������˳�Ӧ�ó���
	//��ת������StartMenu
	Director::getInstance()->replaceScene(StartMenu::createScene());
}
