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
	//人物属性的标签
	Label m_name;
	Label m_hp_label;
	Label m_mp_label;//人物魔法值

	//人物属性的slider
	ui::Slider* m_hp_slider;//人物血条
	ui::Slider* m_mp_slider;//人物魔法值条

};
