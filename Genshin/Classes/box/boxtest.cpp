#include "boxtest.h"


Treasurebox* Treasurebox::create(const std::string& closedImage, const std::string& openedImage)
{
    Treasurebox* chest = new (std::nothrow) Treasurebox();
    if (chest && chest->init(closedImage, openedImage))
    {
        chest->autorelease();
        return chest;
    }
    delete chest;
    return nullptr;
}

// ��ʼ������
bool Treasurebox::init(const std::string& closedImage, const std::string& openedImage)
{
    if (!Node::init())
    {
        return false;
    }

    // ������ͼ·��
    _closedImage = closedImage;
    _openedImage = openedImage;
    _isOpen = false;

    // �������鲢���عر�״̬ͼƬ
    _chestSprite = Sprite::create(_closedImage);
    if (!_chestSprite)
    {
        return false;
    }

    // ���������Ϊ�ӽڵ�
    this->addChild(_chestSprite);

	if (!Node::init())
	{
		return false;
	}
	//���������
	this->scheduleUpdate();//��������ÿ֡����һ��update����


	//��������
	m_body = Sprite::create("box/chest_close.png");
	//��������ӵ��ڵ�
	this->addChild(m_body);


	//����ͷ����ʾԪ�ظ���
	//��ʼ��Ԫ�ظ��š����ֻ��һ��Ԫ�ظ��ž���ʾ�����Ϸ��������������������Ϸ�����������
	for (int i = 0; i < 2; i++)
	{
		m_element_sprite[i] = Sprite::create("Effects/Element/Rock.png");
		m_element_sprite[i]->setScale(0.4);
		m_element_sprite[i]->setVisible(false);
		//Ĭ�����������Ϸ�
		m_element_sprite[i]->setPosition(Vec2(this->getPositionX(), this->getPositionY() + m_body->getContentSize().height * 2));
		this->addChild(m_element_sprite[i]);
	}


	//���˺�������Ԫ�ط�Ӧ���ֳ�ʼ��
	for (int i = 0; i < 20; i++)
	{
		//��ʼ��Ԫ�ط�Ӧ���֣�֧������
		m_element_label[i] = Label::createWithTTF("��Ӧ", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 40);
		m_damage_label[i] = Label::createWithTTF("0", "fonts/HarmonyOS_Sans_SC_Medium.TTF", 30);
		//�Ӻ�ɫ���
		m_element_label[i]->enableOutline(Color4B::BLACK, 2);
		m_damage_label[i]->enableOutline(Color4B::BLACK, 2);
		m_element_label[i]->setVisible(false);//���ò��ɼ�
		m_damage_label[i]->setVisible(false);//���ò��ɼ�
	}



	//��ɫѪ��
	//����һ��Ѫ��
	Enemy_hpBar = ProgressTimer::create(Sprite::create("Me/InfoUI/hp_bar.png"));
	Enemy_hpBar_bg = Sprite::create("Me/InfoUI/hp_bar_bg.png");
	//����Ѫ��������Ϊ����
	Enemy_hpBar->setType(ProgressTimer::Type::BAR);
	//����Ѫ������㣬��������
	Enemy_hpBar->setMidpoint(Vec2(0, 0.5));//��������������0��ʾx�ᣬ0.5��ʾy�ᣬ��ʾѪ�������������м�
	//����Ѫ���ı仯��
	Enemy_hpBar->setBarChangeRate(Vec2(1, 0));
	//����Ѫ���Ĵ�С������ֱ���200��30
	Enemy_hpBar->setScaleX(100 / Enemy_hpBar->getContentSize().width);
	Enemy_hpBar->setScaleY(10 / Enemy_hpBar->getContentSize().height);
	Enemy_hpBar_bg->setScaleX(100 / Enemy_hpBar_bg->getContentSize().width);
	Enemy_hpBar_bg->setScaleY(10 / Enemy_hpBar_bg->getContentSize().height);
	//����Ѫ����λ�ã���������ͷ��
	Enemy_hpBar->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));
	Enemy_hpBar_bg->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));


	this->addChild(Enemy_hpBar_bg);//��Ѫ��������ӵ��ڵ�
	this->addChild(Enemy_hpBar);//����Ѫ����ӵ��ڵ�

	//Ѫ����ǩ
	Enemy_hpLabel = Label::createWithTTF("100/100", "fonts/Marker Felt.ttf", 12);//��������Ϊ��100/100��������Ϊ��Marker Felt������СΪ24
	//�����ɫ���
	Enemy_hpLabel->enableOutline(Color4B::BLACK, 2);
	//����λ�ã���Ѫ����λ��һ��
	Enemy_hpLabel->setPosition(Vec2(0, this->getPositionY() + m_body->getContentSize().height));
	this->addChild(Enemy_hpLabel);//��Ѫ����ǩ��ӵ��ڵ�


	//���������

	return true;
}


void Treasurebox::update(float t)
{
	log("dxcgfvhbjn");
	//����Ѫ��
	Enemy_hpBar->setPercentage(float(m_hp) / float(m_max_hp) * 100);
	//����Ѫ��
	Enemy_hpLabel->setString(std::to_string(m_hp) + "/" + std::to_string(m_max_hp));

	//���������ֱ�Ӱ�״̬ȫ�����
	if (isDead)
	{
		for (int i = 0; i < 99; i++)
		{
			m_statement[i].name = "";
			m_statement_time[i] = 0;
		}
		open();
	}

}

// �򿪱���
void Treasurebox::open()
{
    if (!_isOpen)
    {
        _chestSprite->setTexture(_openedImage);
        _isOpen = true;
        // �˴���Ӵ򿪺��߼���������




        CCLOG("�����Ѵ�");
    }
}

// �رձ���
void Treasurebox::close()
{
    if (_isOpen)
    {
        _chestSprite->setTexture(_closedImage);
        _isOpen = false;
        // ����ӹرն�������Ч
        CCLOG("�����ѹر�");
    }
}

// ��鱦���Ƿ��
bool Treasurebox::isOpen() const
{
    return _isOpen;
}
