#include "Effects.h"



bool Effects::init()
{
      if (!Node::init())
      {
	    return false;
      }

      // ���ض���
      // ��ֹ����֡


      SpriteFrame* saber_normal1 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));//����ͼƬ·����ԭͼƬ��λ�úʹ�С
      SpriteFrame* saber_normal2 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));
      SpriteFrame* saber_normal3 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));
      SpriteFrame* saber_normal4 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));
      saber_normal.pushBack(saber_normal1);
      saber_normal.pushBack(saber_normal2);
      saber_normal.pushBack(saber_normal3);
      saber_normal.pushBack(saber_normal4);


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

      SpriteFrame* Evaporate1 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate1.png", Rect(0, 0, 100, 100));//����ͼƬ·����ͼƬ��λ�úʹ�С
      SpriteFrame* Evaporate2 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate2.png", Rect(0, 0, 100, 100));
      SpriteFrame* Evaporate3 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate3.png", Rect(0, 0, 100, 100));
      SpriteFrame* Evaporate4 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate4.png", Rect(0, 0, 100, 100));
      Evaporate.pushBack(Evaporate1);
      Evaporate.pushBack(Evaporate2);
      Evaporate.pushBack(Evaporate3);
      Evaporate.pushBack(Evaporate4);

      //����Ȯ��ը��"D:\Github_Document\GenshinImpact\Genshin\proj.win32\Debug.win32\Resources\Enemy\HellDog\explosion\explosion4.png"

      for (int i = 3; i <= 21; i++)
      {
	    //ͼƬ·��
	    std::string path = "Enemy/HellDog/explosion/explosion" + std::to_string(i) + ".png";
	    //��ȡͼƬ
	    SpriteFrame* HellDog_explosion1 = SpriteFrame::create(path, Rect(0, 0, 450, 450));
	    //���뵽����֡
	    HellDog_explosion.pushBack(HellDog_explosion1);
      }
      //����ȮQ���ܱ�ը"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\HellDog\q_explosion\explosion2.png"��2-10
      for (int i = 2; i <= 10; i++)
      {
	    //ͼƬ·��
	    std::string path = "Enemy/HellDog/q_explosion/explosion" + std::to_string(i) + ".png";
	    //��ȡͼƬ
	    SpriteFrame* HellDog_q_explosion1 = SpriteFrame::create(path, Rect(0, 0, 376, 376));
	    //���뵽����֡
	    HellDog_q_explosion.pushBack(HellDog_q_explosion1);
      }
      SpriteFrame* q1 = SpriteFrame::create("Effects/WeaponEffect/q1.png", Rect(0, 0, 512, 512));//����ͼƬ·����ԭͼƬ��λ�úʹ�С
      SpriteFrame* q2 = SpriteFrame::create("Effects/WeaponEffect/q2.png", Rect(0, 0, 512, 512));
      SpriteFrame* q3 = SpriteFrame::create("Effects/WeaponEffect/q3.png", Rect(0, 0, 512, 512));
      SpriteFrame* q4 = SpriteFrame::create("Effects/WeaponEffect/q4.png", Rect(0, 0, 512, 512));
      q.pushBack(q1);
      q.pushBack(q2);
      q.pushBack(q3);
      q.pushBack(q4);

      SpriteFrame* bow_normal1 = SpriteFrame::create("Me/Saber/Weapon/bow_light.png", Rect(0, 0, 256, 256));//����ͼƬ·����ԭͼƬ��λ�úʹ�С
      SpriteFrame* bow_normal2 = SpriteFrame::create("Me/Saber/Weapon/bow_light.png", Rect(0, 0, 256, 256));
      SpriteFrame* bow_normal3 = SpriteFrame::create("Me/Saber/Weapon/bow_light.png", Rect(0, 0, 256, 256));
      SpriteFrame* bow_normal4 = SpriteFrame::create("Me/Saber/Weapon/bow_light.png", Rect(0, 0, 256, 256));
      bow_normal.pushBack(bow_normal1);
      bow_normal.pushBack(bow_normal2);
      bow_normal.pushBack(bow_normal3);
      bow_normal.pushBack(bow_normal4);

      SpriteFrame* q_bow1 = SpriteFrame::create("Effects/WeaponEffect/q_bow1.png", Rect(0, 0, 400, 400));
      SpriteFrame* q_bow2 = SpriteFrame::create("Effects/WeaponEffect/q_bow2.png", Rect(0, 0, 400, 400));
      SpriteFrame* q_bow3 = SpriteFrame::create("Effects/WeaponEffect/q_bow3.png", Rect(0, 0, 400, 400));
      SpriteFrame* q_bow4 = SpriteFrame::create("Effects/WeaponEffect/q_bow4.png", Rect(0, 0, 400, 400));
      SpriteFrame* q_bow5 = SpriteFrame::create("Effects/WeaponEffect/q_bow5.png", Rect(0, 0, 400, 400));
      q_bow.pushBack(q_bow1);
      q_bow.pushBack(q_bow2);
      q_bow.pushBack(q_bow3);
      q_bow.pushBack(q_bow4);
      q_bow.pushBack(q_bow5);

      SpriteFrame* e1 = SpriteFrame::create("Effects/WeaponEffect/e.png", Rect(0, 0, 256, 256));//����ͼƬ·����ԭͼƬ��λ�úʹ�С
      e.pushBack(e1);
      e.pushBack(e1);
      e.pushBack(e1);
      e.pushBack(e1);
      e.pushBack(e1);


      effect = Sprite::create("Effects/ElementReaction/Superconducting/Superconducting1.png");
      //���ô�СΪ��100��100
      effect->setScale(200 / effect->getContentSize().width);
      //λ��
      effect->setPosition(Vec2(0, 0));

      this->addChild(effect);
      //"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\Bat_Fire\right_1.png"



      return true;
}

