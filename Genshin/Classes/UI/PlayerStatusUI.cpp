#include "PlayerStatusUI.h"




bool PlayerStatusUI::init()
{
	//设置人物名字的内容
	m_name.setString("Player");
	//设置人物名字的位置
	m_name.setPosition(Vec2(100, 100));//设置人物名字的位置，在屏幕的（100，100）位置


	return true;
}