#include "mapManager.h"

bool mapManager::init()
{
        // ��ʼ��
	if (!Node::init()) { return false; }
	visibleSize = Director::getInstance()->getVisibleSize();

	// ���������
	this->scheduleUpdate();

	// ����������������������������������������������������������
	// ��ʼ����ͼ��������Ը����ֵĵ�ͼ������½��ǵ�ͼ����ϵ��ԭ�㣩
	// ����������������������������������������������������������
	initialMapMiddleX = 2;
	initialMapMiddleY = 2;
	
	// ��ʾ��ͼ������Ӧ�����������ڴ���ӵ�����
	map = TMXTiledMap::create("map//map-2-2.tmx");
	map->setAnchorPoint(Vec2(0.5f, 0.5f));

	// ��ʼ����ͼ����
	mapSize = map->getContentSize() / 3; // ��ȡ��ͼ��С
	tileSize = mapSize / 40; // ��ȡ��ͼ���С
	
	// ����������������������������������������������������������
	// �����Ѿ��õ��˾���ľ�������
	// һ���޸��˾���ľ������꣬Ҳ��Ҫ��������Ĳ�����
	// ����������������������������������������������������������
	spritePos = Vec2(0,0);
	mapMiddleX = (int)std::floor(spritePos.x / mapSize.width);
	mapMiddleY = -(int)std::floor(spritePos.y / mapSize.height);
	spritePosChange = Vec2(std::fmod(spritePos.x, mapSize.width), std::fmod(spritePos.y, mapSize.height));

	// �������Ŀ�ĵ�ͼ
	Vec2 middlePos = Vec2((mapMiddleX + 0.5f) * mapSize.width, (-mapMiddleY + 0.5f) * mapSize.height);
	map->setPosition(middlePos);
	this->addChild(map, 0);

	return true;
}

void mapManager::update(float dt)
{
      Vec2 spritePosition = this->getParent()->getChildByName("Me")->getPosition();
      spritePosChange = spritePosChange + spritePosition - spritePos;
      spritePos = spritePosition;
      // �����������
      mapMiddleX = (int)std::floor(spritePos.x / mapSize.width);
      // ��ͼ����ϵ�;�������ϵ���෴��
      mapMiddleY = -(int)std::floor(spritePos.y / mapSize.height);
      // ���ǵ�ͼ����ϵ�;�������ϵ����ʹ��ͬһ�׾�������ϵ��ʹ���ٴ�ȡ��
      Vec2 middlePos = Vec2((mapMiddleX + 0.5f) * mapSize.width, (-mapMiddleY + 0.5f) * mapSize.height);

      // �ж��Ƿ���Ҫ�л���ͼ
      // ��
      if (spritePosChange.x < 0 )
      {
	    // ѡ��ֱ�����õ�ͼ
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange + Vec2(mapSize.width, 0);
	    currentTransparentTiles.clear();
      }
      // ��
      if (spritePosChange.x > mapSize.width)
      {
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange - Vec2(mapSize.width, 0);
	    currentTransparentTiles.clear();
      }
      // ��
      if (spritePosChange.y > mapSize.height)
      {
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange - Vec2(0, mapSize.height);
	    currentTransparentTiles.clear();
      }
      // ��
      if (spritePosChange.y < 0)
      {
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange + Vec2(0, mapSize.height);
	    currentTransparentTiles.clear();
      }

      //  �ж��Ƿ���Ҫ�ڵ�
      // ��ȡ��ͼ���ڴ������������½ǵĵ�ͼ����
      int tiledPositionX = -(mapMiddleX/* - tiledMiddleX*/) * 40 + (int)std::floor(spritePosition.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(spritePosition.y == 0 ? 0.1 : spritePosition.y / tileSize.height);
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr)
	    log("map is null");
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ�����ײ��
      toFadeLayer = map->getLayer("toFade");
      // ��ȡ���ص���ײ��Ϣ
      if (toFadeLayer) {
	    uint32_t gid = toFadeLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
	    // �ж���ײ��Ϣ��ֻҪ���ǿյľ�����ײ
	    TilePos newPos(tiledPositionX, tiledPositionY);
	    if (gid)
	    {
		  if (currentTransparentTiles.empty()) {
			currentTransparentTiles = findConnectedTiles(tiledPositionX, tiledPositionY);
			setTilesOpacity(currentTransparentTiles, 100);
		  }
	    }
	    else if (!currentTransparentTiles.empty()) {
		  setTilesOpacity(currentTransparentTiles, 255);
		  currentTransparentTiles.clear();
	    }
      }
      // �Գ�ǽ�����ص�������
      TMXLayer* WallLayer = map->getLayer("wall");
      if (WallLayer) {
	    uint32_t wallGid = WallLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
	    // ��⵽��ǽ
	    if (wallGid) 
		  // ֱ���ó�ǽ��ͼ���½�
		  WallLayer->setLocalZOrder(-5);
	    else
		  WallLayer->setLocalZOrder(2);
      }
}

