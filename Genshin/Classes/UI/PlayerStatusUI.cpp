#include "PlayerStatusUI.h"




bool PlayerStatusUI::init()
{
	//�����������ֵ�����
	//Player_Name = Label::createWithTTF("Player", "fonts/Marker Felt.ttf", 24);//��������Ϊ��Player��������Ϊ��Marker Felt������СΪ24
	//Player_Name->setPosition(Vec2(0, 0));//����λ��
	//this->addChild(Player_Name);//������������ӵ��ڵ�

	//���뱳���壬�����Ͻ�
	Background = Sprite::create("Me/InfoUI/BackGround.png");//����һ������
	//���豳����С����Ϊ��500����250
	Background->setScaleX(500 / Background->getContentSize().width);
	Background->setScaleY(250 / Background->getContentSize().height);

	//����λ�õ���Ļ���Ͻǡ��������Ǿ���Ŀ�ȵ�һ�룬����������Ļ�߶ȼ�ȥ����ĸ߶ȵ�һ��
	Background->setPosition(Vec2(Background->getContentSize().width / 2, Director::getInstance()->getVisibleSize().height - Background->getContentSize().height / 2));

	//����Ļ����ʾ����Ѫ��


	this->addChild(Background);//����������ӵ��ڵ�


	Player_Image = Sprite::create("HelloWorld.png");//����һ������
	Player_Image->setPosition(Vec2(100, 100));//����λ��
	this->addChild(Player_Image);//��������ӵ��ڵ�
	/*
	
	//��������ϢUI��ʾ����Ļ�ϣ��趨��ʾ�����Ͻ�
	//D:\Github_Document\GenshinImpact\Genshin\Resources\Me\InfoUI
	playerUI.Player_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));//����һ��Ѫ��
	playerUI.Player_hpBar->setType(ProgressTimer::Type::BAR);//����Ѫ��������Ϊ����
	playerUI.Player_hpBar->setMidpoint(Vec2(0, 0.5));//����Ѫ�������
	playerUI.Player_hpBar->setPercentage(m_hp / m_max_hp * 100);//��Ѫ���İٷֱȵ��ڵ�ǰѪ���������Ѫ��
	playerUI.Player_hpBar->setBarChangeRate(Vec2(1, 0));//����Ѫ���ı仯��
	playerUI.Player_hpBar->setPosition(Vec2(0, 0));//����Ѫ����λ��
	//����Ѫ���Ĵ�С������ֱ���100��10
	playerUI.Player_hpBar->setScaleX(100 / playerUI.Player_hpBar->getContentSize().width);
	playerUI.Player_hpBar->setScaleY(10 / playerUI.Player_hpBar->getContentSize().height);
	this->addChild(playerUI.Player_hpBar);//����Ѫ����ӵ��ڵ�

	*/


	return true;
}