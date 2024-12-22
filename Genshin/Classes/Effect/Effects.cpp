#include "Effects.h"



bool Effects::init()
{
      if (!Node::init())
      {
	    return false;
      }

      // 加载动画
      // 静止动画帧


      SpriteFrame* saber_normal1 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));//传入图片路径，原图片的位置和大小
      SpriteFrame* saber_normal2 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));
      SpriteFrame* saber_normal3 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));
      SpriteFrame* saber_normal4 = SpriteFrame::create("Me/Saber/Weapon/sword_light.png", Rect(0, 0, 256, 256));
      saber_normal.pushBack(saber_normal1);
      saber_normal.pushBack(saber_normal2);
      saber_normal.pushBack(saber_normal3);
      saber_normal.pushBack(saber_normal4);


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

      SpriteFrame* Evaporate1 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate1.png", Rect(0, 0, 100, 100));//传入图片路径，图片的位置和大小
      SpriteFrame* Evaporate2 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate2.png", Rect(0, 0, 100, 100));
      SpriteFrame* Evaporate3 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate3.png", Rect(0, 0, 100, 100));
      SpriteFrame* Evaporate4 = SpriteFrame::create("Effects/ElementReaction/Evaporate/Evaporate4.png", Rect(0, 0, 100, 100));
      Evaporate.pushBack(Evaporate1);
      Evaporate.pushBack(Evaporate2);
      Evaporate.pushBack(Evaporate3);
      Evaporate.pushBack(Evaporate4);

      //地狱犬爆炸，"D:\Github_Document\GenshinImpact\Genshin\proj.win32\Debug.win32\Resources\Enemy\HellDog\explosion\explosion4.png"

      for (int i = 3; i <= 21; i++)
      {
	    //图片路径
	    std::string path = "Enemy/HellDog/explosion/explosion" + std::to_string(i) + ".png";
	    //读取图片
	    SpriteFrame* HellDog_explosion1 = SpriteFrame::create(path, Rect(0, 0, 450, 450));
	    //加入到动画帧
	    HellDog_explosion.pushBack(HellDog_explosion1);
      }
      //地狱犬Q技能爆炸"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\HellDog\q_explosion\explosion2.png"，2-10
      for (int i = 2; i <= 10; i++)
      {
	    //图片路径
	    std::string path = "Enemy/HellDog/q_explosion/explosion" + std::to_string(i) + ".png";
	    //读取图片
	    SpriteFrame* HellDog_q_explosion1 = SpriteFrame::create(path, Rect(0, 0, 376, 376));
	    //加入到动画帧
	    HellDog_q_explosion.pushBack(HellDog_q_explosion1);
      }
      SpriteFrame* q1 = SpriteFrame::create("Effects/WeaponEffect/q1.png", Rect(0, 0, 512, 512));//传入图片路径，原图片的位置和大小
      SpriteFrame* q2 = SpriteFrame::create("Effects/WeaponEffect/q2.png", Rect(0, 0, 512, 512));
      SpriteFrame* q3 = SpriteFrame::create("Effects/WeaponEffect/q3.png", Rect(0, 0, 512, 512));
      SpriteFrame* q4 = SpriteFrame::create("Effects/WeaponEffect/q4.png", Rect(0, 0, 512, 512));
      q.pushBack(q1);
      q.pushBack(q2);
      q.pushBack(q3);
      q.pushBack(q4);

      SpriteFrame* bow_normal1 = SpriteFrame::create("Me/Saber/Weapon/bow_light.png", Rect(0, 0, 256, 256));//传入图片路径，原图片的位置和大小
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

      SpriteFrame* e1 = SpriteFrame::create("Effects/WeaponEffect/e.png", Rect(0, 0, 256, 256));//传入图片路径，原图片的位置和大小
      e.pushBack(e1);
      e.pushBack(e1);
      e.pushBack(e1);
      e.pushBack(e1);
      e.pushBack(e1);


      effect = Sprite::create("Effects/ElementReaction/Superconducting/Superconducting1.png");
      //设置大小为长100宽100
      effect->setScale(200 / effect->getContentSize().width);
      //位置
      effect->setPosition(Vec2(0, 0));

      this->addChild(effect);
      //"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\Bat_Fire\right_1.png"



      return true;
}

void Effects::EffectsSize(std::string mm)
{
      //根据传入的图片路径重设effect的大小
      if (mm == "Bat_Fire")
      {
	    //图像更改为火蝙蝠的火焰
	    //先把原本的effect删除
	    this->removeChild(effect);

	    effect = Sprite::create("Enemy/Bat_Fire/right_1.png");

	    //伤害类型设置为火属性
	    damage_type = Fire;

	    //设为不可见
	    effect->setVisible(false);
	    //重新加入到节点
	    this->addChild(effect);



      }
      else if (mm == "Bat_Ice")
      {
	    //图像更改为冰蝙蝠的冰柱
	    //先把原本的effect删除
	    this->removeChild(effect);
	    effect = Sprite::create("Enemy/Bat_Ice/right_1.png");
	    //伤害类型设置为冰属性
	    damage_type = Ice;
	    //设为不可见
	    effect->setVisible(false);
	    //重新加入到节点
	    this->addChild(effect);
      }
      else if (mm == "HellDog")
      {

	    //先把原本的effect删除
	    this->removeChild(effect);
	    //"D:\Github_Document\GenshinImpact\Genshin\Resources\Enemy\HellDog\down_1.png"
	    effect = Sprite::create("Enemy/HellDog/judge.png");
	    //放大5倍
	    //effect->setScale(5);

	    //伤害类型设置为火属性
	    damage_type = Fire;

	    //设为不可见
	    effect->setVisible(false);
	    //重新加入到节点
	    this->addChild(effect);
      }

}


void Effects::EffectsAnimation(Vector<SpriteFrame*> frame, int actionTag)
{
      //根据传入动画帧的第一帧重设effect的大小
      //effect->setScale(100 / effect->getContentSize().width);//100的作用是将effect的大小设为100*100



      //导入动画帧，0,2秒播放一帧，播放后删除
      auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.1f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);

      //auto action = Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 0.2f)), CallFunc::create([=] {this->removeFromParent(); }), nullptr);
      action->setTag(actionTag);
      effect->runAction(action);


}

