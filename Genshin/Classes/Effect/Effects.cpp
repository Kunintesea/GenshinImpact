#include "Effects.h"



bool Effects::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	// 加载动画
	// 静止动画帧
	SpriteFrame* Explode1 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode1.png", Rect(0, 0, 100, 100));//传入图片路径，图片的位置和大小
	SpriteFrame* Explode2 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode2.png", Rect(0, 0,100, 100));
	SpriteFrame* Explode3 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode3.png", Rect(0, 0,100, 100));
	SpriteFrame* Explode4 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode4.png", Rect(0, 0,100, 100));
	Explode.pushBack(Explode1);
	Explode.pushBack(Explode2);
	Explode.pushBack(Explode3);
	Explode.pushBack(Explode4);

	effect = Sprite::create("grass.png");
	//设置大小为长100宽100
	effect->setScale(100 / effect->getContentSize().width);
	//位置
	effect->setPosition(Vec2(0, 0));
	
	this->addChild(effect);


	
	return true;
}


void Effects::EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag) {
	//导入动画帧，0,2秒播放一帧，播放后删除
	auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);

	//auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);
	action->setTag(actionTag);
	effect->runAction(action);

}

