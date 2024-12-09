#include "Effects.h"



bool Effects::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	// ���ض���
	// ��ֹ����֡
	SpriteFrame* Explode1 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode1.png", Rect(0, 0, 100, 100));//����ͼƬ·����ͼƬ��λ�úʹ�С
	SpriteFrame* Explode2 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode2.png", Rect(0, 0,100, 100));
	SpriteFrame* Explode3 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode3.png", Rect(0, 0,100, 100));
	SpriteFrame* Explode4 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode4.png", Rect(0, 0,100, 100));
	Explode.pushBack(Explode1);
	Explode.pushBack(Explode2);
	Explode.pushBack(Explode3);
	Explode.pushBack(Explode4);

	effect = Sprite::create("grass.png");
	//���ô�СΪ��100��100
	effect->setScale(100 / effect->getContentSize().width);
	//λ��
	effect->setPosition(Vec2(0, 0));
	
	this->addChild(effect);


	
	return true;
}


void Effects::EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag) {
	//���붯��֡��0,2�벥��һ֡�����ź�ɾ��
	auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);

	//auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);
	action->setTag(actionTag);
	effect->runAction(action);

}

