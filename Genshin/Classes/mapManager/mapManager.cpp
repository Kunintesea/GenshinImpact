#include "mapManager.h"

bool mapManager::init()
{
        // 初始化
	if (!Node::init()) { return false; }
	visibleSize = Director::getInstance()->getVisibleSize();

	// 加入调度器
	this->scheduleUpdate();

	// ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	// 初始化地图块参数（以该名字的地图块的左下角是地图坐标系的原点）
	// ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	initialMapMiddleX = 2;
	initialMapMiddleY = 2;
	
	// 显示地图的中心应该是人物所在大格子的中心
	map = TMXTiledMap::create("map//map-2-2.tmx");
	map->setAnchorPoint(Vec2(0.5f, 0.5f));

	// 初始化地图参数
	mapSize = map->getContentSize() / 3; // 获取地图大小
	tileSize = mapSize / 40; // 获取地图块大小
	
	// ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	// 假设已经得到了精灵的绝对坐标
	// 一旦修改了精灵的绝对坐标，也需要更改这里的参数！
	// ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	spritePos = Vec2(0,0);
	mapMiddleX = (int)std::floor(spritePos.x / mapSize.width);
	mapMiddleY = -(int)std::floor(spritePos.y / mapSize.height);
	spritePosChange = Vec2(std::fmod(spritePos.x, mapSize.width), std::fmod(spritePos.y, mapSize.height));

	// 建立中心块的地图
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
      // 计算格子坐标
      mapMiddleX = (int)std::floor(spritePos.x / mapSize.width);
      // 地图坐标系和精灵坐标系是相反的
      mapMiddleY = -(int)std::floor(spritePos.y / mapSize.height);
      // 但是地图坐标系和精灵坐标系都在使用同一套绝对坐标系，使用再次取反
      Vec2 middlePos = Vec2((mapMiddleX + 0.5f) * mapSize.width, (-mapMiddleY + 0.5f) * mapSize.height);

      // 判断是否需要切换地图
      // 左
      if (spritePosChange.x < 0 )
      {
	    // 选择直接重置地图
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange + Vec2(mapSize.width, 0);
	    currentTransparentTiles.clear();
      }
      // 右
      if (spritePosChange.x > mapSize.width)
      {
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange - Vec2(mapSize.width, 0);
	    currentTransparentTiles.clear();
      }
      // 上
      if (spritePosChange.y > mapSize.height)
      {
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange - Vec2(0, mapSize.height);
	    currentTransparentTiles.clear();
      }
      // 下
      if (spritePosChange.y < 0)
      {
	    map->removeFromParentAndCleanup(true);
	    MapCreate(map, middlePos);
	    spritePosChange = spritePosChange + Vec2(0, mapSize.height);
	    currentTransparentTiles.clear();
      }

      //  判断是否需要遮挡
      // 获取地图块在大格子里面的左下角的地图坐标
      int tiledPositionX = -(mapMiddleX/* - tiledMiddleX*/) * 40 + (int)std::floor(spritePosition.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(spritePosition.y == 0 ? 0.1 : spritePosition.y / tileSize.height);
      // 获取地图块所在大格子的地图块
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr)
	    log("map is null");
      // 获取地图块所在大格子的地图块的碰撞层
      toFadeLayer = map->getLayer("toFade");
      // 获取隐藏的碰撞信息
      if (toFadeLayer) {
	    uint32_t gid = toFadeLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
	    // 判断碰撞信息，只要不是空的就是碰撞
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
      // 对城墙的隐藏单独处理
      TMXLayer* WallLayer = map->getLayer("wall");
      if (WallLayer) {
	    uint32_t wallGid = WallLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
	    // 检测到城墙
	    if (wallGid) 
		  // 直接让城墙的图层下降
		  WallLayer->setLocalZOrder(-5);
	    else
		  WallLayer->setLocalZOrder(2);
      }
}

std::set<TilePos> mapManager::findConnectedTiles(int startX, int startY) {
      std::set<TilePos> connectedTiles;
      std::queue<TilePos> q;

      // 获取起始位置的 gid，如果为 0 则直接返回空集合
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

		  // 检查新位置的 gid
		  uint32_t nextGid = toFadeLayer->getTileGIDAt(Vec2(newX, newY));
		  // 只要 gid 不为 0，就认为是连通的
		  if (nextGid != 0) {
			q.push(next);
			connectedTiles.insert(next);
		  }
		  // 如果 gid 为 0，就不会将这个位置加入队列，自然也不会探索它的邻居
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
      // 创建子地图
      char* mapName = new char[40];
      // 地图名：初始地图块名 + 基于精灵坐标的偏移量 + 上下左右偏移量
      // 这里 -j 是因为地图坐标系和精灵坐标系是相反的
      sprintf(mapName, "map//map-%d-%d.tmx", initialMapMiddleY + mapMiddleY, initialMapMiddleX + mapMiddleX);
      log("mapName: %s", mapName);
      map = TMXTiledMap::create(mapName);
      // 设置子地图属性
      map->setAnchorPoint(Vec2(0.5f, 0.5f));
      map->setPosition(middlePos);
      this->addChild(map, 0);
}

bool mapManager::isCollision(Vec2 position) {
      // 获取人物所在大格子
      //int tiledMiddleX = (int)std::floor(position.x / mapSize.width);
      //int tiledMiddleY = (int)std::floor(position.y == 0 ? 0.1 : position.y / mapSize.height);
      // 获取地图块在大格子里面的左下角的地图坐标
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY ) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // 获取地图块所在大格子的地图块
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr )
	    log("map is null");
      // 获取地图块所在大格子的地图块的碰撞层
      TMXLayer* collisionLayer = map->getLayer("colide");
      if (!collisionLayer)
      {
	    log("collisionLayer is null");
	    return false;
      }
      // 获取碰撞层的碰撞信息
      uint32_t gid = collisionLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
      // 判断碰撞信息，只要不是空的就是碰撞
      if (gid) 
      {
	    log("Collision!");
	    return true;
      }
      // 否则说明没有碰撞
      return false;
}

