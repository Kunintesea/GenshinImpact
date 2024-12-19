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
	initialMapMiddleX = 3;
	initialMapMiddleY = 2;
	
	// ��ʾ��ͼ������Ӧ�����������ڴ���ӵ�����
	map_00_00 = TMXTiledMap::create("map//new-map-side-2-3.tmx");
	map_00_00->setAnchorPoint(Vec2(0.5f, 0.5f));

	// ��ʼ����ͼ����
	mapSize = map_00_00->getContentSize(); // ��ȡ��ͼ��С
	tileSize = mapSize / 40; // ��ȡ��ͼ���С
	
	// ����������������������������������������������������������
	// �����Ѿ��õ��˾���ľ�������
	// һ���޸��˾���ľ������꣬Ҳ��Ҫ��������Ĳ�����
	// ����������������������������������������������������������
	spritePos = Vec2(visibleSize.width / 3, visibleSize.height / 3);
	mapMiddleX = (int)std::floor(spritePos.x / mapSize.width);
	mapMiddleY = -(int)std::floor(spritePos.y / mapSize.height);
	spritePosChange = Vec2(std::fmod(spritePos.x, mapSize.width), std::fmod(spritePos.y, mapSize.height));

	// �������Ŀ�ĵ�ͼ
	Vec2 middlePos = Vec2((mapMiddleX + 0.5f) * mapSize.width, (-mapMiddleY + 0.5f) * mapSize.height);
	map_00_00->setPosition(middlePos);
	this->addChild(map_00_00, 0);

	MapCreate(map_00_01, -1, 0, middlePos); // ��
	MapCreate(map_01_00, 0, -1, middlePos); // ��
	MapCreate(map_00_10, 1, 0, middlePos); // ��
	MapCreate(map_10_00, 0, 1, middlePos); // ��
	MapCreate(map_10_01, -1, 1, middlePos); // ����
	MapCreate(map_01_01, -1, -1, middlePos); // ����
	MapCreate(map_10_10, 1, 1, middlePos); // ����
	MapCreate(map_01_10, 1, -1, middlePos); // ����

	return true;
}

void mapManager::update(float dt)
{
    //�ȿ����ܲ����ҵ����Ҳ���ֱ�ӷ���
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
      if (spritePosChange.x < 0)
      {
	    // ѡ��ֱ�����õ�ͼ
	    MapReset(middlePos);
	    spritePosChange = spritePosChange + Vec2(mapSize.width, 0);
      }
      // ��
      if (spritePosChange.y < 0)
      {
	    MapReset(middlePos);
	    spritePosChange = spritePosChange + Vec2(0,mapSize.height);
      }
      // ��
      if (spritePosChange.x > mapSize.width)
      {
	    MapReset(middlePos);
	    spritePosChange = spritePosChange - Vec2(mapSize.width,0);
      }
      // ��
      if (spritePosChange.y > mapSize.width)
      {
	    MapReset(middlePos);
	    spritePosChange = spritePosChange - Vec2(0,mapSize.height);
      }

}

void mapManager::MapCreate(TMXTiledMap*& map, int i, int j, Vec2 middlePos) {
      // �����ӵ�ͼ
      char* mapName = new char[40];
      // ��ͼ������ʼ��ͼ���� + ���ھ��������ƫ���� + ��������ƫ����
      // ���� -j ����Ϊ��ͼ����ϵ�;�������ϵ���෴��
      sprintf(mapName, "map//new-map-side-%d-%d.tmx", initialMapMiddleY + mapMiddleY - j, initialMapMiddleX + mapMiddleX + i);
      log("mapName: %s", mapName);
      map = TMXTiledMap::create(mapName);
      // �����ӵ�ͼ����
      map->setAnchorPoint(Vec2(0.5f - i * 0.5f, 0.5f - j * 0.5f));
      map->setPosition(middlePos + Vec2(mapSize.width * 0.5f * i, mapSize.width * 0.5f * j));
      this->addChild(map, 0);
}

void mapManager::MapReset(Vec2 middlePos) {
      map_00_00->removeFromParentAndCleanup(true);
      MapCreate(map_00_00, 0, 0, middlePos);
      map_00_01->removeFromParentAndCleanup(true);
      MapCreate(map_00_01, -1, 0, middlePos); // ��
      map_01_00->removeFromParentAndCleanup(true);
      MapCreate(map_01_00, 0, -1, middlePos); // ��
      map_00_10->removeFromParentAndCleanup(true);
      MapCreate(map_00_10, 1, 0, middlePos); // ��
      map_10_00->removeFromParentAndCleanup(true);
      MapCreate(map_10_00, 0, 1, middlePos); // ��
      map_10_01->removeFromParentAndCleanup(true);
      MapCreate(map_10_01, -1, 1, middlePos); // ����
      map_01_01->removeFromParentAndCleanup(true);
      MapCreate(map_01_01, -1, -1, middlePos); // ����
      map_10_10->removeFromParentAndCleanup(true);
      MapCreate(map_10_10, 1, 1, middlePos); // ����
      map_01_10->removeFromParentAndCleanup(true);
      MapCreate(map_01_10, 1, -1, middlePos); // ����
}

bool mapManager::isCollision(Vec2 position) {
    return false;

      // ��ȡ�������ڴ����
      int tiledMiddleX = (int)std::floor(position.x / mapSize.width);
      int tiledMiddleY = (int)std::floor(position.y / mapSize.height);
      // ��ȡ��ͼ���ڴ������������½ǵĵ�ͼ����
      int tiledPositionX = - tiledMiddleX * 40 + (int)std::floor(position.x / tileSize.width);
      int tiledPositionY = - tiledMiddleY * 40 + (int)std::ceil(position.y == 0 ? 0.1 : position.y / tileSize.height);
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ��
      TMXTiledMap* map = NULL;
      tiledPositionY = 40 - tiledPositionY;

      switch ((tiledMiddleX - mapMiddleX) + (tiledMiddleY + mapMiddleY) * 10)
      {
      case 0: map = map_00_00;  break; // ��
      case -1: map = map_00_01; break; // ��
      case 1: map = map_00_10;  break; // ��
      case -10: map = map_01_00; break; // ��
      case 10: map = map_10_00; break; // ��
      case -11: map = map_01_01; break; // ����
      case 9: map = map_10_01; break; // ����
      case 11: map = map_10_10; break; // ����
      case -9: map = map_01_10; break; // ����
      }

     // if (tiledPositionX < 0)
	    //if (tiledPositionY < 0) { map = map_01_01; tiledPositionX += 40; tiledPositionY += 40; } // ����
	    //else if (tiledPositionY >= 40) { map = map_10_01; tiledPositionX += 40; tiledPositionY -= 40; }// ����
	    //else { map = map_00_01; tiledPositionX += 40; }// ��    
     // else if(tiledPositionX >= 40)
	    //if (tiledPositionY < 0) { map = map_01_10; tiledPositionX -= 40; tiledPositionY += 40; } // ����
	    //else if (tiledPositionY >= 40) { map = map_10_10; tiledPositionX -= 40; tiledPositionY -= 40; } // ����
	    //else { map = map_00_10; tiledPositionX -= 40; } // ��
     // else
	    //if (tiledPositionY < 0) { map = map_01_00; tiledPositionY += 40; } // ��
	    //else if (tiledPositionY >= 40) { map = map_10_00; tiledPositionY -= 40; } // ��
	    //else { map = map_00_00; } // ��
      if (map == nullptr )
	    log("map is null");
      // ��ȡ��ͼ�����ڴ���ӵĵ�ͼ�����ײ��
      TMXLayer* collisionLayer = map->getLayer("colide");
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