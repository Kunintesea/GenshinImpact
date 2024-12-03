#include "newCamera.h"

// Scene创建相机 newCamera 时，需要创建相机再 
// newCamera->bindPlayer(初始角色)
// this->addChild(newCamera->getCamera)

// 切换角色时
// newCamera->bindPlayer(新角色)

bool newCamera::init()
{
	if (!Node::init()) { return false; }

	//加入调度器
	this->scheduleUpdate();
	
	// 获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// 创建一个相机
	camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	cameraMove = Vec2::ZERO;
	return true;
}

void newCamera::bindPlayer(Player* player)
{
	this->player = player;
	camera->setPosition(player->getBody()->getPosition());
	maxOffSet = 0.1 * 60 * player->getSpeed();
}

void newCamera::update(float dt)
{
	//实现按键控制精灵移动
	auto left = EventKeyboard::KeyCode::KEY_LEFT_ARROW;//左键
	auto right = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;//右键
	auto up = EventKeyboard::KeyCode::KEY_UP_ARROW;//上键
	auto down = EventKeyboard::KeyCode::KEY_DOWN_ARROW;//下键

	if (player->getKeyBoardState(left) && player->getKeyBoardState(up)) // 左上
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
	else 
	      if (cameraMove != Vec2::ZERO &&
		    (abs(cameraMove.x) > float(maxOffSet) || abs(cameraMove.y) > float(maxOffSet / 2)))
	      {
		    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
		    MoveBy* move = MoveBy::create(0.1, cameraMove);
		    camera->runAction(move);
		    cameraMove = Vec2::ZERO;
	      }
}
// 设置个方向的移动
void newCamera::moveSet(int x, int y, float delta) {
      float speed = player->getSpeed();
      auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
      camera->setPosition(camera->getPosition() + Vec2(x, y) * speed);

      if (abs(cameraMove.x) <= float(maxOffSet))
      {
	    // 相机偏移
	    camera->setPosition(camera->getPosition() - Vec2(x * speed, 0));
	    cameraMove.x += x * speed;
      }
      if (abs(cameraMove.y) <= float(maxOffSet) / 2)
      {
	    // 相机偏移
	    camera->setPosition(camera->getPosition() - Vec2(0, y * speed));
	    cameraMove.y += y * speed;
      }
}