set<int> mapManager::isInteraction(Vec2 position) {
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // 获取地图块所在大格子的地图块
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      set<int> interaction;

      // 依次遍历周围的格子
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
      // 获取地图块所在大格子的地图块
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr)
	    log("map is null");

      if (tiledPositionX < 0 || tiledPositionX >= 120 || tiledPositionY < 0 || tiledPositionY >= 120)
	    return 0;

      // 获取地图块所在大格子的地图块的bg层
      TMXLayer* bg = map->getLayer("bg");
      if (bg == NULL) return 0;
      uint32_t gid = bg->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));

      // 获取地图块所在大格子的地图块的object层
      TMXLayer* object = map->getLayer("object");
      if (object == NULL) return 0;
      uint32_t objectGid = object->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));

      if (objectGid == 3890 || objectGid == 3889)
	    return 0;

      if (gid == 26 || gid == 28)
	    return 1;
      else if (gid == 25 || gid == 27)
	    return 2;
      return 0;
}

// 向 set 加入交互信息属性代号
void mapManager::isInteract(int tiledPositionX, int tiledPositionY, set<int>& interaction) {
      if (map == nullptr)
	    log("map is null");
      // 获取地图块所在大格子的地图块的交互层
      TMXLayer* interactLayer = map->getLayer("interact");
      if (interactLayer == NULL) return;

      if (tiledPositionX < 0 || tiledPositionX >= 120 || tiledPositionY < 0 || tiledPositionY >= 120)
	    return;

      // 获取交互层的碰撞信息
      uint32_t gid = interactLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
      // 判断碰撞信息，只要不是空的就是碰撞
      if (!gid) // 
      {
	    log("NO INTERACT!");
	    return;
      }

      // 只要返回值不为 0，就说明有交互
      // 同时保证不重复添加
      if (gid == 4825 || gid == 4849)
	    // 交互属性11 :  凯瑟琳 - Kaiselin
	    if (interaction.find(11) == interaction.end())
	    {
		  interaction.insert(11);
	    }
      if (gid == 4827 || gid == 4851)
	    // 交互属性12 :  琴 - qin
	    if (interaction.find(12) == interaction.end())
	    {
		  interaction.insert(12);
	    }
      if (gid == 4829 || gid == 4853)
	    // 交互属性13 :  ice-man
	    if (interaction.find(13) == interaction.end())
	    {
		  interaction.insert(13);
	    }
    //  if (gid == 4845 || gid == 4869)
	   // // 交互属性14 :  Varka
	   // if (interaction.find(14) == interaction.end())
	   // {
		  //interaction.insert(14);
	   // }
      if (gid == 4838 || gid == 4862)
	    // 交互属性15 :  fisherman
	    if (interaction.find(15) == interaction.end())
	    {
		  interaction.insert(15);
	    }
    //  if (gid == 4840 || gid == 4864 || gid == 4841 || gid == 4865)
	   // // 交互属性16 :  butcher
	   // if (interaction.find(16) == interaction.end())
	   // {
		  //interaction.insert(16);
	   // }
    //  if (gid == 4785 || gid == 4786 || gid == 4809 || gid == 4833)
	   // // 交互属性17 :  DragonGirl
	   // if (interaction.find(17) == interaction.end())
	   // {
		  //interaction.insert(17);
	   // }
    //  if (gid == 4843 || gid == 4867)
	   // // 交互属性18 :  Wagner
	   // if (interaction.find(18) == interaction.end())
	   // {
		  //interaction.insert(18);
	   // }

      if (gid == 4682 || gid == 4683 || gid == 4706 || gid == 4707
	    || gid == 4154 || gid == 4178 || gid == 4155 || gid == 4179 || gid == 4156 || gid == 4180)
	    // 交互属性25 :  tree
	    if (interaction.find(25) == interaction.end())
	    {
		  interaction.insert(25);
	    }

      if (gid == 26)
	    // 交互属性26 :  fish
	    if (interaction.find(26) == interaction.end())
	    {
		  interaction.insert(26);
	    }


      if (gid == 4831 || gid == 4855)
	    // 交互属性9 :  传送锚点 - Teleport Waypoint
	    if (interaction.find(9) == interaction.end())
	    {
		  interaction.insert(9);
	    }
      if (gid == 3419)
	    // 交互属性8 :  传送室内地图
	    if (interaction.find(8) == interaction.end())
	    {
		  interaction.insert(8);
	    }
      if (gid == 1187)
	    // 交互属性8 :  传送室内地图
	    if (interaction.find(8) == interaction.end())
	    {
		  interaction.insert(7);
	    }
      return;
}
bool mapManager::isRefreshMonster(Vec2 position) {
      int tiledPositionX = -(mapMiddleX) * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = (mapMiddleY) * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // 获取地图块所在大格子的地图块
      tiledPositionY = 80 - tiledPositionY;
      tiledPositionX = 40 + tiledPositionX;

      if (map == nullptr)
	    log("map is null");
      // 获取地图块所在大格子的地图块的交互层
      TMXLayer* interactLayer = map->getLayer("interact");
      if (interactLayer == NULL) return false;

      if (tiledPositionX < 0 || tiledPositionX >= 120 || tiledPositionY < 0 || tiledPositionY >= 120)
	    return false;

      // 获取交互层的碰撞信息
      uint32_t gid = interactLayer->getTileGIDAt(Vec2(tiledPositionX, tiledPositionY));
      if (position.x < 20000 && position.y > -20000 && gid == 3339)
          return true;
      if (position.x > 20000 && position.y < -20000 && gid == 5904)
          return true;

      // 只要返回值不为 0，就说明有交互
      return false;
}