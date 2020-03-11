#include "stdafx.h"
#include "loadGame.h"


loadGame::loadGame()
{
}


loadGame::~loadGame()
{
}

bool loadGame::loadgame(int num)
{
	item *_item = nullptr;
	tileMap tilemapTemp;
	tilemapTemp.setTileMap(100,100);
	TagTile_TERRAIN tileTerrainTemp;
	TagTile_Object *tileObjectTemp;
	TILE_TERRAINKIND temp;
	farmland farmlandTemp;
	vSampleTileMapString _vSampleTileMapString_terrian = TILEMAPMANAGER->getSampleTileMapString_terrian();
	vSampleTileMapString _vSampleTileMapString_object = TILEMAPMANAGER->getSampleTileMapString_object();

	char dirTemp[256];
	char strTemp[1000];
	char middleTemp[512], middleTemp2[512];

	string stringTemp;
	int numTemp, numTemp2, numTemp3, numTemp4, numTemp5;

	if (num == 1)
	{
		sprintf(dirTemp, "save/load1.ini");
	}
	else if (num == 2)
	{
		sprintf(dirTemp, "save/load2.ini");
	}
	else if (num == 3)
	{
		sprintf(dirTemp, "save/load3.ini");
	}
	else
	{
		return false;
	}

	ifstream inFile(dirTemp);

	ZeroMemory(strTemp, sizeof(strTemp));
	inFile.getline(strTemp, 1000);

	if (!strcmp(strTemp, "y") == 0)
	{
		return false;
	}
	else
	{
		PLAYERMANAGER->init();
		GAMETIMEMANAGER->init();
		INVENTORYMANAGER->clearInventory();
		ANIMALMANAGER->clearAnimal();
		NPCMANAGER->npcClear();
		FARMMANAGER->farmClear();

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "name : %s\r\n", &middleTemp);
		PLAYERMANAGER->setPlayerName(middleTemp);

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "farmName : %s\r\n", &middleTemp);
		PLAYERMANAGER->setPlayerFarmName(middleTemp);

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "Date : %d, %d\r\n", &numTemp, &numTemp2);

		GAMETIMEMANAGER->setSeason((SEASON)numTemp);
		GAMETIMEMANAGER->setDate(numTemp2);

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerHairColor : %d, %d, %d\r\n", &numTemp, &numTemp2, &numTemp3);
		PLAYERMANAGER->setPlayerHairColor(color{ numTemp, numTemp2, numTemp3 });

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerPantsColor : %d, %d, %d\r\n", &numTemp, &numTemp2, &numTemp3);
		PLAYERMANAGER->setPlayerPantsColor(color{ numTemp, numTemp2, numTemp3 });

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerHairNum : %d\r\n", &numTemp);
		PLAYERMANAGER->setPlayerHairNum(numTemp);

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerShirtsNum : %d\r\n", &numTemp);
		PLAYERMANAGER->setPlayerShirtsNum(numTemp);

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerMoney : %d\r\n", &numTemp);
		PLAYERMANAGER->setPlayerMoney(numTemp);
		
		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerInventorylevel : %d\r\n", &numTemp);

		for (int n = 1; n < numTemp; n++)
		{
			INVENTORYMANAGER->inventoryUpgrade();
		}


		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerInventoryNum : %d\r\n", &numTemp);

		for (int i = 0; i < numTemp; i++)
		{
			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "ItemCategory : %d\r\n", &numTemp2);

			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "ItemDivision : %d\r\n", &numTemp3);

			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "ItemSection : %d\r\n", &numTemp4);

			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "ItemNum : %d\r\n", &numTemp5);


			for (int n = 0; n < numTemp5; n++)
			{
				if (numTemp2 == (int)ITEMKIND_EQUIPMENT)
				{
					//_item = new item_equipment();
				}
				else if (numTemp2 == (int)ITEMKIND_TOOL)
				{
					if (numTemp3 == (int)TOOLKIND_AXE)
					{
						_item = new item_tool_axe();
						_item->init((AXEKIND)numTemp4);
					}
					else if (numTemp3 == (int)TOOLKIND_HOE)
					{
						_item = new item_tool_hoe();
						_item->init((HOEKIND)numTemp4);
					}
					else if (numTemp3 == (int)TOOLKIND_PICKAXE)
					{
						_item = new item_tool_pickaxe();
						_item->init((PICKAXEKIND)numTemp4);
					}
					else if (numTemp3 == (int)TOOLKIND_SCYTHE)
					{
						_item = new item_tool_scythe();
						_item->init((SCYTHEKIND)numTemp4);
					}
					if (numTemp3 == (int)TOOLKIND_WATERINGCAN)
					{
						_item = new item_tool_wateringcan();
						_item->init((WATERINGCANKIND)numTemp4);
					}
				}
				else if (numTemp2 == (int)ITEMKIND_CROPS)
				{
					_item = new item_crops();
					_item->init(numTemp4);
				}
				else if (numTemp2 == (int)ITEMKIND_SEED)
				{
					_item = new item_seed();
					_item->init(numTemp4);
				}
				else if (numTemp2 == (int)ITEMKIND_FOOD)
				{
					_item = new item_food();
					_item->init(numTemp4);
				}
				else if (numTemp2 == (int)ITEMKIND_CRAFTABLE)
				{
					/*
					_item = new item_crops();
					_item->init(numTemp4);
					*/
				}
				else if (numTemp2 == (int)ITEMKIND_ANIMALITEM)
				{
					_item = new item_animalitem();
					_item->init(numTemp4);
				}
				else if (numTemp2 == (int)ITEMKIND_ROCK)
				{
					_item = new item_rock();
					_item->init(numTemp4);
				}
				else if (numTemp2 == (int)ITEMKIND_MATERIAL)
				{
					_item = new item_material();
					_item->init(numTemp4);
				}
				else
				{
					return false;
				}

				INVENTORYMANAGER->addItem(*_item);
				_item = nullptr;
			}
		}

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerCoopAnimalNum : %d\r\n", &numTemp);

		for (int i = 0; i < numTemp; i++)
		{
			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "animalNum : %d\r\n", &numTemp2);

			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "animalPeriod : %d\r\n", &numTemp3);

			ANIMALMANAGER->addAnimal((ANIMAL_KIND)numTemp2, numTemp3);
		}

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "playerBarnAnimalNum : %d\r\n", &numTemp);

		for (int i = 0; i < numTemp; i++)
		{
			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "animalNum : %d\r\n", &numTemp2);

			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "animalPeriod : %d\r\n", &numTemp3);

			ANIMALMANAGER->addAnimal((ANIMAL_KIND)numTemp2, numTemp3);
		}

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "npcNum : %d\r\n", &numTemp);

		for (int i = 0; i < numTemp; i++)
		{
			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "kind : %d, feeling : %d\r\n", &numTemp2, &numTemp3);

			NPCMANAGER->setFeeling(numTemp2, numTemp3);
		}

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				ZeroMemory(strTemp, sizeof(strTemp));
				inFile.getline(strTemp, 1000);
				sscanf_s(strTemp, "%d ,%d, %d, %d, imageframe : %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n",
					&tileTerrainTemp.isTerrain,
					&tileTerrainTemp.isObject,
					&tileTerrainTemp.tileNum,
					&temp,

					&tileTerrainTemp.imageIndex[0],
					&tileTerrainTemp.tileFrame[0].x,
					&tileTerrainTemp.tileFrame[0].y,
					&tileTerrainTemp.imageIndex[1],
					&tileTerrainTemp.tileFrame[1].x,
					&tileTerrainTemp.tileFrame[1].y,
					&tileTerrainTemp.imageIndex[2],
					&tileTerrainTemp.tileFrame[2].x,
					&tileTerrainTemp.tileFrame[2].y
				);

				if (tileTerrainTemp.imageIndex[0] > -1)
				{
					tileTerrainTemp.tileTerrainImg[0] = IMAGEMANAGER->findImage(_vSampleTileMapString_terrian[tileTerrainTemp.imageIndex[0]]);
				}
				if (tileTerrainTemp.imageIndex[1] > -1)
				{
					tileTerrainTemp.tileTerrainImg[1] = IMAGEMANAGER->findImage(_vSampleTileMapString_terrian[tileTerrainTemp.imageIndex[1]]);
				}
				if (tileTerrainTemp.imageIndex[2] > -1)
				{
					tileTerrainTemp.tileTerrainImg[2] = IMAGEMANAGER->findImage(_vSampleTileMapString_terrian[tileTerrainTemp.imageIndex[2]]);
				}

				tilemapTemp.setTile(tileTerrainTemp, j, i, 0);
				tilemapTemp.setTile(tileTerrainTemp, j, i, 1);
				tilemapTemp.setTile(tileTerrainTemp, j, i, 2);

				tilemapTemp.setKindTerrian(temp, j, i);
			}
		}

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "tileMap_object_num : %d\r\n", &numTemp);

		for (int i = 0; i < numTemp; i++)
		{
			tileObjectTemp = new TagTile_Object;

			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 1000);

			sscanf_s(strTemp, "%d ,%d, %d, %d, %d, %d, %d\r\n",
				&(tileObjectTemp->imageIndex),
				&(tileObjectTemp->objectPos.x),
				&(tileObjectTemp->objectPos.y),
				&(tileObjectTemp->objectFrame.x),
				&(tileObjectTemp->objectFrame.y),
				&(tileObjectTemp->sizeX),
				&(tileObjectTemp->sizeY)
			);

			tileObjectTemp->tileObjectImg = IMAGEMANAGER->findImage(_vSampleTileMapString_object[tileObjectTemp->imageIndex]);

			tilemapTemp.addObject(tileObjectTemp);
			tileObjectTemp = nullptr;
		}
		FARMMANAGER->setFarmMap(tilemapTemp);
		FARMMANAGER->setIsFirst(false);

		ZeroMemory(strTemp, sizeof(strTemp));
		inFile.getline(strTemp, 100);
		sscanf_s(strTemp, "farmHoeing_num : %d\r\n", &numTemp);

		for (int i = 0; i < numTemp; i++)
		{
			ZeroMemory(strTemp, sizeof(strTemp));
			inFile.getline(strTemp, 100);
			sscanf_s(strTemp, "%d ,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n",
				&numTemp2,
				&numTemp3,
				&farmlandTemp.crops.kind,
				&farmlandTemp.crops.period,
				&farmlandTemp.crops.max_Period,
				&farmlandTemp.crops.sellValue,
				&farmlandTemp.crops.frame.x,
				&farmlandTemp.crops.frame.y,
				&farmlandTemp.crops.isHarvesting,
				&farmlandTemp.frame.x,
				&farmlandTemp.frame.y,
				&farmlandTemp.isHoeing,
				&farmlandTemp.isCrops);

			FARMMANAGER->setFarmLand(numTemp2, numTemp3, farmlandTemp);
		}

	}

	inFile.close();

	PLAYERMANAGER->setPlayerPosition(480, 480);
	CAMERAMANAGER->setCameraPos(POINT{ 0,0 });

	SCENEMANAGER->changeScene("homeScene");
	return true;
}
