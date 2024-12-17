/*武器编号，对应is_Fill数组中的存储1-5和weapon数组
1、直长剑
2、倾斜剑
3、弓
4、锤子
5、长矛*/



#include "bag.h"
#include "cocos2d.h"
#include "Player/Player.h"  // 确保正确包含 Player.h 文件
#include "ui/CocosGUI.h"

// 背包初始化方法
bool Bag::init() {
    if (!Node::init()) {  // 调用父类的初始化方法
        return false;
    }
    m_bagSprite = Sprite::create("bag/bag_background.png");
        
    // 检查 m_bagSprite 是否成功创建
    if (m_bagSprite == nullptr)
    {
        log("m_bagSprite not set. Exiting init.");
        return false;  // 如果没有传递 m_bagSprite，就退出初始化
    }
    
    if (m_bagSprite) {
        m_bagSprite->setLocalZOrder(100);  // 确保背包精灵在最上层
        
        // 设置背包界面的尺寸（根据实际需求
        m_bagSprite->setContentSize(Size(500, 500));  // 设置 Sprite 的尺寸
               
    }
   
    // 默认背包界面隐藏
    m_bagSprite->setVisible(false);  // 初始时隐藏背包

    this->addChild(m_bagSprite);
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
        auto small_grid = Sprite::create("bag/smallbaggrid.png");
        // 检查 small_grid是否成功创建
        if (small_grid == nullptr)
        {
            log("small_grid not set. Exiting init.");
            return false; 
        }
        small_grid->setContentSize(Size(100, 100));  // 设置 Sprite 的尺寸
        small_grid->setLocalZOrder(101);
        small_grid->setPosition(Vec2(i*100+100, 400-j*100)); // 相对主图片的偏移位置
        m_bagSprite->addChild(small_grid);
        }
    }

    auto small_grid1 = Sprite::create("bag/smallbaggrid.png");
    if (small_grid1 == nullptr)
    {
        log("small_grid not set. Exiting init.");
        return false;  
    }
    small_grid1->setContentSize(Size(100, 100));  // 设置 Sprite 的尺寸
    small_grid1->setLocalZOrder(103);
    small_grid1->setPosition(Vec2(560, 300)); // 相对主图片的偏移位置
    small_grid1->setVisible(false);
    m_bagSprite->addChild(small_grid1);
    auto small_grid2 = Sprite::create("bag/smallbaggrid.png");
    if (small_grid2 == nullptr)
    {
        log("small_grid not set. Exiting init.");
        return false;
    }
    small_grid2->setContentSize(Size(100, 100));  // 设置 Sprite 的尺寸
    small_grid2->setLocalZOrder(103);
    small_grid2->setPosition(Vec2(560, 175)); // 相对主图片的偏移位置
    small_grid2->setVisible(false);
    m_bagSprite->addChild(small_grid2);
    // 创建两个米黄色的矩形
    auto colorLayer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 245, 220, 255), 400, 150);//下方的装备界面长400宽150
    colorLayer->setVisible(false);  // 初始时隐藏
    colorLayer->setLocalZOrder(102);  
    m_bagSprite->addChild(colorLayer);

    auto colorLayer2 = cocos2d::LayerColor::create(cocos2d::Color4B(255, 245, 220, 255), 120, 400);//右方的装备界面长120宽400
    colorLayer2->setVisible(false);  // 初始时隐藏
    colorLayer2->setLocalZOrder(102);
    m_bagSprite->addChild(colorLayer2);
    //创建文字
    auto label_equipped = Label::createWithSystemFont("Equipped", "Arial", 25);
    label_equipped->setTextColor(Color4B::BLACK); // 设置文字颜色为黑色
    label_equipped->setVisible(false);  // 初始时隐藏
    label_equipped->setLocalZOrder(103);
    m_bagSprite->addChild(label_equipped);
    auto label_introduce = Label::createWithSystemFont("INTRODUCE:", "Arial", 25);
    label_introduce->setTextColor(Color4B::BLACK); // 设置文字颜色为黑色
    label_introduce->setVisible(false);  // 初始时隐藏
    label_introduce->setLocalZOrder(103);
    m_bagSprite->addChild(label_introduce);

    //创建装备贴纸
     Sprite* equipmentSprite = Sprite::create("bag/equip.png");
     equipmentSprite->setContentSize(Size(75, 50));
     equipmentSprite->setVisible(false);
     equipmentSprite->setLocalZOrder(104);
     m_bagSprite->addChild(equipmentSprite);

     //创建删除按钮贴纸
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

    // 创建并添加武器
    Sprite* swordSprite = Sprite::create("Me/Saber/sword.png");//长剑
    swordSprite->setContentSize(Size(90, 90));  // 设置 Sprite 的尺寸
    WeaponInfo sword = { swordSprite, "small_little_sword", 100, "sword" };
    swordSprite->setPosition(Vec2(100, 400));
    swordSprite->setLocalZOrder(104);
    weapons.push_back(sword);
    m_bagSprite->addChild(swordSprite);
    Sprite* sword2Sprite = Sprite::create("bag/sword2.png");//另一把长剑
    sword2Sprite->setContentSize(Size(90, 90));  // 设置 Sprite 的尺寸
    WeaponInfo sword2 = { sword2Sprite, "the_second_little_sword", 100, "sword" };
    sword2Sprite->setPosition(Vec2(200, 400));
    sword2Sprite->setLocalZOrder(104);
    weapons.push_back(sword2);
    m_bagSprite->addChild(sword2Sprite);
    Sprite* bowSprite = Sprite::create("bag/bow.png");//弓
    bowSprite->setContentSize(Size(90, 90));  // 设置 Sprite 的尺寸
    WeaponInfo bow = { bowSprite, "the_bow", 100, "sword" };
    bowSprite->setPosition(Vec2(300, 400));
    bowSprite->setLocalZOrder(104);
    weapons.push_back(bow);
    m_bagSprite->addChild(bowSprite);
    Sprite* hammerSprite = Sprite::create("bag/hammer.png");//锤子
    hammerSprite->setContentSize(Size(90, 90));  // 设置 Sprite 的尺寸
    WeaponInfo hammer = { hammerSprite, "the_hammer", 100, "sword" };
    hammerSprite->setPosition(Vec2(400, 400));
    hammerSprite->setLocalZOrder(104);
    weapons.push_back(hammer);
    m_bagSprite->addChild(hammerSprite);
    Sprite* lanceSprite = Sprite::create("bag/lance.png");//长矛
    hammerSprite->setContentSize(Size(90, 90));  // 设置 Sprite 的尺寸
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

    // 初始化按键状态
    _keyMap[EventKeyboard::KeyCode::KEY_LEFT_CTRL] = false;
    _keyMap[EventKeyboard::KeyCode::KEY_RIGHT_CTRL] = false;
    _keyMap[EventKeyboard::KeyCode::KEY_B] = false;

    // 监听键盘事件
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 更新按键状态
            _keyMap[keyCode] = true;

            // 检查是否按下了 Ctrl+B 组合键
            if ((_keyMap[EventKeyboard::KeyCode::KEY_LEFT_CTRL] || _keyMap[EventKeyboard::KeyCode::KEY_RIGHT_CTRL]) &&
                _keyMap[EventKeyboard::KeyCode::KEY_B])
            {
                
                toggleBag();  // 如果是 Ctrl+B 组合键，切换背包的显示状态
                
            }
        };

    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            // 更新按键状态
            _keyMap[keyCode] = false;
        };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);


    // 添加鼠标监听器
    auto mouseListener = EventListenerMouse::create();

    // 设置鼠标点击的回调
    mouseListener->onMouseDown = [=](Event* event) {
        auto mouseEvent = static_cast<EventMouse*>(event);

        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
            // 获取鼠标点击位置
            Vec2 clickPosition = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
            CCLOG("Mouse clicked at: x = %f, y = %f", clickPosition.x, clickPosition.y);


            Vec2 playerPos = m_bagSprite->getPosition();
            int placeX = 0;
            int placeY = 0;

            
            Rect targetArea(playerPos.x-200 , playerPos.y-200 , 400, 400);//layer锚点在左下角，Bag精灵锚点在中心
            if (targetArea.containsPoint(clickPosition)) {
                CCLOG("Mouse clicked inside the target area!");

                placeX = (clickPosition.x - playerPos.x + 200) / 100;
                placeY = (clickPosition.y - playerPos.y + 200) / 100;
                select_x = placeX;
                select_y = placeY;
                if (placeX >= 0 && placeX <= 3 && placeY >= 0 && placeY <= 3) {
                    if (is_Fill[placeX][placeY] == 1&& is_openbag==0) {//安全访问
                        // 设置矩形的位置
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
                is_1weaponGridEmpty == 0;//0代表空，数字代表存储的武器编号
                void returnweapon();
            }
            Rect deleteArea2(playerPos.x + 350, playerPos.y -25, 20, 20);
            if (deleteArea1.containsPoint(clickPosition) && is_2weaponGridEmpty != 0 && is_openbag == 1) {
                swordSprite->setPosition(Vec2(100, 400));
                is_2weaponGridEmpty == 0;
            }
        }
        
    };
    // 将监听器添加到事件分发器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);


    return true;
      
}

