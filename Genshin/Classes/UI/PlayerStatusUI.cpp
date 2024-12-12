#include "PlayerStatusUI.h"




bool PlayerStatusUI::init()
{


	//���뱳���壬�����Ͻ�
	Background = Sprite::create("Me/InfoUI/BackGround.png");//����һ������
	//���豳����С��
	Background->setScaleX(800 / Background->getContentSize().width);
	Background->setScaleY(250 / Background->getContentSize().height);



	//����λ�õ���Ļ���Ͻǡ��������Ǿ���Ŀ�ȵ�һ�룬����������Ļ�߶ȼ�ȥ����ĸ߶ȵ�һ��
	Background->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));
	this->addChild(Background);//����������ӵ��ڵ�

	//������ɫͷ��
	Player_Image = Sprite::create("HelloWorld.png");//����һ������
	//����ͷ���С����߶���100
	Player_Image->setScaleX(100 / Player_Image->getContentSize().width);
	Player_Image->setScaleY(100 / Player_Image->getContentSize().height);
	Player_Image->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));
	this->addChild(Player_Image);//��������ӵ��ڵ�

	//�����������ֵ�����
	Player_Name = Label::createWithTTF("Player", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 24);//��������Ϊ��Player��������Ϊ��Marker Felt������СΪ24
	//λ������ͷ������
	Player_Name->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	//���
	Player_Name->enableOutline(Color4B::BLACK, 2);


	this->addChild(Player_Name);//������������ӵ��ڵ�



	//��ɫѪ��
	//����һ��Ѫ��
	Player_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));
	Player_hpBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//����Ѫ��������Ϊ����
	Player_hpBar->setType(ProgressTimer::Type::BAR);
	//����Ѫ������㣬��������
	Player_hpBar->setMidpoint(Vec2(0, 0.5));//��������������0��ʾx�ᣬ0.5��ʾy�ᣬ��ʾѪ�������������м�
	//����Ѫ���ı仯��
	Player_hpBar->setBarChangeRate(Vec2(1, 0));
	//����Ѫ���Ĵ�С������ֱ���300��30
	Player_hpBar->setScaleX(300 / Player_hpBar->getContentSize().width);
	Player_hpBar->setScaleY(30 / Player_hpBar->getContentSize().height);
	Player_hpBar_bg->setScaleX(300 / Player_hpBar_bg->getContentSize().width);
	Player_hpBar_bg->setScaleY(30 / Player_hpBar_bg->getContentSize().height);
	//����Ѫ����λ��
	Player_hpBar->setPosition(Vec2(Player_hpBar->getContentSize().width / 2+220, Director::getInstance()->getVisibleSize().height - Player_hpBar->getContentSize().height / 2+20));
	Player_hpBar_bg->setPosition(Vec2(Player_hpBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_hpBar->getContentSize().height / 2 + 20));

	this->addChild(Player_hpBar_bg);//��Ѫ��������ӵ��ڵ�
	this->addChild(Player_hpBar);//����Ѫ����ӵ��ڵ�



	//��ɫ����������ȫ������Ѫ����
	//����һ��������
	Player_shieldBar = ProgressTimer::create(Sprite::create("Me/InfoUI/shield_bar.png"));
	//���û�����������Ϊ����
	Player_shieldBar->setType(ProgressTimer::Type::BAR);
	//���û���������㣬��������
	Player_shieldBar->setMidpoint(Vec2(0, 0.5));//��������������0��ʾx�ᣬ0.5��ʾy�ᣬ��ʾ�����������������м�
	//���û������ı仯��
	Player_shieldBar->setBarChangeRate(Vec2(1, 0));
	//���û������Ĵ�С������ֱ���300��30
	Player_shieldBar->setScaleX(300 / Player_shieldBar->getContentSize().width);
	Player_shieldBar->setScaleY(30 / Player_shieldBar->getContentSize().height);
	//���û�������λ��
	Player_shieldBar->setPosition(Vec2(Player_shieldBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_shieldBar->getContentSize().height / 2 + 20));	
	this->addChild(Player_shieldBar);//������������ӵ��ڵ�

	//Ѫ����ǩ
	Player_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 24);//��������Ϊ��100/100��������Ϊ��Marker Felt������СΪ24
	//�����ɫ���
	Player_hpLabel->enableOutline(Color4B::BLACK, 2);
	Player_hpLabel->setPosition(Vec2(Player_hpBar->getPosition().x, Player_hpBar->getPosition().y));//����λ��
	this->addChild(Player_hpLabel);//��Ѫ����ǩ��ӵ��ڵ�

	//��ɫ������
