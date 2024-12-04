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




	//��ȡ����ͼƬgrass�����䲻���ظ�����������Ļ
	auto background = Sprite::create("grass.png");//����һ�����飬����ͼƬ��grass
	if (background == nullptr)//�������ͼƬΪ�գ��ͻ��ӡ������Ϣ
	{
		problemLoading("'grass.png'");
	}
	else
	{
		//����ѭ������������Ļ
		for (int i = 0; i < visibleSize.width / background->getContentSize().width + 1; i++)
		{
			for (int j = 0; j < visibleSize.height / background->getContentSize().height + 1; j++)
			{
				auto bg = Sprite::create("grass.png");//����һ�����飬����ͼƬ��grass
				bg->setPosition(Vec2(i * bg->getContentSize().width, j * bg->getContentSize().height));//���ñ���ͼƬ��λ��
				this->addChild(bg, 0);//������ͼƬ��ӵ�������
			}
		}
	}
	//����һ����Ƥ��������
	auto bg = Sprite::create("grass.png");//����һ�����飬����ͼƬ��grass
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));//���ñ���ͼƬ��λ��
	//���ñ�ǩ
	bg->setName("Center");
	this->addChild(bg, 0);//������ͼƬ��ӵ�������










	//���һ���˵������رյİ�ť�����˳�����
	//���һ�����رա�ͼ�����˳�����MenuItemImage���������ť��һ��ͼƬ��ť
	//�����create�Ĳ����ֱ��ǣ�����ͼƬ��һ��������״̬�µ�ͼƬ��һ����ѡ��״̬�µ�ͼƬ��������������һ���ص���������ʾ��������ťʱ������������
    closeItem = MenuItemImage::create(
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
	  closeItemInitialPosition 
		= Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 -80,
		      origin.y + closeItem->getContentSize().height / 2 + 80);
		closeItem->setPosition(closeItemInitialPosition);//����λ��
    }
    closeItem->setScale(5, 5);
	//����һ���˵������Menu���͵Ķ������MenuItemImage��Ҫ��������������Ҫ����Menu��
	auto menu = Menu::create(closeItem, NULL);//����һ���˵����������һ����ť
	menu->setPosition(Vec2::ZERO);//���ò˵���λ�ã�������ԭ��
	this->addChild(menu, 1);//���˵���ӵ������У�1��ʾz���λ�ã�z���λ��Խ����ʾ�����ȼ�Խ��

	//����һ�����飨����ֻ������ʾ����ͼƬ�ã�����ʾ��HelloWorld����ͼ������Ϊ1
	Player * sprite = Player::create();
	
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
		//���þ����λ�ã���������Ļ������
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		sprite->setName("Me");//���ñ�ǩ
		//��������ӵ�������
        this->addChild(sprite, 0);

    }
	

    // ����һ�����
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
	
      return true;//����true��ʾ��ʼ���ɹ�
}

//���º�����ÿ֡����һ��
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
	//Director::getInstance()->end();//�ر���Ϸ�������˳�Ӧ�ó���
	//��ת������StartMenu
	Director::getInstance()->replaceScene(StartMenu::createScene());

}
