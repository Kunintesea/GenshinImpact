#include "Effects.h"



bool Effects::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	// ���ض���
	// ��ֹ����֡



	SpriteFrame* Explode1 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode1.png", Rect(0, 0, 280, 280));//����ͼƬ·����ԭͼƬ��λ�úʹ�С
	SpriteFrame* Explode2 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode2.png", Rect(0, 0, 280, 280));
	SpriteFrame* Explode3 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode3.png", Rect(0, 0, 280, 280));
	SpriteFrame* Explode4 = SpriteFrame::create("Effects/ElementReaction/Explode/Explode4.png", Rect(0, 0, 280, 280));
	Explode.pushBack(Explode1);
	Explode.pushBack(Explode2);
	Explode.pushBack(Explode3);
	Explode.pushBack(Explode4);



	SpriteFrame* Superconducting1 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting1.png", Rect(0, 0, 200, 200));//����ͼƬ·����ͼƬ��λ�úʹ�С
	SpriteFrame* Superconducting2 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting2.png", Rect(0, 0, 200, 200));
	SpriteFrame* Superconducting3 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting3.png", Rect(0, 0, 200, 200));
	SpriteFrame* Superconducting4 = SpriteFrame::create("Effects/ElementReaction/Superconducting/Superconducting4.png", Rect(0, 0, 200, 200));
	Superconducting.pushBack(Superconducting1);
	Superconducting.pushBack(Superconducting2);
	Superconducting.pushBack(Superconducting3);
	Superconducting.pushBack(Superconducting4);

	SpriteFrame* Shocked1 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked1.png", Rect(0, 0, 200, 200));//����ͼƬ·����ͼƬ��λ�úʹ�С
	SpriteFrame* Shocked2 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked2.png", Rect(0, 0, 200, 200));
	SpriteFrame* Shocked3 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked3.png", Rect(0, 0, 200, 200));
	SpriteFrame* Shocked4 = SpriteFrame::create("Effects/ElementReaction/Shocked/Shocked4.png", Rect(0, 0, 200, 200));
	Shocked.pushBack(Shocked1);
	Shocked.pushBack(Shocked2);
	Shocked.pushBack(Shocked3);
	Shocked.pushBack(Shocked4);




	effect = Sprite::create("Effects/ElementReaction/Superconducting/Superconducting1.png");
	//���ô�СΪ��100��100
	effect->setScale(200 / effect->getContentSize().width);
	//λ��
	effect->setPosition(Vec2(0, 0));
	
	this->addChild(effect);


	
	return true;
}


void Effects::EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag) {
	//���ݴ��붯��֡�ĵ�һ֡����effect�Ĵ�С
	//effect->setScale(100 / effect->getContentSize().width);//100�������ǽ�effect�Ĵ�С��Ϊ100*100

	//���붯��֡��0,2�벥��һ֡�����ź�ɾ��
	auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);

	//auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);
	action->setTag(actionTag);
	effect->runAction(action);

}