std::set<TilePos> mapManager::findConnectedTiles(int startX, int startY) {
      std::set<TilePos> connectedTiles;
      std::queue<TilePos> q;

      // ��ȡ��ʼλ�õ� gid�����Ϊ 0 ��ֱ�ӷ��ؿռ���
      uint32_t startGid = toFadeLayer->getTileGIDAt(Vec2(startX, startY));
      if (startGid == 0) return connectedTiles;

      TilePos start(startX, startY);
      q.push(start);
      connectedTiles.insert(start);

      while (!q.empty()) {
	    TilePos current = q.front();
	    q.pop();

	    for (int i = 0; i < 4; i++) {
		  int newX = current.x + dx[i];
		  int newY = current.y + dy[i];

		  if (!isValidPosition(newX, newY)) continue;

		  TilePos next(newX, newY);
		  if (connectedTiles.find(next) != connectedTiles.end())
			continue;

		  // �����λ�õ� gid
		  uint32_t nextGid = toFadeLayer->getTileGIDAt(Vec2(newX, newY));
		  // ֻҪ gid ��Ϊ 0������Ϊ����ͨ��
		  if (nextGid != 0) {
			q.push(next);
			connectedTiles.insert(next);
		  }
		  // ��� gid Ϊ 0���Ͳ��Ὣ���λ�ü�����У���ȻҲ����̽�������ھ�
	    }
      }

      return connectedTiles;
}

void mapManager::setTilesOpacity(const std::set<TilePos>& tiles, GLubyte opacity) {
      for (const auto& pos : tiles) {
	    Sprite* tile = toFadeLayer->getTileAt(Vec2(pos.x, pos.y));
	    if (tile) {
		  tile->setOpacity(opacity);
	    }
      }
}

void mapManager::MapCreate(TMXTiledMap*& map, Vec2 middlePos) {
      // �����ӵ�ͼ
      char* mapName = new char[40];
      // ��ͼ������ʼ��ͼ���� + ���ھ��������ƫ���� + ��������ƫ����
      // ���� -j ����Ϊ��ͼ����ϵ�;�������ϵ���෴��
      sprintf(mapName, "map//map-%d-%d.tmx", initialMapMiddleY + mapMiddleY, initialMapMiddleX + mapMiddleX);
      log("mapName: %s", mapName);
      map = TMXTiledMap::create(mapName);
      // �����ӵ�ͼ����
      map->setAnchorPoint(Vec2(0.5f, 0.5f));
      map->setPosition(middlePos);
      this->addChild(map, 0);
}

bool mapManager::isCollision(Vec2 position) {
      // ��ȡ�������ڴ����
      //int tiledMiddleX = (int)std::floor(position.x / mapSize.width);
      //int tiledMiddleY = (int)std::floor(position.y == 0 ? 0.1 : position.y / mapSize.height);
      // ��ȡ��ͼ���ڴ������������½ǵĵ�ͼ����
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY ) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr )
	    log("map is null");
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ�����ײ��
      TMXLayer* collisionLayer = map->getLayer("colide");
      if (!collisionLayer)
      {
	    log("collisionLayer is null");
	    return false;
      }
      // ��ȡ��ײ�����ײ��Ϣ
      uint32_t gid = collisionLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
      // �ж���ײ��Ϣ��ֻҪ���ǿյľ�����ײ
      if (gid) 
      {
	    log("Collision!");
	    return true;
      }
      // ����˵��û����ײ
      return false;
}

