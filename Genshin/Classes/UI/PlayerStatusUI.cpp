#include "PlayerStatusUI.h"
#include "HelloWorldScene.h"



bool PlayerStatusUI::init()
{
      Size visibleSize = Director::getInstance()->getVisibleSize();//获取屏幕大小

	//加入背景板，在左上角
	Background = Sprite::create("Me/InfoUI/BackGround.png");//创建一个精灵
	//重设背景大小。
	Background->setScaleX(800 / Background->getContentSize().width);
	Background->setScaleY(250 / Background->getContentSize().height);



	//设置位置到屏幕左上角。横坐标是精灵的宽度的一半，纵坐标是屏幕高度减去精灵的高度的一半
	Background->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));
	this->addChild(Background);//将背景板添加到节点

	//创建角色头像
	Player_Image = Sprite::create("HelloWorld.png");//创建一个精灵
	//设置头像大小，宽高都是100
	Player_Image->setScaleX(100 / Player_Image->getContentSize().width);
	Player_Image->setScaleY(100 / Player_Image->getContentSize().height);
	Player_Image->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));
	this->addChild(Player_Image);//将精灵添加到节点

	//设置人物名字的内容
	Player_Name = Label::createWithTTF("Player", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 24);//设置内容为“Player”，字体为“Marker Felt”，大小为24
	//位置设在头像下面
	Player_Name->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	//描边
	Player_Name->enableOutline(Color4B::BLACK, 2);
	this->addChild(Player_Name);//将人物名字添加到节点

	//设置人物的等级
	Player_Level = Label::createWithTTF("Lv.1", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 24);//设置内容为“Lv.1”，字体为“Marker Felt”，大小为24
	//位置设在人物名字下面
	Player_Level->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 100));
	//描边
	Player_Level->enableOutline(Color4B::BLACK, 2);
	this->addChild(Player_Level);//将人物等级添加到节点



	//角色血条
	//创建一个血条
	Player_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));
	Player_hpBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//设置血条的类型为条形
	Player_hpBar->setType(ProgressTimer::Type::BAR);
	//设置血条的起点，从左往右
	Player_hpBar->setMidpoint(Vec2(0, 0.5));//传入两个参数，0表示x轴，0.5表示y轴，表示血条的起点在左边中间
	//设置血条的变化率
	Player_hpBar->setBarChangeRate(Vec2(1, 0));
	//设置血条的大小，长宽分别是300，30
	Player_hpBar->setScaleX(300 / Player_hpBar->getContentSize().width);
	Player_hpBar->setScaleY(30 / Player_hpBar->getContentSize().height);
	Player_hpBar_bg->setScaleX(300 / Player_hpBar_bg->getContentSize().width);
	Player_hpBar_bg->setScaleY(30 / Player_hpBar_bg->getContentSize().height);
	//设置血条的位置
	Player_hpBar->setPosition(Vec2(Player_hpBar->getContentSize().width / 2+220, Director::getInstance()->getVisibleSize().height - Player_hpBar->getContentSize().height / 2+20));
	Player_hpBar_bg->setPosition(Vec2(Player_hpBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_hpBar->getContentSize().height / 2 + 20));

	this->addChild(Player_hpBar_bg);//将血条背景添加到节点
	this->addChild(Player_hpBar);//将滑血条添加到节点


	//角色经验条
	//创建一个经验条
	Player_expBar = ProgressTimer::create(Sprite::create("Me/InfoUI/exp_bar.png"));
	Player_expBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//设置经验条的类型为条形
	Player_expBar->setType(ProgressTimer::Type::BAR);
	//设置经验条的起点，从左往右
	Player_expBar->setMidpoint(Vec2(0, 0.5));//传入两个参数，0表示x轴，0.5表示y轴，表示经验条的起点在左边中间
	//设置经验条的变化率
	Player_expBar->setBarChangeRate(Vec2(1, 0));
	//设置经验条的大小，长宽分别是300，30
	Player_expBar->setScaleX(300 / Player_expBar->getContentSize().width);
	Player_expBar->setScaleY(10 / Player_expBar->getContentSize().height);
	Player_expBar_bg->setScaleX(300 / Player_expBar_bg->getContentSize().width);
	Player_expBar_bg->setScaleY(10 / Player_expBar_bg->getContentSize().height);
	//设置经验条的位置
	Player_expBar->setPosition(Vec2(Player_expBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_expBar->getContentSize().height / 2));
	Player_expBar_bg->setPosition(Vec2(Player_expBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_expBar->getContentSize().height / 2));
	this->addChild(Player_expBar_bg);//将经验条背景添加到节点
	this->addChild(Player_expBar);//将滑经验条添加到节点


	//角色护盾条，完全覆盖在血条上
	//创建一个护盾条
	Player_shieldBar = ProgressTimer::create(Sprite::create("Me/InfoUI/shield_bar.png"));
	//设置护盾条的类型为条形
	Player_shieldBar->setType(ProgressTimer::Type::BAR);
	//设置护盾条的起点，从左往右
	Player_shieldBar->setMidpoint(Vec2(0, 0.5));//传入两个参数，0表示x轴，0.5表示y轴，表示护盾条的起点在左边中间
	//设置护盾条的变化率
	Player_shieldBar->setBarChangeRate(Vec2(1, 0));
	//设置护盾条的大小，长宽分别是300，30
	Player_shieldBar->setScaleX(300 / Player_shieldBar->getContentSize().width);
	Player_shieldBar->setScaleY(30 / Player_shieldBar->getContentSize().height);
	//设置护盾条的位置
	Player_shieldBar->setPosition(Vec2(Player_shieldBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_shieldBar->getContentSize().height / 2 + 20));	
	this->addChild(Player_shieldBar);//将滑护盾条添加到节点

	//血量标签
	Player_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 24);//设置内容为“100/100”，字体为“Marker Felt”，大小为24
	//加入黑色描边
	Player_hpLabel->enableOutline(Color4B::BLACK, 2);
	Player_hpLabel->setPosition(Vec2(Player_hpBar->getPosition().x, Player_hpBar->getPosition().y));//设置位置
	this->addChild(Player_hpLabel);//将血量标签添加到节点

	//角色体力条