//����һ��������
	Player_staminaBar = ProgressTimer::create(Sprite::create("Me/InfoUI/stamina_bar.png"));
	Player_staminaBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//����������������Ϊ����
	Player_staminaBar->setType(ProgressTimer::Type::BAR);
	//��������������㣬��������
	Player_staminaBar->setMidpoint(Vec2(0, 0.5));//��������������0��ʾx�ᣬ0.5��ʾy�ᣬ��ʾ�����������������м�
	//�����������ı仯��
	Player_staminaBar->setBarChangeRate(Vec2(1, 0));
	//�����������Ĵ�С������ֱ���300��30
	Player_staminaBar->setScaleX(300 / Player_staminaBar->getContentSize().width);
	Player_staminaBar->setScaleY(10 / Player_staminaBar->getContentSize().height);
	Player_staminaBar_bg->setScaleX(300 / Player_staminaBar_bg->getContentSize().width);
	Player_staminaBar_bg->setScaleY(10 / Player_staminaBar_bg->getContentSize().height);
	//������������λ��
	Player_staminaBar->setPosition(Vec2(Player_staminaBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_staminaBar->getContentSize().height / 2 ));
	Player_staminaBar_bg->setPosition(Vec2(Player_staminaBar->getContentSize().width / 2 + 220, Director::getInstance()->getVisibleSize().height - Player_staminaBar->getContentSize().height / 2 ));

	this->addChild(Player_staminaBar_bg);//��������������ӵ��ڵ�
	this->addChild(Player_staminaBar);//������������ӵ��ڵ�




	//Ԫ��������
	//����һ��������
	Player_mpBar = ProgressTimer::create(Sprite::create("UI/Player_Skill/Q.png"));//����һ��������
	Player_mpBar_bg = Sprite::create("UI/Player_Skill/BackGround.png");//����һ������
	//����������������Ϊ����
	Player_mpBar->setType(ProgressTimer::Type::BAR);
	//��������������������ʾ
	Player_mpBar->setMidpoint(Vec2(0.5, 0));//��������������0.5��ʾx�ᣬ0��ʾy�ᣬ��ʾ��������������±��м�


	//�����������ı仯��
	Player_mpBar->setBarChangeRate(Vec2(0, 1));
	//�����������Ĵ�С����߶���100
	Player_mpBar->setScaleX(100 / Player_mpBar->getContentSize().width);
	Player_mpBar->setScaleY(100 / Player_mpBar->getContentSize().height);
	Player_mpBar_bg->setScaleX(100 / Player_mpBar_bg->getContentSize().width);
	Player_mpBar_bg->setScaleY(100 / Player_mpBar_bg->getContentSize().height);
	//������������λ��
	Player_mpBar->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	Player_mpBar_bg->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));

	this->addChild(Player_mpBar_bg);//��������������ӵ��ڵ�
	this->addChild(Player_mpBar);//����������ӵ��ڵ�

	//����Q������ȴʱ���ǩ
	Player_Q_CD = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);//��������Ϊ��0��������Ϊ��Marker Felt������СΪ24
	//�����ɫ���
	Player_Q_CD->enableOutline(Color4B::BLACK, 2);
	//����λ�ã�����������λ��һ��
	Player_Q_CD->setPosition(Vec2(Background->getContentSize().width + 250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	this->addChild(Player_Q_CD);//��Q������ȴʱ���ǩ��ӵ��ڵ�


	//E����
	//����һ��E����
	Player_E = ProgressTimer::create(Sprite::create("UI/Player_Skill/E.png"));//����һ��������
	Player_E_bg = Sprite::create("UI/Player_Skill/BackGround.png");//����һ������
	//����E���ܵ�����Ϊ����
	Player_E->setType(ProgressTimer::Type::BAR);
	//����E���ܴ���������ʾ
	Player_E->setMidpoint(Vec2(0.5, 0));//��������������0.5��ʾx�ᣬ0��ʾy�ᣬ��ʾE���ܵ�������±��м�
	//����E���ܵı仯��
	Player_E->setBarChangeRate(Vec2(0, 1));
	//����E���ܵĴ�С����߶���100
	Player_E->setScaleX(100 / Player_E->getContentSize().width);
	Player_E->setScaleY(100 / Player_E->getContentSize().height);
	Player_E_bg->setScaleX(100 / Player_E_bg->getContentSize().width);
	Player_E_bg->setScaleY(100 / Player_E_bg->getContentSize().height);
	//����E���ܵ�λ��
	Player_E->setPosition(Vec2(Background->getContentSize().width + 70, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	Player_E_bg->setPosition(Vec2(Background->getContentSize().width + 70, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));

	this->addChild(Player_E_bg);//��E���ܱ�����ӵ��ڵ�
	this->addChild(Player_E);//��E������ӵ��ڵ�

	//����E������ȴʱ���ǩ
	Player_E_CD = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);//��������Ϊ��0��������Ϊ��Marker Felt������СΪ24
	//�����ɫ���
	Player_E_CD->enableOutline(Color4B::BLACK, 2);
	//����λ�ã���E���ܵ�λ��һ��
	Player_E_CD->setPosition(Vec2(Background->getContentSize().width + 70, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 70));
	this->addChild(Player_E_CD);//��E������ȴʱ���ǩ��ӵ��ڵ�

	


	return true;
}

void PlayerStatusUI::updateUI(Player& player)
{
	//����Ѫ��
	Player_hpBar->setPercentage(float(player.m_hp) / float(player.m_max_hp) * 100);
	//����������
	Player_staminaBar->setPercentage(float(player.m_stamina) / float(player.m_max_stamina) * 100);
	//����Ѫ��
	Player_hpLabel->setString(to_string(player.m_hp) + "/" + to_string(player.m_max_hp));
	//����������
	Player_mpBar->setPercentage(float(player.m_mp) / float(player.m_max_mp) * 100);
	//����Q���ܵ�CD�������0����ʾ
	if (player.m_Q_CD == 0)
	{
		Player_Q_CD->setString("");
	}
	else
	{
		//ȡһλС��
		Player_Q_CD->setString(to_string(player.m_Q_CD).substr(0, 3));
	}

	//����E����
	Player_E->setPercentage(float(player.m_max_E_CD-player.m_E_CD) / float(player.m_max_E_CD) * 100);

	//����E���ܵ�CD�������0����ʾ
	if (player.m_E_CD == 0)
	{
		Player_E_CD->setString("");
	}
	else
	{
		//ȡһλС����һλ�������0������ʾ
		Player_E_CD->setString(to_string(player.m_E_CD).substr(0, 3));
	}


	//������������
	Player_Name->setString(player.m_name);
	//���»�����
	Player_shieldBar->setPercentage(float(player.m_shield) / float(player.m_max_hp) * 100);


}