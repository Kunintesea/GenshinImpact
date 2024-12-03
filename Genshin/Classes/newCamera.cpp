#include "newCamera.h"

// Scene������� newCamera ʱ����Ҫ��������� 
// newCamera->bindPlayer(��ʼ��ɫ)
// this->addChild(newCamera->getCamera)

// �л���ɫʱ
// newCamera->bindPlayer(�½�ɫ)

bool newCamera::init()
{
	if (!Node::init()) { return false; }

	//���������
	this->scheduleUpdate();
	
	// ��ȡ��Ļ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// ����һ�����
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
	//ʵ�ְ������ƾ����ƶ�
	auto left = EventKeyboard::KeyCode::KEY_LEFT_ARROW;//���
	auto right = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;//�Ҽ�
	auto up = EventKeyboard::KeyCode::KEY_UP_ARROW;//�ϼ�
	auto down = EventKeyboard::KeyCode::KEY_DOWN_ARROW;//�¼�

	if (player->getKeyBoardState(left) && player->getKeyBoardState(up)) // ����
	      moveSet(-1, 1, dt);
	else if (player->getKeyBoardState(left) && player->getKeyBoardState(down)) // ����
	      moveSet(-1, -1, dt);
	else if (player->getKeyBoardState(right) && player->getKeyBoardState(up)) // ����
	      moveSet(1, 1, dt);
	else if (player->getKeyBoardState(right) && player->getKeyBoardState(down)) // ����
	      moveSet(1, -1, dt);
	else if (player->getKeyBoardState(left)) // ����������
	      moveSet(-1, 0, dt);
	else if (player->getKeyBoardState(right)) // ����Ҽ�����
	      moveSet(1, 0, dt);
	else if (player->getKeyBoardState(up)) // ����ϼ�����
	      moveSet(0, 1, dt);
	else if (player->getKeyBoardState(down)) // ����¼�����
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
// ���ø�������ƶ�
void newCamera::moveSet(int x, int y, float delta) {
      float speed = player->getSpeed();
      auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
      camera->setPosition(camera->getPosition() + Vec2(x, y) * speed);

      if (abs(cameraMove.x) <= float(maxOffSet))
      {
	    // ���ƫ��
	    camera->setPosition(camera->getPosition() - Vec2(x * speed, 0));
	    cameraMove.x += x * speed;
      }
      if (abs(cameraMove.y) <= float(maxOffSet) / 2)
      {
	    // ���ƫ��
	    camera->setPosition(camera->getPosition() - Vec2(0, y * speed));
	    cameraMove.y += y * speed;
      }
}