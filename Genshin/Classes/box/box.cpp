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

// 初始化方法
bool TreasureChest::init(const std::string& closedImage, const std::string& openedImage)
{
    if (!Node::init()) 
    {
        return false;
    }

    // 设置贴图路径
    _closedImage = closedImage;
    _openedImage = openedImage;
    _isOpen = false;

    // 创建精灵并加载关闭状态图片
    _chestSprite = Sprite::create(_closedImage);
    if (!_chestSprite) 
    {
        return false;
    }

    // 将精灵添加为子节点
    this->addChild(_chestSprite);

    return true;
}

// 打开宝箱
void TreasureChest::open()
{
    if (!_isOpen) 
    {
        _chestSprite->setTexture(_openedImage);
        _isOpen = true;
        // 此处添加打开后逻辑！！！！




        CCLOG("宝箱已打开");
    }
}

// 关闭宝箱
void TreasureChest::close()
{
    if (_isOpen) 
    {
        _chestSprite->setTexture(_closedImage);
        _isOpen = false;
        // 可添加关闭动画或音效
        CCLOG("宝箱已关闭");
    }
}

// 检查宝箱是否打开
bool TreasureChest::isOpen() const 
{
    return _isOpen;
}