void Effects::EffectsSize(std::string mm)
{
      //���ݴ����ͼƬ·������effect�Ĵ�С
      if (mm == "Bat_Fire")
      {
	    //ͼ�����Ϊ������Ļ���
	    //�Ȱ�ԭ����effectɾ��
	    this->removeChild(effect);

	    effect = Sprite::create("Enemy/Bat_Fire/right_1.png");

	    //�˺���������Ϊ������
	    damage_type = Fire;

	    //��Ϊ���ɼ�
	    effect->setVisible(false);
	    //���¼��뵽�ڵ�
	    this->addChild(effect);



      }
      else if (mm == "Bat_Ice")
      {
	    //ͼ�����Ϊ������ı���
	    //�Ȱ�ԭ����effectɾ��
	    this->removeChild(effect);
	    effect = Sprite::create("Enemy/Bat_Ice/right_1.png");
	    //�˺���������Ϊ������
	    damage_type = Ice;
	    //��Ϊ���ɼ�
	    effect->setVisible(false);
	    //���¼��뵽�ڵ�
	    this->addChild(effect);
      }
      else if (mm == "HellDog")
      {

	    //�Ȱ�ԭ����effectɾ��
	    this->removeChild(effect);
	    //"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\HellDog\down_1.png"
	    effect = Sprite::create("Enemy/HellDog/judge.png");
	    //�Ŵ�5��
	    //effect->setScale(5);

	    //�˺���������Ϊ������
	    damage_type = Fire;

	    //��Ϊ���ɼ�
	    effect->setVisible(false);
	    //���¼��뵽�ڵ�
	    this->addChild(effect);
      }

}


void Effects::EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag)
{
      //���ݴ��붯��֡�ĵ�һ֡����effect�Ĵ�С
      //effect->setScale(100 / effect->getContentSize().width);//100�������ǽ�effect�Ĵ�С��Ϊ100*100



      //���붯��֡��0,2�벥��һ֡�����ź�ɾ��
      auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);

      //auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);
      action->setTag(actionTag);
      effect->runAction(action);


}

