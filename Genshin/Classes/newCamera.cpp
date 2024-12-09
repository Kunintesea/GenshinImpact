#include "newCamera.h"

// Scene创建相机 newCamera 时，需要创建相机再 
// newCamera->bindPlayer(初始角色)
// this->addChild(newCamera->getCamera)

// 切换角色时
// newCamera->bindPlayer(新角色)

bool newCamera::init()
{
	//让playerUI跟着相机移动
	PlayerStatusUI* playerUI = PlayerStatusUI::create();
	//设一个nametag为playerUI
	playerUI->setName("playerUI");
	//将playerUI添加到相机节点
	this->addChild(playerUI);


	if (!Node::init()) { return false; }

	//加入调度器
	this->scheduleUpdate();

	// 获取屏幕大小
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	// 创建一个相机精灵
	cameraSprite = Sprite::create("HelloWorld.png");
	cameraSprite->setOpacity(0);
	this->addChild(cameraSprite);
	// 创建一个相机
	camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	// 初始化相机移动参数
	cameraMove = Vec2::ZERO;
	cameraBackMove = Vec2::ZERO;
	return true;
}

void newCamera::bindPlayer(Player* player)
{
	this->player = player;
	initialOffset = player->getPosition();
	this->setPosition(initialOffset);

	lastPosition = player->getPosition();
	cameraSprite->setPosition(Vec2::ZERO);
	camera->setPosition(Vec2::ZERO);
	cameraMove = Vec2::ZERO;
	cameraBackMove = Vec2::ZERO;

	maxOffSet = 0.2 * 60 * player->getSpeed();

	PlayerStatusUI* playerUI = (PlayerStatusUI*)this->getChildByName("playerUI");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	;	playerUI->setPosition(cameraSprite->getPosition() - visibleSize * 0.5);
}



void newCamera::update(float dt)
{
	//对玩家UI进行更新
	PlayerStatusUI* playerUI = (PlayerStatusUI*)this->getChildByName("playerUI");
	//传入player类，根据其数据更新UI
	playerUI->updateUI(*player);

	//实现按键控制精灵移动
	auto left = EventKeyboard::KeyCode::KEY_LEFT_ARROW;//左键
	auto right = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;//右键
	auto up = EventKeyboard::KeyCode::KEY_UP_ARROW;//上键
	auto down = EventKeyboard::KeyCode::KEY_DOWN_ARROW;//下键

	// 优先保证相机跟随
	cameraSprite->setPosition(cameraSprite->getPosition() + player->getPosition() - lastPosition);

	if (player->getKeyBoardState(left) && player->getKeyBoardState(up) && player->getKeyBoardState(down))
		moveSet(-1, 0, dt);
	else if (player->getKeyBoardState(right) && player->getKeyBoardState(up) && player->getKeyBoardState(down))
		moveSet(1, 0, dt);
	else if (player->getKeyBoardState(left) && player->getKeyBoardState(right) && player->getKeyBoardState(up))
		moveSet(0, 1, dt);
	else if (player->getKeyBoardState(left) && player->getKeyBoardState(right) && player->getKeyBoardState(down))
		moveSet(0, -1, dt);
	else
		// 如果左右按键同时按下，返回
		if (player->getKeyBoardState(left) && player->getKeyBoardState(right) // 左右
			|| player->getKeyBoardState(down) && player->getKeyBoardState(up)) // 上下
			return;
		else if (player->getKeyBoardState(left) && player->getKeyBoardState(up)) // 左上
			moveSet(-1, 1, dt);
		else if (player->getKeyBoardState(left) && player->getKeyBoardState(down)) // 左下
			moveSet(-1, -1, dt);
		else if (player->getKeyBoardState(right) && player->getKeyBoardState(up)) // 右上
			moveSet(1, 1, dt);
		else if (player->getKeyBoardState(right) && player->getKeyBoardState(down)) // 右下
			moveSet(1, -1, dt);
		else if (player->getKeyBoardState(left)) // 如果左键按下
			moveSet(-1, 0, dt);
		else if (player->getKeyBoardState(right)) // 如果右键按下
			moveSet(1, 0, dt);
		else if (player->getKeyBoardState(up)) // 如果上键按下
			moveSet(0, 1, dt);
		else if (player->getKeyBoardState(down)) // 如果下键按下
			moveSet(0, -1, dt);
		else if (!isFollowedDynamicly)
			return;
		else if (cameraMove != Vec2::ZERO &&
			(abs(cameraMove.x) > float(maxOffSet) || abs(cameraMove.y) > float(maxOffSet / 2)))
		{
			cameraBackMove += cameraMove;
			cameraMove = Vec2::ZERO;
		}

	if (cameraBackMove != Vec2::ZERO) {
		//auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
		//float speed = player->getSpeed();

		if (cameraBackMove.x == 0 || cameraBackMove.y == 0)
		{
			Vec2 temp = cameraBackMove * cameraOffsetTime * 0.25f;
			cameraSprite->setPosition(cameraSprite->getPosition() + temp);
			cameraBackMove -= temp;
		}
		else {
			Vec2 temp = cameraBackMove * cameraOffsetTime * 0.25f * 0.707f;
			cameraSprite->setPosition(cameraSprite->getPosition() + temp);
			cameraBackMove -= temp;
		}
	}

	auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
	camera->setPosition(cameraSprite->getPosition() + initialOffset);

	lastPosition = player->getPosition();

	playerUI->setPosition(cameraSprite->getPosition() - visibleSize * 0.5);
	//z轴单独设计，在相机下
	playerUI->setLocalZOrder(-1);
}
// 设置个方向的移动
void newCamera::moveSet(int x, int y, float delta) {
	//float deltaMove;
	//if (x == 0 || y == 0) deltaMove = 1;
	//else deltaMove = 0.707;

	float speed = player->getSpeed();
	//cameraSprite->setPosition(cameraSprite->getPosition() + Vec2(x, y) * speed);

	if (!isFollowedDynamicly)
		return;

	//camera->setPosition(camera->getPosition() + Vec2(x * deltaMove, y * deltaMove) * speed);

	if (abs(cameraMove.x) <= float(maxOffSet))
	{
		// 相机偏移
		// camera->setPosition(camera->getPosition() - Vec2(x * deltaMove * speed, 0));
		// cameraMove.x += x * deltaMove * speed;

		//cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(x * speed, 0));
		cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(player->getPosition().x - lastPosition.x, 0));

		cameraMove.x += player->getPosition().x - lastPosition.x;
	}
	if (abs(cameraMove.y) <= float(maxOffSet) / 2)
	{
		// 相机偏移
		// camera->setPosition(camera->getPosition() - Vec2(0, y * deltaMove * speed));

		//cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(0, y * speed));
		cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(0, player->getPosition().y - lastPosition.y));

		// cameraMove.y += y * deltaMove * speed;
		cameraMove.y += player->getPosition().y - lastPosition.y;
	}
}