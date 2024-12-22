#include "box.h"


TreasureChest* TreasureChest::create(const std::string& closedImage, const std::string& openedImage)
{
    TreasureChest* chest = new (std::nothrow) TreasureChest();
    if (chest && chest->init(closedImage, openedImage))
    {
        chest->autorelease();
        return chest;
    }
    delete chest;
    return nullptr;
}

// ��ʼ������
bool TreasureChest::init(const std::string& closedImage, const std::string& openedImage)
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

    return true;
}

// �򿪱���
void TreasureChest::open()
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
void TreasureChest::close()
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
bool TreasureChest::isOpen() const 
{
    return _isOpen;
}