//创建一个体力条
	Player_staminaBar = ProgressTimer::create(Sprite::create("Me/InfoUI/stamina_bar.png"));
	Player_staminaBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//设置体力条的类型为条形
	Player_staminaBar->setType(ProgressTimer::Type::BAR);
	//设置体力条的起点，从左往右
	Player_staminaBar->setMidpoint(Vec2(0, 0.5));//传入两个参数，0表示x轴，0.5表示y轴，表示体力条的起点在左边中间
	//设置体力条的变化率
	Player_staminaBar->setBarChangeRate(Vec2(1, 0));
	//设置体力条的大小，长宽分别是300，30
	Player_staminaBar->setScaleX(300 / Player_staminaBar->getContentSize().width);
	Player_staminaBar->setScaleY(10 / Player_staminaBar->getContentSize().height);
	Player_staminaBar_bg->setScaleX(300 / Player_staminaBar_bg->getContentSize().width);
	Player_staminaBar_bg->setScaleY(10 / Player_staminaBar_bg->getContentSize().height);
	//设置体力条的位置
	Player_staminaBar->setPosition(Vec2(Player_staminaBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_staminaBar->getContentSize().height / 2 - 10));
	Player_staminaBar_bg->setPosition(Vec2(Player_staminaBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_staminaBar->getContentSize().height / 2 - 10));

	this->addChild(Player_staminaBar_bg);//将体力条背景添加到节点
	this->addChild(Player_staminaBar);//将滑体力条添加到节点




	//元素能量条
	//创建一个能量条
	Player_mpBar = ProgressTimer::create(Sprite::create("UI/Player_Skill/Q.png"));//创建一个滑动条
	Player_mpBar_bg = Sprite::create("UI/Player_Skill/BackGround.png");//创建一个背景
	//设置能量条的类型为球形
	Player_mpBar->setType(ProgressTimer::Type::BAR);
	//设置能量条从下往上显示
	Player_mpBar->setMidpoint(Vec2(0.5, 0));//传入两个参数，0.5表示x轴，0表示y轴，表示能量条的起点在下边中间


	//设置能量条的变化率
	Player_mpBar->setBarChangeRate(Vec2(0, 1));
	//设置能量条的大小，宽高都是100
	Player_mpBar->setScaleX(100 / Player_mpBar->getContentSize().width);
	Player_mpBar->setScaleY(100 / Player_mpBar->getContentSize().height);
	Player_mpBar_bg->setScaleX(100 / Player_mpBar_bg->getContentSize().width);
	Player_mpBar_bg->setScaleY(100 / Player_mpBar_bg->getContentSize().height);
	//设置能量条的位置
	Player_mpBar->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	Player_mpBar_bg->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));

	this->addChild(Player_mpBar_bg);//将能量条背景添加到节点
	this->addChild(Player_mpBar);//将能量条添加到节点

	//设置Q技能冷却时间标签
	Player_Q_CD = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);//设置内容为“0”，字体为“Marker Felt”，大小为24
	//加入黑色描边
	Player_Q_CD->enableOutline(Color4B::BLACK, 2);
	//设置位置，与能量条的位置一样
	Player_Q_CD->setPosition(Vec2(Background->getContentSize().width + 250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	this->addChild(Player_Q_CD);//将Q技能冷却时间标签添加到节点


	//E技能
	//创建一个E技能
	Player_E = ProgressTimer::create(Sprite::create("UI/Player_Skill/E.png"));//创建一个滑动条
	Player_E_bg = Sprite::create("UI/Player_Skill/BackGround.png");//创建一个背景
	//设置E技能的类型为球形
	Player_E->setType(ProgressTimer::Type::BAR);
	//设置E技能从下往上显示
	Player_E->setMidpoint(Vec2(0.5, 0));//传入两个参数，0.5表示x轴，0表示y轴，表示E技能的起点在下边中间
	//设置E技能的变化率
	Player_E->setBarChangeRate(Vec2(0, 1));
	//设置E技能的大小，宽高都是100
	Player_E->setScaleX(100 / Player_E->getContentSize().width);
	Player_E->setScaleY(100 / Player_E->getContentSize().height);
	Player_E_bg->setScaleX(100 / Player_E_bg->getContentSize().width);
	Player_E_bg->setScaleY(100 / Player_E_bg->getContentSize().height);
	//设置E技能的位置
	Player_E->setPosition(Vec2(Background->getContentSize().width + 70, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	Player_E_bg->setPosition(Vec2(Background->getContentSize().width + 70, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));

	this->addChild(Player_E_bg);//将E技能背景添加到节点
	this->addChild(Player_E);//将E技能添加到节点

	//设置E技能冷却时间标签
	Player_E_CD = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);//设置内容为“0”，字体为“Marker Felt”，大小为24
	//加入黑色描边
	Player_E_CD->enableOutline(Color4B::BLACK, 2);
	//设置位置，与E技能的位置一样
	Player_E_CD->setPosition(Vec2(Background->getContentSize().width + 70, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	this->addChild(Player_E_CD);//将E技能冷却时间标签添加到节点

	//设置交互图标 
	// 改成Button的写法
	Interact_1 = Button::create("UI//Interact//interact_non_selected.png",
	      "UI//Interact//interact_selected.png",
	      "UI//Interact//interact_disabled.png");
	Interact_1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
	      if (type == ui::Widget::TouchEventType::ENDED) {
		    auto button = dynamic_cast<Button*>(sender);
		    int tag = button->getTag();
		    interact(tag);
	      }
	      });
	Interact_1->setPosition(Vec2(100 , - Interact_1->getContentSize().height) + visibleSize / 2 + Interact_1->getContentSize() / 2);
	Interact_1->setEnabled(false);//设置按钮不可用
	this->addChild(Interact_1);//将按钮添加到节点



	return true;
}

void PlayerStatusUI::updateUI(Player& player)
{
	//更新血条
	Player_hpBar->setPercentage(float(player.m_hp) / float(player.m_max_hp) * 100);
	//更新体力条
	Player_staminaBar->setPercentage(float(player.m_stamina) / float(player.m_max_stamina) * 100);
	//更新经验条
	Player_expBar->setPercentage(float(player.m_exp) / float(player.m_max_exp) * 100);

	//更新血量
	Player_hpLabel->setString(to_string(player.m_hp) + "/" + to_string(player.m_max_hp));
	//更新能量条
	Player_mpBar->setPercentage(float(player.m_mp) / float(player.m_max_mp) * 100);
	//更新Q技能的CD，如果是0则不显示
	if (player.m_Q_CD == 0)
	{
		Player_Q_CD->setString("");
	}
	else
	{
		//取一位小数
		Player_Q_CD->setString(to_string(player.m_Q_CD).substr(0, 3));
	}

	//更新E技能
	Player_E->setPercentage(float(player.m_max_E_CD-player.m_E_CD) / float(player.m_max_E_CD) * 100);

	//更新E技能的CD，如果是0则不显示
	if (player.m_E_CD == 0)
	{
		Player_E_CD->setString("");
	}
	else
	{
		//取一位小数，一位后的所有0都不显示
		Player_E_CD->setString(to_string(player.m_E_CD).substr(0, 3));
	}


	//更新人物名字
	Player_Name->setString(player.m_name);
	//更新护盾条
	Player_shieldBar->setPercentage(float(player.m_shield) / float(player.m_max_hp) * 100);
	//更新状态图标。检测Player.h中的m_statement数组，如果有状态就显示，没有就不显示
	//按照状态图标顺序，每次向右移动50


	for (int i = 0; i < 99; i++)
	{
	      //只要某位置的m_statement_sprite_name与m_statement的name不同，就说明状态改变了
	      if (player.m_statement[i].name != m_statement_sprite_name[i])
	      {
		    //删除原来的状态图标（如果有）
		    if (m_statement_sprite[i] != NULL)
		    {
			  this->removeChild(m_statement_sprite[i]);
			  m_statement_sprite[i] = NULL;
			  m_statement_sprite_name[i] = "";
		    }


		    //如果某位置m_statement的name是shock，且m_statement_sprite中这个位置是空的，用empty来判断
		    if (player.m_statement[i].name == "shock")
		    {
			  //创建一个状态图标
			  Sprite* temp = Sprite::create("Me/InfoUI/shock.png");
			  //设置大小
			  temp->setScale(0.3);
			  //设置位置，从背景板左下角开始，每次向右移动50
			  temp->setPosition(Vec2(Background->getContentSize().width / 2 - 40 + (i) * 50, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 145));

			  //添加到节点
			  this->addChild(temp);
			  //加入到数组
			  m_statement_sprite[i] = temp;
			  m_statement_sprite_name[i] = "shock";
		    }
		    if (player.m_statement[i].name == "def_down")
		    {
			  //创建一个状态图标
			  Sprite* temp = Sprite::create("Me/InfoUI/def_down.png");
			  //设置大小
			  temp->setScale(0.3);
			  //设置位置，从背景板左下角开始，每次向右移动50
			  temp->setPosition(Vec2(Background->getContentSize().width / 2 - 40 + (i) * 50, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 145));

			  //添加到节点
			  this->addChild(temp);
			  //加入到数组
			  m_statement_sprite[i] = temp;
			  m_statement_sprite_name[i] = "def_down";
		    }
	      }
	      else if (player.m_statement[i].name != "" && player.m_statement[i].time > 2)
	      {
		    //如果没有改变透明度，就改变透明度
		    if (m_statement_sprite[i]->getOpacity() != 255)
		    {
			  m_statement_sprite[i]->setOpacity(255);
		    }
	      }
	      else if (player.m_statement[i].name != "" && player.m_statement[i].time < 2)
	      {
		    //如果没有改变透明度，就改变透明度
		    if (m_statement_sprite[i]->getOpacity() == 255)
		    {
			  m_statement_sprite[i]->setOpacity(100);
		    }
	      }
	}

}
 
void PlayerStatusUI::updateInteractUI(Player& player) {
      mapManager* map = (mapManager*)this->getParent()->getParent()->getChildByName("mapManager");
      Vec2 spritePosition = this->getParent()->getParent()->getChildByName("Me")->getPosition();
      // 检测交互
      std::set<int> interaction = map->isInteraction(spritePosition);
      if (interaction.size() > 0)
      {
	    for (int i : interaction)
	    {
		  Interact_1->setEnabled(true);
		  Interact_1->setTag(i);
		 if (((Player*)this->getParent()->getParent()->getChildByName("Me"))->getKeyBoardState(EventKeyboard::KeyCode::KEY_F))
		       interact(i);
	    }
      }
      else
      {
	    Interact_1->setEnabled(false);
      }
}

void PlayerStatusUI::interact(int tag) {
      MapScene* map;
      auto sizeWidth = - 40 * ((mapManager*)this->getParent()->getParent()->getChildByName("mapManager"))->getTileSize();
      switch (tag) {
      case 9:
	    // 传送锚点
	    // 取消所以按键按下状态
	    ((Player*)this->getParent()->getParent()->getChildByName("Me"))->clearKeyBoardState();
	    map = MapScene::create();
	    Director::getInstance()->pushScene(map);
	    // 根据地图传送得到的位置，设置人物位置
	    break;
      case 8:
	    // 传送到室内地图
	    ((HelloWorld*)this->getParent()->getParent())->set_New_Teleport_position(Vec2(12 * sizeWidth + 800, 98 * sizeWidth + 200));
      default:
	    break;
      }
}