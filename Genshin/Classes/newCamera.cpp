#include "newCamera.h"

// Scene������� newCamera ʱ����Ҫ��������� 
// newCamera->bindPlayer(��ʼ��ɫ)
// this->addChild(newCamera->getCamera)

// �л���ɫʱ
// newCamera->bindPlayer(�½�ɫ)

bool newCamera::init()
{
	//��playerUI��������ƶ�
	PlayerStatusUI* playerUI = PlayerStatusUI::create();
	//��һ��nametagΪplayerUI
	playerUI->setName("playerUI");
	//��playerUI��ӵ�����ڵ�
	this->addChild(playerUI);


	if (!Node::init()) { return false; }

	//���������
	this->scheduleUpdate();

	// ��ȡ��Ļ��С
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	// ����һ���������
	cameraSprite = Sprite::create("HelloWorld.png");
	cameraSprite->setOpacity(0);
	this->addChild(cameraSprite);
	// ����һ�����
	camera = Camera::createPerspective(60, visibleSize.width / visibleSize.height, 1, 1000);
	camera->setCameraFlag(CameraFlag::USER1);
	// ��ʼ������ƶ�����
	cameraMove = Vec2::ZERO;
	cameraBackMove = Vec2::ZERO;



	//�Ի����ʼ��
	dialogmenu = Sprite::create("UI/dialog.png");
	//λ�÷�����Ļ�·��м�
	dialogmenu->setPosition(Vec2(visibleSize.width / 3 + origin.x, 100));
	//�󶨵�����
	this->addChild(dialogmenu, 55);
	//Ĭ�ϲ��ɼ�
	dialogmenu->setVisible(false);

	//��ȡ�Ի����С
	//��
	float dialogwidth = dialogmenu->getContentSize().width;
	//��
	float dialogheight = dialogmenu->getContentSize().height;


	//�Ի��ߵ����֣���ʾ�ڶԻ������Ͻ�
	dialoger = Label::createWithTTF("npc1asdsad", "fonts/Marker Felt.ttf", 24);
	//�󶨵��Ի���
	dialoger->setPosition(Vec2(120, dialogheight * 0.8));
	//���뵽�Ի���
	dialogmenu->addChild(dialoger);
	//���
	dialoger->enableOutline(Color4B::BLACK, 2);

	//�Ի����ݣ���ʾ�ڶԻ����м�
	dialogcontent = Label::createWithTTF("you,get money to me!!!!!!", "fonts/Marker Felt.ttf", 24);
	//�󶨵��Ի���
	dialogcontent->setPosition(Vec2(dialogwidth / 2, dialogheight / 2));
	//���뵽�Ի���
	dialogmenu->addChild(dialogcontent);
	//���
	dialogcontent->enableOutline(Color4B::BLACK, 2);



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
playerUI->setPosition(cameraSprite->getPosition() - visibleSize * 0.5);

//���¶Ի���λ��
//dialogmenu->setPosition(cameraSprite->getPosition() - visibleSize * 0.5 + Vec2(visibleSize.width / 3, 100));

}



void newCamera::update(float dt)
{
      //�����UI���и���
      PlayerStatusUI* playerUI = (PlayerStatusUI*)this->getChildByName("playerUI");
      //����player�࣬���������ݸ���UI
      playerUI->updateUI(*player);
      playerUI->updateInteractUI(*player);

      //���¶Ի���λ��
      //dialogmenu->setPosition(cameraSprite->getPosition() - visibleSize * 0.5 + Vec2(visibleSize.width / 3, 100));


	//ʵ�ְ������ƾ����ƶ�
	auto left = EventKeyboard::KeyCode::KEY_LEFT_ARROW;//���
	auto right = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;//�Ҽ�
	auto up = EventKeyboard::KeyCode::KEY_UP_ARROW;//�ϼ�
	auto down = EventKeyboard::KeyCode::KEY_DOWN_ARROW;//�¼�

	// ���ȱ�֤�������
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
		// ������Ұ���ͬʱ���£�����
		//if (player->getKeyBoardState(left) && player->getKeyBoardState(right) // ����
		//	|| player->getKeyBoardState(down) && pladyer->getKeyBoardState(up)) // ����
		//	return;
		//else 
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
	//z�ᵥ����ƣ��������
	playerUI->setLocalZOrder(-1);
	//���¶Ի���λ��
	dialogmenu->setPosition(cameraSprite->getPosition() - visibleSize * 0.5 + Vec2(visibleSize.width /2, 240));
	//z�ᵥ����ƣ��������
	//dialogmenu->setLocalZOrder(-1);
}
// ���ø�������ƶ�
void newCamera::moveSet(int x, int y, float delta) {
	//float deltaMove;
	//if (x == 0 || y == 0) deltaMove = 1;
	//else deltaMove = 0.707;
      float speed = player->getSpeed();

	if (!isFollowedDynamicly)
		return;

	//camera->setPosition(camera->getPosition() + Vec2(x * deltaMove, y * deltaMove) * speed);

	if (abs(cameraMove.x) <= float(maxOffSet))
	{
		// ���ƫ��
		// camera->setPosition(camera->getPosition() - Vec2(x * deltaMove * speed, 0));
		// cameraMove.x += x * deltaMove * speed;

		//cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(x * speed, 0));
		cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(player->getPosition().x - lastPosition.x, 0));
	      
		cameraMove.x += player->getPosition().x - lastPosition.x;
	}
	if (abs(cameraMove.y) <= float(maxOffSet) / 2)
	{
		// ���ƫ��
		// camera->setPosition(camera->getPosition() - Vec2(0, y * deltaMove * speed));
		
		//cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(0, y * speed));
	      cameraSprite->setPosition(cameraSprite->getPosition() - Vec2(0, player->getPosition().y - lastPosition.y));

		// cameraMove.y += y * deltaMove * speed;
		cameraMove.y += player->getPosition().y - lastPosition.y;
	}
}

void newCamera::setDialog(std::string dialog, std::string dialogername)
{
      dialogcontent->setString(dialog);
      dialoger->setString(dialogername);
}