set<int> mapManager::isInteraction(Vec2 position) {
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      set<int> interaction;

      // ���α�����Χ�ĸ���
      isInteract(tiledPositionX, tiledPositionY, interaction);

      isInteract(tiledPositionX - 1, tiledPositionY, interaction);
      isInteract(tiledPositionX, tiledPositionY - 1, interaction);
      isInteract(tiledPositionX + 1, tiledPositionY, interaction);
      isInteract(tiledPositionX, tiledPositionY + 1, interaction);

      isInteract(tiledPositionX - 1, tiledPositionY - 1, interaction);
      isInteract(tiledPositionX + 1, tiledPositionY - 1, interaction);
      isInteract(tiledPositionX - 1, tiledPositionY + 1, interaction);
      isInteract(tiledPositionX + 1, tiledPositionY + 1, interaction);

      isInteract(tiledPositionX - 2, tiledPositionY, interaction);
      isInteract(tiledPositionX, tiledPositionY - 2, interaction);
      isInteract(tiledPositionX + 2, tiledPositionY, interaction);
      isInteract(tiledPositionX, tiledPositionY + 2, interaction);

      isInteract(tiledPositionX - 2, tiledPositionY - 1, interaction);
      isInteract(tiledPositionX - 2, tiledPositionY + 1, interaction);
      isInteract(tiledPositionX + 2, tiledPositionY - 1, interaction);
      isInteract(tiledPositionX + 2, tiledPositionY + 1, interaction);
      isInteract(tiledPositionX - 1, tiledPositionY - 2, interaction);
      isInteract(tiledPositionX - 1, tiledPositionY + 2, interaction);
      isInteract(tiledPositionX + 1, tiledPositionY - 2, interaction);
      isInteract(tiledPositionX + 1, tiledPositionY + 2, interaction);

      return interaction;
}

int mapManager::getBackgroundTag(Vec2 position) {
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr)
	    log("map is null");
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��Ľ�����
      TMXLayer* interactLayer = map->getLayer("bg");

      if (tiledPositionX < 0 || tiledPositionX >= 120 || tiledPositionY < 0 || tiledPositionY >= 120)
	    return 0;

      // ��ȡ���������ײ��Ϣ
      uint32_t gid = interactLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));

      if (gid == 26 || gid == 28)
	    return 1;
      else if (gid == 25 || gid == 27)
	    return 2;
      return 0;
}

// �� set ���뽻����Ϣ���Դ���
void mapManager::isInteract(int tiledPositionX, int tiledPositionY, set<int>& interaction) {
      if (map == nullptr)
	    log("map is null");
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��Ľ�����
      TMXLayer* interactLayer = map->getLayer("interact");

      if (tiledPositionX < 0 || tiledPositionX >= 120 || tiledPositionY < 0 || tiledPositionY >= 120)
	    return;

      // ��ȡ���������ײ��Ϣ
      uint32_t gid = interactLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
      // �ж���ײ��Ϣ��ֻҪ���ǿյľ�����ײ
      if (!gid) // 
      {
	    log("NO INTERACT!");
	    return;
      }

      // ֻҪ����ֵ��Ϊ 0����˵���н���
      // ͬʱ��֤���ظ����
      if (gid == 4825 || gid == 4849)
	    // ��������11 :  ��ɪ�� - kaiselin
	    if (interaction.find(11) == interaction.end())
	    {
		  interaction.insert(11);
	    }
      if (gid == 4827 || gid == 4851)
	    // ��������12 :  �� - qin
	    if (interaction.find(12) == interaction.end())
	    {
		  interaction.insert(12);
	    }
      if (gid == 4829 || gid == 4853)
	    // ��������13 :  ice-man
	    if (interaction.find(13) == interaction.end())
	    {
		  interaction.insert(13);
	    }
      if (gid == 4831 || gid == 4855)
	    // ��������9 :  ����ê�� - Teleport Waypoint
	    if (interaction.find(9) == interaction.end())
	    {
		  interaction.insert(9);
	    }
      if (gid == 3419)
	    // ��������8 :  �������ڵ�ͼ
	    if (interaction.find(8) == interaction.end())
	    {
		  interaction.insert(8);
	    }
      if (gid == 1187)
	    // ��������8 :  �������ڵ�ͼ
	    if (interaction.find(8) == interaction.end())
	    {
		  interaction.insert(7);
	    }
      return;
}
bool mapManager::isRefreshMonster(Vec2 position) {
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr)
	    log("map is null");
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��Ľ�����
      TMXLayer* interactLayer = map->getLayer("interact");

      if (tiledPositionX < 0 || tiledPositionX >= 120 || tiledPositionY < 0 || tiledPositionY >= 120)
	    return false;

      // ��ȡ���������ײ��Ϣ
      uint32_t gid = interactLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
      if (gid == 3339)
	    return true;

      // ֻҪ����ֵ��Ϊ 0����˵���н���
      return false;
}