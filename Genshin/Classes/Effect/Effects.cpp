#include "Effects.h"



bool Effects::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	// 加载动画
	// 静止动画帧



	SpriteFrame* Explode1 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode1.png", Rect(0, 0, 280, 280));//传入图片路径，原图片的位置和大小
	SpriteFrame* Explode2 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode2.png", Rect(0, 0, 280, 280));
	SpriteFrame* Explode3 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode3.png", Rect(0, 0, 280, 280));
	SpriteFrame* Explode4 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode4.png", Rect(0, 0, 280, 280));
	Explode.pushBack(Explode1);
	Explode.pushBack(Explode2);
	Explode.pushBack(Explode3);
	Explode.pushBack(Explode4);



	SpriteFrame* Superconducting1 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting1.png", Rect(0, 0, 200, 200));//传入图片路径，图片的位置和大小
	SpriteFrame* Superconducting2 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting2.png", Rect(0, 0, 200, 200));
	SpriteFrame* Superconducting3 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting3.png", Rect(0, 0, 200, 200));
	SpriteFrame* Superconducting4 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting4.png", Rect(0, 0, 200, 200));
	Superconducting.pushBack(Superconducting1);
	Superconducting.pushBack(Superconducting2);
	Superconducting.pushBack(Superconducting3);
	Superconducting.pushBack(Superconducting4);

	SpriteFrame* Shocked1 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked1.png", Rect(0, 0, 200, 200));//传入图片路径，图片的位置和大小
	SpriteFrame* Shocked2 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked2.png", Rect(0, 0, 200, 200));
	SpriteFrame* Shocked3 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked3.png", Rect(0, 0, 200, 200));
	SpriteFrame* Shocked4 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked4.png", Rect(0, 0, 200, 200));
	Shocked.pushBack(Shocked1);
	Shocked.pushBack(Shocked2);
	Shocked.pushBack(Shocked3);
	Shocked.pushBack(Shocked4);




	effect = Sprite::create("Effects/ElementReaction/Superconducting/Superconducting1.png");
	//设置大小为长100宽100
	effect->setScale(200 / effect->getContentSize().width);
	//位置
	effect->setPosition(Vec2(0, 0));
	
	this->addChild(effect);


	
	return true;
}


void Effects::EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag) {
	//根据传入动画帧的第一帧重设effect的大小
	//effect->setScale(100 / effect->getContentSize().width);//100的作用是将effect的大小设为100*100

	//导入动画帧，0,2秒播放一帧，播放后删除
	auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);

	//auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);
	action->setTag(actionTag);
	effect->runAction(action);

}

