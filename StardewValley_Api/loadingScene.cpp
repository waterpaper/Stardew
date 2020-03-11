#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_sceneName = SCENE_NAME_LOADDING_SCENE;

	scene::init();

	_loading = new loading;
	_loading->init();

	this->totalLoding();

	return S_OK;
}

void loadingScene::update()
{
	scene::update();
	_loading->update();

	//�ε��� ������ ü����
	if (_loading->loadingDone())
	{
		gameNode::init(true, true);

		SCENEMANAGER->changeScene("titleScene");
	}

}

void loadingScene::release()
{
	scene::release();
	SAFE_DELETE(_loading);
}

void loadingScene::render()
{
	scene::render();
	_loading->render();
}

void loadingScene::totalLoding()
{
	//----------------------------------------------------------------------------------------------
	//�÷��̾� �ε��Դϴ�
	_loading->loadFrameImage("playerHair", "images/player/player_hairs.bmp", 512 * 3, 128 * 3, 32, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerBody", "images/player/player_body.bmp", 96 * 3, 512 * 3, 6, 16, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerArm", "images/player/player_arm.bmp", 96 * 3, 640 * 3, 6, 20, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerShirts", "images/player/player_shirts.bmp", 896 * 3, 32 * 3, 112, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerPants", "images/player/player_pants.bmp", 96 * 3, 512 * 3, 6, 16, true, RGB(255, 0, 255));
	_loading->loadImage("�׸���", "images/player/player_shadow.bmp", 36, 21, true, RGB(255, 0, 255));


	_loading->loadFrameImage("tool_axe", "images/player/tool_axe.bmp",110*3, 88 * 3, 5, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_hoe", "images/player/tool_hoe.bmp",110*3, 88 * 3, 5, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_pickaxe", "images/player/tool_pickaxe.bmp", 110*3, 88 * 3, 5, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_wateringcan", "images/player/tool_wateringcan.bmp", 66 * 3, 88 * 3, 3, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_scythe", "images/player/tool_scythe.bmp", 96 * 3, 64 * 3, 6, 4, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//���� �ε��Դϴ�
	_loading->loadFrameImage("Ÿ��_�⺻1_��", "images/maptool/maptool_tile1_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻1_����", "images/maptool/maptool_tile1_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻1_����", "images/maptool/maptool_tile1_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻1_�ܿ�", "images/maptool/maptool_tile1_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻2_��", "images/maptool/maptool_tile2_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻2_����", "images/maptool/maptool_tile2_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻2_����", "images/maptool/maptool_tile2_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻2_�ܿ�", "images/maptool/maptool_tile2_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻3_��", "images/maptool/maptool_tile3_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻3_����", "images/maptool/maptool_tile3_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻3_����", "images/maptool/maptool_tile3_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_�⺻3_�ܿ�", "images/maptool/maptool_tile3_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Ÿ��_Ÿ��1_��", "images/maptool/maptool_tile_town1_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��1_����", "images/maptool/maptool_tile_town1_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��1_����", "images/maptool/maptool_tile_town1_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��1_�ܿ�", "images/maptool/maptool_tile_town1_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��2_��", "images/maptool/maptool_tile_town2_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��2_����", "images/maptool/maptool_tile_town2_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��2_����", "images/maptool/maptool_tile_town2_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��2_�ܿ�", "images/maptool/maptool_tile_town2_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��3_��", "images/maptool/maptool_tile_town3_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��3_����", "images/maptool/maptool_tile_town3_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��3_����", "images/maptool/maptool_tile_town3_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_Ÿ��3_�ܿ�", "images/maptool/maptool_tile_town3_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_��1", "images/maptool/maptool_tile_house1.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_��2", "images/maptool/maptool_tile_house2.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_��1", "images/maptool/maptool_tile_shop1.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_��2", "images/maptool/maptool_tile_shop2.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_��3", "images/maptool/maptool_tile_shop3.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��_����1", "images/maptool/maptool_tile_farm1.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));

	_loading->loadFrameImage("Ÿ��_����", "images/maptool/maptool_hoedirt.bmp", 384, 192, 8, 4, true, RGB(255, 0, 255));

	_loading->loadImage("������Ʈ_Ǯ", "images/maptool/maptool_grass.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("������Ʈ_��", "images/maptool/maptool_rock.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("������Ʈ_��������", "images/maptool/maptool_wood.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ_����1", "images/maptool/maptool_tree1.bmp", 576, 288, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ_����2", "images/maptool/maptool_tree2.bmp", 576, 288, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������Ʈ_����3", "images/maptool/maptool_tree3.bmp", 576, 288, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("������Ʈ_����1_����", "images/maptool/maptool_tree1_down.bmp", 2592, 2160, 9, 5, true, RGB(255, 0, 255));

	//���� UI
	_loading->loadImage("����â_���", "images/ui/maptool/Ui_maptool_subscene.bmp", 500, 768, true, RGB(255, 0, 255));
	_loading->loadImage("����â_ī�޶�", "images/ui/maptool/Ui_maptool_camera.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadImage("����â_���ü���", "images/ui/maptool/Ui_maptool_camera.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_Ÿ�Ϲ�ư", "images/ui/maptool/Ui_maptool_tile.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_������Ʈ��ư", "images/ui/maptool/Ui_maptool_object.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�Ӽ���ư", "images/ui/maptool/Ui_maptool_attribute.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�̹�����ư", "images/ui/maptool/Ui_maptool_image.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�������ư", "images/ui/maptool/Ui_maptool_exit.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_������ư", "images/ui/maptool/Ui_maptool_erase.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�ʱ�ȭ��ư", "images/ui/maptool/Ui_maptool_init.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�����ư", "images/ui/maptool/Ui_maptool_save.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�ε��ư", "images/ui/maptool/Ui_maptool_load.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_��������ư", "images/ui/maptool/Ui_maptool_sizechange.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("����â_������ư", "images/ui/maptool/Ui_maptool_nextButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_������ư", "images/ui/maptool/Ui_maptool_beforeButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_����ư", "images/ui/maptool/Ui_maptool_upButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�Ʒ���ư", "images/ui/maptool/Ui_maptool_downButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("����â_�Ӽ����ư", "images/ui/maptool/Ui_maptool_soil.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�Ӽ�Ǯ��ư", "images/ui/maptool/Ui_maptool_grass.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�Ӽ��Ϲݹ�ư", "images/ui/maptool/Ui_maptool_normal.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����â_�Ӽ��̵��Ұ���ư", "images/ui/maptool/Ui_maptool_notMove.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//�� �ε��Դϴ�

	//�� �̹���
	_loading->loadImage("ingame_Minimap.bmp", "images/background/ingame_Minimap.bmp", 300, 180, true, RGB(255, 0, 255));
	_loading->loadImage("back.bmp", "images/background/back.bmp", 1816, 776, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//UI�ε� �Դϴ�
	_loading->loadImage("���ο����Ui", "images/ui/Ui_newStartScene.bmp", 750, 655, true, RGB(255, 0, 255));
	_loading->loadImage("��Ʈ�ѹ�Back", "images/ui/Ui_controlBarBack.bmp", 255, 4, true, RGB(255, 0, 255));
	_loading->loadImage("��Ʈ�ѹ�Front", "images/ui/Ui_controlBarFront.bmp", 255, 4, true, RGB(255, 0, 255));
	_loading->loadImage("��Ʈ�ѹ�ư", "images/ui/Ui_controlButton.bmp", 16, 20, true, RGB(255, 0, 255));
	_loading->loadImage("okay��ư", "images/ui/Ui_okayButton.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadFrameImage("cancel��ư", "images/ui/Ui_cancelButton.bmp", 26 * 3, 12 * 3, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("UI_����������", "images/ui/Ui_itemInfo.bmp", 295, 431, true, RGB(255, 0, 255));
	_loading->loadImage("UI_����������_�ൿ��", "images/ui/Ui_itemInfo_actting.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("UI_����������_ü��", "images/ui/Ui_itemInfo_hp.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("UI_�������Լ�", "images/ui/Ui_getItem.bmp", 287, 96, true, RGB(255, 0, 255));
	_loading->loadImage("UI_�κ��丮Ǯ", "images/ui/Ui_fullinventory.bmp", 287, 96, true, RGB(255, 0, 255));
	_loading->loadImage("UI_������", "images/ui/Ui_notMoney.bmp", 287, 96, true, RGB(255, 0, 255));
	_loading->loadImage("UI_���ùڽ�", "images/ui/Ui_selectBox.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("UI_���ùڽ�2", "images/ui/Ui_selectBox2.bmp", 768, 48, true, RGB(255, 0, 255));
	_loading->loadImage("UI_��Ʈ", "images/ui/Ui_menu_goodFeeling.bmp", 24, 21, true, RGB(255, 0, 255));
	_loading->loadImage("UI_����Ʈ", "images/ui/Ui_menu_notFeeling.bmp", 24, 21, true, RGB(255, 0, 255));

	_loading->loadFrameImage("ȭ��UI_timer", "images/ui/Ui_timer.bmp", 2070, 183, 9, 1, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ��UI_HpEnergyBar", "images/ui/Ui_Hp_Energy_bar.bmp", 90, 180, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ��UI_HpBar_Front", "images/ui/Ui_hp_energy_bar_front.bmp", 20, 132, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ��UI_EnergyBar_Front", "images/ui/Ui_hp_energy_bar_front.bmp", 20, 132, true, RGB(255, 0, 255));
	_loading->loadImage("ȭ��UI_MainInventory", "images/ui/Ui_mainInventory.bmp", 655, 90, true, RGB(255, 0, 255));

	_loading->loadImage("�޴�â_�κ��丮1", "images/ui/Ui_menu_inventory1.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("�޴�â_�κ��丮2", "images/ui/Ui_menu_inventory2.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("�޴�â_�κ��丮3", "images/ui/Ui_menu_inventory3.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("�޴�â_ȣ����", "images/ui/Ui_menu_feelingMenu.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("�޴�â_�̴ϸ�", "images/ui/Ui_menu_mapMenu.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("�޴�â_����", "images/ui/Ui_menu_makingMenu.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("�޴�â_������", "images/ui/Ui_menu_exit.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�޴�â_������޴�_Ÿ��Ʋ", "images/ui/Ui_menu_titleButton.bmp", 560, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�޴�â_������޴�_������", "images/ui/Ui_menu_exitButton.bmp", 424, 104, 2, 1, true, RGB(255, 0, 255));

	_loading->loadImage("����UI_����â", "images/ui/Ui_shop.bmp", 893, 595, true, RGB(255, 0, 255));
	_loading->loadImage("����UI_����â�ٹ�ư", "images/ui/Ui_shop_button.bmp", 13, 22, true, RGB(255, 0, 255));
	_loading->loadImage("����UI_��������â", "images/ui/Ui_animalShop.bmp", 500, 420, true, RGB(255, 0, 255));
	_loading->loadImage("����UI_����1", "images/ui/Ui_shop_bag1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("����UI_����2", "images/ui/Ui_shop_bag2.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("��ȭUI_��ȭâ", "images/ui/Ui_dialog.bmp", 800, 284, true, RGB(255, 0, 255));
	_loading->loadImage("��ȭUI_����", "images/ui/Ui_selectdialog.bmp", 800, 228, true, RGB(255, 0, 255));

	_loading->loadImage("UI_�ε�ȭ��", "images/ui/Ui_loadingScene.bmp", 1024, 768, true, RGB(255, 0, 255));
	_loading->loadImage("UI_Ű����ȭ��", "images/ui/Ui_keyExplanation.bmp", 800, 558, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//���� �ε��Դϴ�


	//---------------------------------------------------------------------------------------------
	//������Ʈ �ε��Դϴ�
	_loading->loadFrameImage("������Ʈ_���۹�", "images/object/object_crops.bmp", 384, 1536, 8, 16, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//������ �ε��Դϴ�
	_loading->loadFrameImage("������_tool", "images/item/item_tool.bmp", 240, 240, 5, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������_seed", "images/item/item_seed.bmp", 288, 240, 6, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������_crops", "images/item/item_crops.bmp", 288, 240, 6, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������_animalitem", "images/item/item_animalitem.bmp", 112*3, 16*3, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������_food", "images/item/item_food.bmp", 288, 48, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������_rock", "images/item/item_rock.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("������_material", "images/item/item_material.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//NPC �ε��Դϴ�
	_loading->loadFrameImage("ĳ����_�������", "images/character/character_abigail.bmp", 64*3, 128*3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ĳ����_���и�", "images/character/character_emily.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ĳ����_����", "images/character/character_leah.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ĳ����_����", "images/character/character_marnie.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ĳ����_�ǿ���", "images/character/character_pierre.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ����_�ʻ�ȭ_�������", "images/character/character_portrait_abigail.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("ĳ����_�ʻ�ȭ_���и�", "images/character/character_portrait_emily.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("ĳ����_�ʻ�ȭ_����", "images/character/character_portrait_leah.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("ĳ����_�ʻ�ȭ_����", "images/character/character_portrait_marnie.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("ĳ����_�ʻ�ȭ_�ǿ���", "images/character/character_portrait_pierre.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("ĳ����_ȣ����_�������", "images/character/character_feeling_abigail.bmp", 64,64, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ����_ȣ����_���и�", "images/character/character_feeling_emily.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ����_ȣ����_����", "images/character/character_feeling_leah.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ����_ȣ����_����", "images/character/character_feeling_marnie.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ����_ȣ����_�ǿ���", "images/character/character_feeling_pierre.bmp", 64, 64, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//���� �ε��Դϴ�
	_loading->loadFrameImage("����_���", "images/character/animal/animal_babyChicken.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_��", "images/character/animal/animal_chicken.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_�����", "images/character/animal/animal_babyDuck.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_����", "images/character/animal/animal_duck.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_��䳢", "images/character/animal/animal_babyRabbit.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_�䳢", "images/character/animal/animal_rabbit.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_���", "images/character/animal/animal_babyCow.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_��", "images/character/animal/animal_cow.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_�����", "images/character/animal/animal_babyGoat.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_����", "images/character/animal/animal_goat.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_���", "images/character/animal/animal_babySheep.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_��", "images/character/animal/animal_sheep.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_�����", "images/character/animal/animal_babyPig.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����_����", "images/character/animal/animal_pig.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//����ȭ�� �ε��Դϴ�

	_loading->loadImage("Ÿ��Ʋ���", "images/title/title_backGround.bmp", WINSIZEX, WINSIZEY * 2, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ��Ʋ�̹���1", "images/title/titleImage1.bmp", WINSIZEX, WINSIZEY / 2, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ��Ʋ�̹���2", "images/title/titleImage2.bmp", WINSIZEX, WINSIZEY / 2, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ��Ʋ�̹���3", "images/title/titleImage3.bmp", WINSIZEX, WINSIZEY / 2, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ��Ʋ����1", "images/title/title_cloud1.bmp", 123 * 3, 54 * 3, true, RGB(0, 0, 255));
	_loading->loadImage("Ÿ��Ʋ����2", "images/title/title_cloud2.bmp", 64 * 3, 36 * 3, true, RGB(0, 0, 255));
	_loading->loadImage("Ÿ��Ʋ����3", "images/title/title_cloud3.bmp", 480, 344, true, RGB(0, 0, 255));
	_loading->loadImage("Ÿ��Ʋ����4", "images/title/title_cloud4.bmp", 123 * 3, 79 * 3, true, RGB(0, 0, 255));
	_loading->loadFrameImage("Ÿ��Ʋ��", "images/title/title_bird.bmp", 104 * 3, 18 * 3, 4, 1, true, RGB(255, 0, 255));

	_loading->loadImage("Ÿ��Ʋ", "images/title/title_stardewvalley.bmp", 398 * 2, 187 * 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��Ʋ����", "images/title/title_newButton.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��Ʋ�ε�", "images/title/title_loadButton.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��Ʋ����", "images/title/title_coop.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Ÿ��Ʋ������", "images/title/title_exitButton.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));

	_loading->loadImage("�ε�ȭ��", "images/title/title_loadSceneImage.bmp", 1024, 768, true, RGB(255, 0, 255));


	//����Ʈ �ε��Դϴ�
	_loading->loadFrameImage("����Ʈ_ȣ����", "images/animation/animation_hoe.bmp", 384, 48, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ʈ_��Ȯ", "images/animation/animation_cropsHarvesting.bmp", 288, 96, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ʈ_������", "images/animation/animation_rock.bmp", 384, 48, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ʈ_Ǯ����", "images/animation/animation_grass.bmp", 336, 48, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ʈ_��", "images/animation/animation_water.bmp", 480, 48, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ʈ_��������", "images/animation/animation_removeTree.bmp", 2800, 160, 10, 1, true, RGB(255, 0, 255));
}
