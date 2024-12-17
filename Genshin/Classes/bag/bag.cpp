/*������ţ���Ӧis_Fill�����еĴ洢1-5��weapon����
1��ֱ����
2����б��
3����
4������
5����ì*/



#include "bag.h"
#include "cocos2d.h"
#include "Player/Player.h"  // ȷ����ȷ���� Player.h �ļ�
#include "ui/CocosGUI.h"

// ������ʼ������
bool Bag::init() {
    if (!Node::init()) {  // ���ø���ĳ�ʼ������
        return false;
    }
    m_bagSprite = Sprite::create("bag/bag_background.png");
        
    // ��� m_bagSprite �Ƿ�ɹ�����
    if (m_bagSprite == nullptr)
    {
        log("m_bagSprite not set. Exiting init.");
        return false;  // ���û�д��� m_bagSprite�����˳���ʼ��
    }
    
    if (m_bagSprite) {
        m_bagSprite->setLocalZOrder(100);  // ȷ���������������ϲ�
        
        // ���ñ�������ĳߴ磨����ʵ������
        m_bagSprite->setContentSize(Size(500, 500));  // ���� Sprite �ĳߴ�
               
    }
   
    // Ĭ�ϱ�����������
    m_bagSprite->setVisible(false);  // ��ʼʱ���ر���

    this->addChild(m_bagSprite);
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
        auto small_grid = Sprite::create("bag/smallbaggrid.png");
        // ��� small_grid�Ƿ�ɹ�����
        if (small_grid == nullptr)
        {
            log("small_grid not set. Exiting init.");
            return false; 
        }
        small_grid->setContentSize(Size(100, 100));  // ���� Sprite �ĳߴ�
        small_grid->setLocalZOrder(101);
        small_grid->setPosition(Vec2(i*100+100, 400-j*100)); // �����ͼƬ��ƫ��λ��
        m_bagSprite->addChild(small_grid);
        }
    }

    auto small_grid1 = Sprite::create("bag/smallbaggrid.png");
    if (small_grid1 == nullptr)
    {
        log("small_grid not set. Exiting init.");
        return false;  
    }
    small_grid1->setContentSize(Size(100, 100));  // ���� Sprite �ĳߴ�
    small_grid1->setLocalZOrder(103);
    small_grid1->setPosition(Vec2(560, 300)); // �����ͼƬ��ƫ��λ��
    small_grid1->setVisible(false);
    m_bagSprite->addChild(small_grid1);
    auto small_grid2 = Sprite::create("bag/smallbaggrid.png");
    if (small_grid2 == nullptr)
    {
        log("small_grid not set. Exiting init.");
        return false;
    }
    small_grid2->setContentSize(Size(100, 100));  // ���� Sprite �ĳߴ�
    small_grid2->setLocalZOrder(103);
    small_grid2->setPosition(Vec2(560, 175)); // �����ͼƬ��ƫ��λ��
    small_grid2->setVisible(false);
    m_bagSprite->addChild(small_grid2);
    // ���������׻�ɫ�ľ���
    auto colorLayer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 245, 220, 255), 400, 150);//�·���װ�����泤400��150
    colorLayer->setVisible(false);  // ��ʼʱ����
    colorLayer->setLocalZOrder(102);  
    m_bagSprite->addChild(colorLayer);

    auto colorLayer2 = cocos2d::LayerColor::create(cocos2d::Color4B(255, 245, 220, 255), 120, 400);//�ҷ���װ�����泤120��400
    colorLayer2->setVisible(false);  // ��ʼʱ����
    colorLayer2->setLocalZOrder(102);
    m_bagSprite->addChild(colorLayer2);
    //��������
    auto label_equipped = Label::createWithSystemFont("Equipped", "Arial", 25);
    label_equipped->setTextColor(Color4B::BLACK); // ����������ɫΪ��ɫ
    label_equipped->setVisible(false);  // ��ʼʱ����
    label_equipped->setLocalZOrder(103);
    m_bagSprite->addChild(label_equipped);
    auto label_introduce = Label::createWithSystemFont("INTRODUCE:", "Arial", 25);
    label_introduce->setTextColor(Color4B::BLACK); // ����������ɫΪ��ɫ
    label_introduce->setVisible(false);  // ��ʼʱ����
    label_introduce->setLocalZOrder(103);
    m_bagSprite->addChild(label_introduce);

    //����װ����ֽ
     Sprite* equipmentSprite = Sprite::create("bag/equip.png");
     equipmentSprite->setContentSize(Size(75, 50));
     equipmentSprite->setVisible(false);
     equipmentSprite->setLocalZOrder(104);
     m_bagSprite->addChild(equipmentSprite);

     //����ɾ����ť��ֽ
     Sprite* deldtebutton1 = Sprite::create("bag/button.png");
     deldtebutton1->setContentSize(Size(20, 20));
     deldtebutton1->setVisible(false);
     deldtebutton1->setLocalZOrder(105);
     deldtebutton1->setPosition(Vec2(610, 350));
     m_bagSprite->addChild(deldtebutton1);
     Sprite* deldtebutton2 = Sprite::create("bag/button.png");
     deldtebutton2->setContentSize(Size(20, 20));
     deldtebutton2->setVisible(false);
     deldtebutton2->setLocalZOrder(105);
     deldtebutton2->setPosition(Vec2(610, 225));
     m_bagSprite->addChild(deldtebutton2);

    // �������������
    Sprite* swordSprite = Sprite::create("Me/Saber/sword.png");//����
    swordSprite->setContentSize(Size(90, 90));  // ���� Sprite �ĳߴ�
    WeaponInfo sword = { swordSprite, "small_little_sword", 100, "sword" };
    swordSprite->setPosition(Vec2(100, 400));
    swordSprite->setLocalZOrder(104);
    weapons.push_back(sword);
    m_bagSprite->addChild(swordSprite);
    Sprite* sword2Sprite = Sprite::create("bag/sword2.png");//��һ�ѳ���
    sword2Sprite->setContentSize(Size(90, 90));  // ���� Sprite �ĳߴ�
    WeaponInfo sword2 = { sword2Sprite, "the_second_little_sword", 100, "sword" };
    sword2Sprite->setPosition(Vec2(200, 400));
    sword2Sprite->setLocalZOrder(104);
    weapons.push_back(sword2);
    m_bagSprite->addChild(sword2Sprite);
    Sprite* bowSprite = Sprite::create("bag/bow.png");//��
    bowSprite->setContentSize(Size(90, 90));  // ���� Sprite �ĳߴ�
    WeaponInfo bow = { bowSprite, "the_bow", 100, "sword" };
    bowSprite->setPosition(Vec2(300, 400));
    bowSprite->setLocalZOrder(104);
    weapons.push_back(bow);
    m_bagSprite->addChild(bowSprite);
    Sprite* hammerSprite = Sprite::create("bag/hammer.png");//����
    hammerSprite->setContentSize(Size(90, 90));  // ���� Sprite �ĳߴ�
    WeaponInfo hammer = { hammerSprite, "the_hammer", 100, "sword" };
    hammerSprite->setPosition(Vec2(400, 400));
    hammerSprite->setLocalZOrder(104);
    weapons.push_back(hammer);
    m_bagSprite->addChild(hammerSprite);
    Sprite* lanceSprite = Sprite::create("bag/lance.png");//��ì
    hammerSprite->setContentSize(Size(90, 90));  // ���� Sprite �ĳߴ�
    WeaponInfo lance = { lanceSprite, "the_lance", 100, "sword" };
    lanceSprite->setPosition(Vec2(100, 300));
    lanceSprite->setLocalZOrder(104);
    weapons.push_back(lance);
    m_bagSprite->addChild(lanceSprite);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; ++j) {
            is_Fill[i][j] = 0;
        }
    }
    is_Fill[0][3] = 1; 
    is_Fill[1][3] = 2;
    is_Fill[2][3] = 3;
    is_Fill[3][3] = 4;
    is_Fill[0][2] = 5;
    is_1weaponGridEmpty = 0;
    is_2weaponGridEmpty = 0;
    is_openbag = 0;

    // ��ʼ������״̬
    _keyMap[EventKeyboard::KeyCode::KEY_LEFT_CTRL] = false;
    _keyMap[EventKeyboard::KeyCode::KEY_RIGHT_CTRL] = false;
    _keyMap[EventKeyboard::KeyCode::KEY_B] = false;

    // ���������¼�
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // ���°���״̬
            _keyMap[keyCode] = true;

            // ����Ƿ����� Ctrl+B ��ϼ�
            if ((_keyMap[EventKeyboard::KeyCode::KEY_LEFT_CTRL] || _keyMap[EventKeyboard::KeyCode::KEY_RIGHT_CTRL]) &&
                _keyMap[EventKeyboard::KeyCode::KEY_B])
            {
                
                toggleBag();  // ����� Ctrl+B ��ϼ����л���������ʾ״̬
                
            }
        };

    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // ���°���״̬
            _keyMap[keyCode] = false;
        };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);


    // �����������
    auto mouseListener = EventListenerMouse::create();

    // ����������Ļص�
    mouseListener->onMouseDown = [=](Event* event) {
        auto mouseEvent = static_cast<EventMouse*>(event);

        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            // ��ȡ�����λ��
            Vec2 clickPosition = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
            CCLOG("Mouse clicked at: x = %f, y = %f", clickPosition.x, clickPosition.y);


            Vec2 playerPos = m_bagSprite->getPosition();
            int placeX = 0;
            int placeY = 0;

            
            Rect targetArea(playerPos.x-200 , playerPos.y-200 , 400, 400);//layerê�������½ǣ�Bag����ê��������
            if (targetArea.containsPoint(clickPosition)) {
                CCLOG("Mouse clicked inside the target area!");

                placeX = (clickPosition.x - playerPos.x + 200) / 100;
                placeY = (clickPosition.y - playerPos.y + 200) / 100;
                select_x = placeX;
                select_y = placeY;
                if (placeX >= 0 && placeX <= 3 && placeY >= 0 && placeY <= 3) {
                    if (is_Fill[placeX][placeY] == 1&& is_openbag==0) {//��ȫ����
                        // ���þ��ε�λ��
                        colorLayer->setPosition(Vec2(0, -150));
                        colorLayer2->setPosition(Vec2(500, 100));
                        label_equipped->setPosition(Vec2(560, 450));
                        label_introduce->setPosition(Vec2(80, -30));
                        
                        togglelayer(colorLayer, colorLayer2, small_grid1, small_grid2);
                        toggletext(label_equipped, label_introduce, equipmentSprite);
                        equipmentSprite->setPosition(Vec2(440, -25));
                    }
                }
                
            }
            Rect buttunArea(playerPos.x+152, playerPos.y-300, 75, 50);
            if (buttunArea.containsPoint(clickPosition) && is_openbag == 1&& is_Fill[select_x][select_y] == 1) {
                if (is_1weaponGridEmpty == 0) {
                    deldtebutton1->setVisible(true);
                    
                    swordSprite->setPosition(Vec2(560, 300));
                    is_1weaponGridEmpty = is_Fill[select_x][select_y];
                    is_Fill[select_x][select_y] = 0;
                }
                else if (is_2weaponGridEmpty == 0) {
                    deldtebutton2->setVisible(true);
                    
                    swordSprite->setPosition(Vec2(560, 175));
                    is_2weaponGridEmpty = is_Fill[select_x][select_y] ;
                    is_Fill[select_x][select_y] = 0;
                }
            }
            Rect deleteArea1(playerPos.x +350, playerPos.y +90, 20, 20);
            if (deleteArea1.containsPoint(clickPosition)&& is_1weaponGridEmpty !=0&& is_openbag == 1) {
                swordSprite->setPosition(Vec2(100, 400));
                is_1weaponGridEmpty == 0;//0����գ����ִ���洢���������
                void returnweapon();
            }
            Rect deleteArea2(playerPos.x + 350, playerPos.y -25, 20, 20);
            if (deleteArea1.containsPoint(clickPosition) && is_2weaponGridEmpty != 0 && is_openbag == 1) {
                swordSprite->setPosition(Vec2(100, 400));
                is_2weaponGridEmpty == 0;
            }
        }
        
    };
    // ����������ӵ��¼��ַ���
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);


    return true;
      
}

