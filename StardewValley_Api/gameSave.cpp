#include "stdafx.h"
#include "gameSave.h"


gameSave::gameSave()
{
}


gameSave::~gameSave()
{
}

void gameSave::nowGameSave(int num)
{
	int hoeingNum = 0;
	int hoeingMaxNum = FARMMANAGER->getHoeingFieldNum();

	int itemNum=0;
	char dirTemp[256];
	char strTemp[1000];

	playerState playerstate = PLAYERMANAGER->getPlayerState();
	playerAvatar playeravatar = PLAYERMANAGER->getPlayerAvatar();
	inventory inven = INVENTORYMANAGER->getInventory();
	item items;
	tileMap tilemapTemp = FARMMANAGER->getFarmMap();
	bTileMap bTilemapTemp = tilemapTemp.getTileMap();
	vTileObject vTileObjectTemp = tilemapTemp.getTileObject();
	vector<animal> coopTemp = ANIMALMANAGER->getAniMalCoopVector();
	vector<animal> barnTemp = ANIMALMANAGER->getAniMalBarnVector();
	vector<npc *>npcTemp = NPCMANAGER->getNpcVector();
	vFarmland farmLandTemp = FARMMANAGER->getFarmLand();


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
		return;
	}

	file = CreateFile(dirTemp, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "y\r\n");
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	if (playerstate.getPlayerName().size() > 0)
	{
		sprintf_s(strTemp, "name : %s\r\n", playerstate.getPlayerName().c_str());
	}
	else
	{
		sprintf_s(strTemp, "name : notName\r\n");
	}
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);


	ZeroMemory(strTemp, sizeof(strTemp));
	if (playerstate.getPlayerFarmName().size() > 0)
	{
		sprintf_s(strTemp, "farmName : %s\r\n", playerstate.getPlayerFarmName().c_str());
	}
	else
	{
		sprintf_s(strTemp, "farmName : notName\r\n");
	}
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "Date : %d, %d\r\n", (int)GAMETIMEMANAGER->getSeason(), GAMETIMEMANAGER->getDate());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerHairColor : %d, %d, %d\r\n", playeravatar.getPlayerHairColor().r, playeravatar.getPlayerHairColor().g, playeravatar.getPlayerHairColor().b);
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerPantsColor : %d, %d, %d\r\n", playeravatar.getPlayerPantsColor().r, playeravatar.getPlayerPantsColor().g, playeravatar.getPlayerPantsColor().b);
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerHairNum : %d\r\n", playeravatar.getPlayerHairNum());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerShirtsNum : %d\r\n", playeravatar.getPlayerShirtsNum());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerMoney : %d\r\n", playerstate.getPlayerMoney());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerInventorylevel : %d\r\n", inven.getInventoryLevel());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerInventoryNum : %d\r\n", inven.getNowSize());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	for (int i = 0; itemNum < inven.getNowSize(); i++)
	{
		itemNum += 1;
		items = inven.getItem(i % 12, i / 12);

		if (items.getItemCategory() == ITEMKIND_NULL)
		{
			itemNum--;
			continue;
		}

		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "ItemCategory : %d\r\n", (int)items.getItemCategory());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "ItemDivision : %d\r\n", (int)items.getItemDivision());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "ItemSection : %d\r\n", (int)items.getItemSection());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "ItemNum : %d\r\n", (int)items.getItemNum());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);
	}

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerCoopAnimalNum : %d\r\n", coopTemp.size());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	for (int i = 0; i < coopTemp.size(); i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "animalNum : %d\r\n", (int)coopTemp[i].getKind());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);


		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "animalPeriod : %d\r\n", (int)coopTemp[i].getLifePeriod());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);
	}

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "playerBarnAnimalNum : %d\r\n", barnTemp.size());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);


	for (int i = 0; i < barnTemp.size(); i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "animalNum : %d\r\n", (int)barnTemp[i].getKind());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "animalPeriod : %d\r\n", (int)barnTemp[i].getLifePeriod());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);
	}

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "npcNum : %d\r\n", npcTemp.size());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	for (int i = 0; i < npcTemp.size(); i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));
		sprintf_s(strTemp, "kind : %d, feeling : %d\r\n", i, npcTemp[i]->getFeeling());
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			ZeroMemory(strTemp, sizeof(strTemp));
			sprintf_s(strTemp, "%d ,%d, %d, %d, imageframe : %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n",
				bTilemapTemp[i][j].isTerrain,
				bTilemapTemp[i][j].isObject,
				bTilemapTemp[i][j].tileNum,
				bTilemapTemp[i][j].tile_terrainKind,
				bTilemapTemp[i][j].imageIndex[0],
				bTilemapTemp[i][j].tileFrame[0].x,
				bTilemapTemp[i][j].tileFrame[0].y,
				bTilemapTemp[i][j].imageIndex[1],
				bTilemapTemp[i][j].tileFrame[1].x,
				bTilemapTemp[i][j].tileFrame[1].y,
				bTilemapTemp[i][j].imageIndex[2],
				bTilemapTemp[i][j].tileFrame[2].x,
				bTilemapTemp[i][j].tileFrame[2].y
			);

			WriteFile(file, strTemp, strlen(strTemp), &write, NULL);
		}
	}

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "tileMap_object_num : %d\r\n", vTileObjectTemp.size());
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	for (int i = 0; i < vTileObjectTemp.size(); i++)
	{
		ZeroMemory(strTemp, sizeof(strTemp));

		sprintf_s(strTemp, "%d ,%d, %d, %d, %d, %d, %d\r\n",
			(vTileObjectTemp[i]->imageIndex),
			(vTileObjectTemp[i]->objectPos.x),
			(vTileObjectTemp[i]->objectPos.y),
			(vTileObjectTemp[i]->objectFrame.x),
			(vTileObjectTemp[i]->objectFrame.y),
			(vTileObjectTemp[i]->sizeX),
			(vTileObjectTemp[i]->sizeY)
		);
		WriteFile(file, strTemp, strlen(strTemp), &write, NULL);
	}

	ZeroMemory(strTemp, sizeof(strTemp));
	sprintf_s(strTemp, "farmHoeing_num : %d\r\n", hoeingMaxNum);
	WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (farmLandTemp[i][j].isHoeing)
			{
				ZeroMemory(strTemp, sizeof(strTemp));
				sprintf_s(strTemp, "%d ,%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n",
					j,
					i,
					farmLandTemp[i][j].crops.kind,
					farmLandTemp[i][j].crops.period,
					farmLandTemp[i][j].crops.max_Period,
					farmLandTemp[i][j].crops.sellValue,
					farmLandTemp[i][j].crops.frame.x,
					farmLandTemp[i][j].crops.frame.y,
					farmLandTemp[i][j].crops.isHarvesting,
					farmLandTemp[i][j].frame.x,
					farmLandTemp[i][j].frame.y,
					farmLandTemp[i][j].isHoeing,
					farmLandTemp[i][j].isCrops);
				WriteFile(file, strTemp, strlen(strTemp), &write, NULL);

				hoeingNum++;
			}
		}
		if (hoeingNum >= hoeingMaxNum)
		{
			break;
		}
	}


	CloseHandle(file);
}