// 显示/隐藏背包的切换方法
void Bag::toggleBag()
{
    // 如果背包已经显示，就隐藏它；如果没有显示，就显示它
    if (m_bagSprite->isVisible())
    {
        m_bagSprite->setVisible(false);  // 隐藏背包
    }
    else
    {
        getPlayerplace();
        m_bagSprite->setVisible(true);   // 显示背包
    }
}
void Bag::getPlayerplace() {
    Vec2 playPos;
    if (m_player) {
        //获得当前精灵的位置
        playPos = m_player->getPosition();
    }
    else {
        log("m_player not set. Exiting init.");
        return;  // 如果没有传递 m_player，就退出初始化
    }
    //设置相对玩家位置
    Vec2 offset(300, 0);
    m_bagSprite->setPosition(playPos + offset);
}
void Bag::togglelayer(LayerColor* colorLayer,LayerColor* colorLayer2, Sprite* small_grid1, Sprite* small_grid2) {

    // 如果界面已经显示，就隐藏它；如果没有显示，就显示它
    if (colorLayer->isVisible())
    {
        colorLayer->setVisible(false);  // 隐藏装备界面
        colorLayer2->setVisible(false);
        small_grid1->setVisible(false);
        small_grid2->setVisible(false);
    }
    else
    {
        
        colorLayer->setVisible(true);   // 显示装备界面
        colorLayer2->setVisible(true);
        small_grid1->setVisible(true);
        small_grid2->setVisible(true);
    }
}
void Bag::toggletext(Label* label_equipped, Label* label_introduce, Sprite* equipmentSprite) {
    // 如果界面已经显示，就隐藏它；如果没有显示，就显示它
    if (label_equipped->isVisible())
    {
        label_equipped->setVisible(false);  // 隐藏装备界面
        label_introduce->setVisible(false);
        equipmentSprite->setVisible(false);
        is_openbag = 0;
    }
    else
    {

        label_equipped->setVisible(true);   // 显示装备界面
        label_introduce->setVisible(true);
        equipmentSprite->setVisible(true);
        is_openbag = 1;
    }
}