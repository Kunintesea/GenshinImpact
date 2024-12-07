#include "UI/PlayerStatusUI.h"
#include "Player/Player.h"

bool PlayerStatusUI::init()
{
	//���뱳���壬�����Ͻ�
	Background = Sprite::create("Me/InfoUI/BackGround.png");//����һ������
	//���豳����С����Ϊ��500����250
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

	//Ѫ����ǩ
	Player_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 24);//��������Ϊ��100/100��������Ϊ��Marker Felt������СΪ24
	Player_hpLabel->setPosition(Vec2(Player_hpBar->getPosition().x, Player_hpBar->getPosition().y));//����λ��
	this->addChild(Player_hpLabel);//��Ѫ����ǩ��ӵ��ڵ�

	//UI\Player_Skill
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
	Player_mpBar->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 50));
	Player_mpBar_bg->setPosition(Vec2(Background->getContentSize().width+250, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2 - 50));

	this->addChild(Player_mpBar_bg);//��������������ӵ��ڵ�
	this->addChild(Player_mpBar);//����������ӵ��ڵ�



	return true;
}

void PlayerStatusUI::updateUI(Player& player)
{
	//����Ѫ��
	Player_hpBar->setPercentage(float(player.m_hp) / float(player.m_max_hp) * 100);
	//����Ѫ��
	Player_hpLabel->setString(to_string(player.m_hp) + "/" + to_string(player.m_max_hp));
	//����������
	Player_mpBar->setPercentage(float(player.m_mp) / float(player.m_max_mp) * 100);
	//������������
	Player_Name->setString(player.m_name);
}