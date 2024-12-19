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
	initialMapMiddleX = 3;
	initialMapMiddleY = 2;
	
	// 显示地图的中心应该是人物所在大格子的中心
	map_00_00 = TMXTiledMap::create("map//new-map-side-2-3.tmx");
	map_00_00->setAnchorPoint(Vec2(0.5f, 0.5f));

	// 初始化地图参数
	mapSize = map_00_00->getContentSize(); // 获取地图大小
	tileSize = mapSize / 40; // 获取地图块大小
	
	// ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	// 假设已经得到了精灵的绝对坐标
	// 一旦修改了精灵的绝对坐标，也需要更改这里的参数！
	// ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	spritePos = Vec2(visibleSize.width / 3, visibleSize.height / 3);
	mapMiddleX = (int)std::floor(spritePos.x / mapSize.width);
	mapMiddleY = -(int)std::floor(spritePos.y / mapSize.height);
	spritePosChange = Vec2(std::fmod(spritePos.x, mapSize.width), std::fmod(spritePos.y, mapSize.height));

	// 建立中心块的地图
	Vec2 middlePos = Vec2((mapMiddleX + 0.5f) * mapSize.width, (-mapMiddleY + 0.5f) * mapSize.height);
	map_00_00->setPosition(middlePos);
	this->addChild(map_00_00, 0);

	MapCreate(map_00_01, -1, 0, middlePos); // 左
	MapCreate(map_01_00, 0, -1, middlePos); // 下
	MapCreate(map_00_10, 1, 0, middlePos); // 右
	MapCreate(map_10_00, 0, 1, middlePos); // 上
	MapCreate(map_10_01, -1, 1, middlePos); // 左上
	MapCreate(map_01_01, -1, -1, middlePos); // 左下
	MapCreate(map_10_10, 1, 1, middlePos); // 右上
	MapCreate(map_01_10, 1, -1, middlePos); // 右下

	return true;
}

void mapManager::update(float dt)
{
    //先看看能不能找到，找不到直接返回
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
      if (spritePosChange.x < 0)
      {
	    // 选择直接重置地图
	    MapReset(middlePos);
	    spritePosChange = spritePosChange + Vec2(mapSize.width, 0);
      }
      // 下
      if (spritePosChange.y < 0)
      {
	    MapReset(middlePos);
	    spritePosChange = spritePosChange + Vec2(0,mapSize.height);
      }
      // 右
      if (spritePosChange.x > mapSize.width)
      {
	    MapReset(middlePos);
	    spritePosChange = spritePosChange - Vec2(mapSize.width,0);
      }
      // 上
      if (spritePosChange.y > mapSize.width)
      {
	    MapReset(middlePos);
	    spritePosChange = spritePosChange - Vec2(0,mapSize.height);
      }

}

void mapManager::MapCreate(TMXTiledMap*& map, int i, int j, Vec2 middlePos) {
      // 创建子地图
      char* mapName = new char[40];
      // 地图名：初始地图块名 + 基于精灵坐标的偏移量 + 上下左右偏移量
      // 这里 -j 是因为地图坐标系和精灵坐标系是相反的
      sprintf(mapName, "map//new-map-side-%d-%d.tmx", initialMapMiddleY + mapMiddleY - j, initialMapMiddleX + mapMiddleX + i);
      log("mapName: %s", mapName);
      map = TMXTiledMap::create(mapName);
      // 设置子地图属性
      map->setAnchorPoint(Vec2(0.5f - i * 0.5f, 0.5f - j * 0.5f));
      map->setPosition(middlePos + Vec2(mapSize.width * 0.5f * i, mapSize.width * 0.5f * j));
      this->addChild(map, 0);
}

void mapManager::MapReset(Vec2 middlePos) {
      map_00_00->removeFromParentAndCleanup(true);
      MapCreate(map_00_00, 0, 0, middlePos);
      map_00_01->removeFromParentAndCleanup(true);
      MapCreate(map_00_01, -1, 0, middlePos); // 左
      map_01_00->removeFromParentAndCleanup(true);
      MapCreate(map_01_00, 0, -1, middlePos); // 下
      map_00_10->removeFromParentAndCleanup(true);
      MapCreate(map_00_10, 1, 0, middlePos); // 右
      map_10_00->removeFromParentAndCleanup(true);
      MapCreate(map_10_00, 0, 1, middlePos); // 上
      map_10_01->removeFromParentAndCleanup(true);
      MapCreate(map_10_01, -1, 1, middlePos); // 左上
      map_01_01->removeFromParentAndCleanup(true);
      MapCreate(map_01_01, -1, -1, middlePos); // 左下
      map_10_10->removeFromParentAndCleanup(true);
      MapCreate(map_10_10, 1, 1, middlePos); // 右上
      map_01_10->removeFromParentAndCleanup(true);
      MapCreate(map_01_10, 1, -1, middlePos); // 右下
}

bool mapManager::isCollision(Vec2 position) {
    return false;

      // 获取人物所在大格子
      int tiledMiddleX = (int)std::floor(position.x / mapSize.width);
      int tiledMiddleY = (int)std::floor(position.y / mapSize.height);
      // 获取地图块在大格子里面的左下角的地图坐标
      int tiledPositionX = - tiledMiddleX * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = - tiledMiddleY * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // 获取地图块所在大格子的地图块
      TMXTiledMap* map = NULL;
      tiledPositionY = 40 - tiledPositionY;

      switch ((tiledMiddleX - mapMiddleX) + (tiledMiddleY + mapMiddleY) * 10)
      {
      case 0: map = map_00_00;  break; // 中
      case -1: map = map_00_01; break; // 左
      case 1: map = map_00_10;  break; // 右
      case -10: map = map_01_00; break; // 下
      case 10: map = map_10_00; break; // 上
      case -11: map = map_01_01; break; // 左下
      case 9: map = map_10_01; break; // 左上
      case 11: map = map_10_10; break; // 右上
      case -9: map = map_01_10; break; // 右下
      }

     // if (tiledPositionX < 0)
	    //if (tiledPositionY < 0) { map = map_01_01; tiledPositionX += 40; tiledPositionY += 40; } // 左下
	    //else if (tiledPositionY >= 40) { map = map_10_01; tiledPositionX += 40; tiledPositionY -= 40; }// 左上
	    //else { map = map_00_01; tiledPositionX += 40; }// 左    
     // else if(tiledPositionX >= 40)
	    //if (tiledPositionY < 0) { map = map_01_10; tiledPositionX -= 40; tiledPositionY += 40; } // 右下
	    //else if (tiledPositionY >= 40) { map = map_10_10; tiledPositionX -= 40; tiledPositionY -= 40; } // 右上
	    //else { map = map_00_10; tiledPositionX -= 40; } // 右
     // else
	    //if (tiledPositionY < 0) { map = map_01_00; tiledPositionY += 40; } // 下
	    //else if (tiledPositionY >= 40) { map = map_10_00; tiledPositionY -= 40; } // 上
	    //else { map = map_00_00; } // 中
      if (map == nullptr )
	    log("map is null");
      // 获取地图块所在大格子的地图块的碰撞层
      TMXLayer* collisionLayer = map->getLayer("colide");
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