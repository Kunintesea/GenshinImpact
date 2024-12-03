#include "cocos2d.h"
#include "Player\Player.h"
#include "ui/CocosGUI.h"
#include <string>

using namespace std;
USING_NS_CC;
class PlayerStatusUI : public Node
{
public:

	virtual bool init();

	CREATE_FUNC(PlayerStatusUI);
private:
	//�������Եı�ǩ
	Label m_name;
	Label m_hp_label;
	Label m_mp_label;//����ħ��ֵ

	//�������Ե�slider
	ui::Slider* m_hp_slider;//����Ѫ��
	ui::Slider* m_mp_slider;//����ħ��ֵ��

};