// ��ʾ/���ر������л�����
void Bag::toggleBag()
{
    // ��������Ѿ���ʾ���������������û����ʾ������ʾ��
    if (m_bagSprite->isVisible())
    {
        m_bagSprite->setVisible(false);  // ���ر���
    }
    else
    {
        getPlayerplace();
        m_bagSprite->setVisible(true);   // ��ʾ����
    }
}
void Bag::getPlayerplace() {
    Vec2 playPos;
    if (m_player) {
        //��õ�ǰ�����λ��
        playPos = m_player->getPosition();
    }
    else {
        log("m_player not set. Exiting init.");
        return;  // ���û�д��� m_player�����˳���ʼ��
    }
    //����������λ��
    Vec2 offset(300, 0);
    m_bagSprite->setPosition(playPos + offset);
}
void Bag::togglelayer(LayerColor* colorLayer,LayerColor* colorLayer2, Sprite* small_grid1, Sprite* small_grid2) {

    // ��������Ѿ���ʾ���������������û����ʾ������ʾ��
    if (colorLayer->isVisible())
    {
        colorLayer->setVisible(false);  // ����װ������
        colorLayer2->setVisible(false);
        small_grid1->setVisible(false);
        small_grid2->setVisible(false);
    }
    else
    {
        
        colorLayer->setVisible(true);   // ��ʾװ������
        colorLayer2->setVisible(true);
        small_grid1->setVisible(true);
        small_grid2->setVisible(true);
    }
}
void Bag::toggletext(Label* label_equipped, Label* label_introduce, Sprite* equipmentSprite) {
    // ��������Ѿ���ʾ���������������û����ʾ������ʾ��
    if (label_equipped->isVisible())
    {
        label_equipped->setVisible(false);  // ����װ������
        label_introduce->setVisible(false);
        equipmentSprite->setVisible(false);
        is_openbag = 0;
    }
    else
    {

        label_equipped->setVisible(true);   // ��ʾװ������
        label_introduce->setVisible(true);
        equipmentSprite->setVisible(true);
        is_openbag = 1;
    }
}