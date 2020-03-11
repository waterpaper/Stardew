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

	//로딩이 끝나면 체인지
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
	//플레이어 로드입니다
	_loading->loadFrameImage("playerHair", "images/player/player_hairs.bmp", 512 * 3, 128 * 3, 32, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerBody", "images/player/player_body.bmp", 96 * 3, 512 * 3, 6, 16, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerArm", "images/player/player_arm.bmp", 96 * 3, 640 * 3, 6, 20, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerShirts", "images/player/player_shirts.bmp", 896 * 3, 32 * 3, 112, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("playerPants", "images/player/player_pants.bmp", 96 * 3, 512 * 3, 6, 16, true, RGB(255, 0, 255));
	_loading->loadImage("그림자", "images/player/player_shadow.bmp", 36, 21, true, RGB(255, 0, 255));


	_loading->loadFrameImage("tool_axe", "images/player/tool_axe.bmp",110*3, 88 * 3, 5, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_hoe", "images/player/tool_hoe.bmp",110*3, 88 * 3, 5, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_pickaxe", "images/player/tool_pickaxe.bmp", 110*3, 88 * 3, 5, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_wateringcan", "images/player/tool_wateringcan.bmp", 66 * 3, 88 * 3, 3, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("tool_scythe", "images/player/tool_scythe.bmp", 96 * 3, 64 * 3, 6, 4, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//맵툴 로드입니다
	_loading->loadFrameImage("타일_기본1_봄", "images/maptool/maptool_tile1_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본1_여름", "images/maptool/maptool_tile1_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본1_가을", "images/maptool/maptool_tile1_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본1_겨울", "images/maptool/maptool_tile1_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본2_봄", "images/maptool/maptool_tile2_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본2_여름", "images/maptool/maptool_tile2_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본2_가을", "images/maptool/maptool_tile2_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본2_겨울", "images/maptool/maptool_tile2_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본3_봄", "images/maptool/maptool_tile3_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본3_여름", "images/maptool/maptool_tile3_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본3_가을", "images/maptool/maptool_tile3_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_기본3_겨울", "images/maptool/maptool_tile3_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));

	_loading->loadFrameImage("타일_타운1_봄", "images/maptool/maptool_tile_town1_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운1_여름", "images/maptool/maptool_tile_town1_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운1_가을", "images/maptool/maptool_tile_town1_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운1_겨울", "images/maptool/maptool_tile_town1_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운2_봄", "images/maptool/maptool_tile_town2_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운2_여름", "images/maptool/maptool_tile_town2_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운2_가을", "images/maptool/maptool_tile_town2_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운2_겨울", "images/maptool/maptool_tile_town2_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운3_봄", "images/maptool/maptool_tile_town3_spring.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운3_여름", "images/maptool/maptool_tile_town3_summer.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운3_가을", "images/maptool/maptool_tile_town3_fall.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_타운3_겨울", "images/maptool/maptool_tile_town3_winter.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_집1", "images/maptool/maptool_tile_house1.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_집2", "images/maptool/maptool_tile_house2.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_샵1", "images/maptool/maptool_tile_shop1.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_샵2", "images/maptool/maptool_tile_shop2.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_샵3", "images/maptool/maptool_tile_shop3.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타일_농장1", "images/maptool/maptool_tile_farm1.bmp", 192 * 3, 192 * 3, 12, 12, true, RGB(255, 0, 255));

	_loading->loadFrameImage("타일_농지", "images/maptool/maptool_hoedirt.bmp", 384, 192, 8, 4, true, RGB(255, 0, 255));

	_loading->loadImage("오브젝트_풀", "images/maptool/maptool_grass.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("오브젝트_돌", "images/maptool/maptool_rock.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("오브젝트_나무조각", "images/maptool/maptool_wood.bmp", 16 * 3, 16 * 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("오브젝트_나무1", "images/maptool/maptool_tree1.bmp", 576, 288, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("오브젝트_나무2", "images/maptool/maptool_tree2.bmp", 576, 288, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("오브젝트_나무3", "images/maptool/maptool_tree3.bmp", 576, 288, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("오브젝트_나무1_벌목", "images/maptool/maptool_tree1_down.bmp", 2592, 2160, 9, 5, true, RGB(255, 0, 255));

	//맵툴 UI
	_loading->loadImage("맵툴창_배경", "images/ui/maptool/Ui_maptool_subscene.bmp", 500, 768, true, RGB(255, 0, 255));
	_loading->loadImage("맵툴창_카메라", "images/ui/maptool/Ui_maptool_camera.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadImage("맵툴창_샘플선택", "images/ui/maptool/Ui_maptool_camera.bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_타일버튼", "images/ui/maptool/Ui_maptool_tile.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_오브젝트버튼", "images/ui/maptool/Ui_maptool_object.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_속성버튼", "images/ui/maptool/Ui_maptool_attribute.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_이미지버튼", "images/ui/maptool/Ui_maptool_image.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_나가기버튼", "images/ui/maptool/Ui_maptool_exit.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_지우기버튼", "images/ui/maptool/Ui_maptool_erase.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_초기화버튼", "images/ui/maptool/Ui_maptool_init.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_저장버튼", "images/ui/maptool/Ui_maptool_save.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_로드버튼", "images/ui/maptool/Ui_maptool_load.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_사이즈변경버튼", "images/ui/maptool/Ui_maptool_sizechange.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("맵툴창_다음버튼", "images/ui/maptool/Ui_maptool_nextButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_이전버튼", "images/ui/maptool/Ui_maptool_beforeButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_위버튼", "images/ui/maptool/Ui_maptool_upButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_아래버튼", "images/ui/maptool/Ui_maptool_downButton.bmp", 48, 24, 2, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("맵툴창_속성흙버튼", "images/ui/maptool/Ui_maptool_soil.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_속성풀버튼", "images/ui/maptool/Ui_maptool_grass.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_속성일반버튼", "images/ui/maptool/Ui_maptool_normal.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("맵툴창_속성이동불가버튼", "images/ui/maptool/Ui_maptool_notMove.bmp", 200, 80, 2, 1, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//씬 로드입니다

	//씬 이미지
	_loading->loadImage("ingame_Minimap.bmp", "images/background/ingame_Minimap.bmp", 300, 180, true, RGB(255, 0, 255));
	_loading->loadImage("back.bmp", "images/background/back.bmp", 1816, 776, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//UI로드 입니다
	_loading->loadImage("새로운시작Ui", "images/ui/Ui_newStartScene.bmp", 750, 655, true, RGB(255, 0, 255));
	_loading->loadImage("컨트롤바Back", "images/ui/Ui_controlBarBack.bmp", 255, 4, true, RGB(255, 0, 255));
	_loading->loadImage("컨트롤바Front", "images/ui/Ui_controlBarFront.bmp", 255, 4, true, RGB(255, 0, 255));
	_loading->loadImage("컨트롤버튼", "images/ui/Ui_controlButton.bmp", 16, 20, true, RGB(255, 0, 255));
	_loading->loadImage("okay버튼", "images/ui/Ui_okayButton.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadFrameImage("cancel버튼", "images/ui/Ui_cancelButton.bmp", 26 * 3, 12 * 3, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("UI_아이템정보", "images/ui/Ui_itemInfo.bmp", 295, 431, true, RGB(255, 0, 255));
	_loading->loadImage("UI_아이템정보_행동력", "images/ui/Ui_itemInfo_actting.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("UI_아이템정보_체력", "images/ui/Ui_itemInfo_hp.bmp", 34, 34, true, RGB(255, 0, 255));
	_loading->loadImage("UI_아이템입수", "images/ui/Ui_getItem.bmp", 287, 96, true, RGB(255, 0, 255));
	_loading->loadImage("UI_인벤토리풀", "images/ui/Ui_fullinventory.bmp", 287, 96, true, RGB(255, 0, 255));
	_loading->loadImage("UI_돈없음", "images/ui/Ui_notMoney.bmp", 287, 96, true, RGB(255, 0, 255));
	_loading->loadImage("UI_선택박스", "images/ui/Ui_selectBox.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("UI_선택박스2", "images/ui/Ui_selectBox2.bmp", 768, 48, true, RGB(255, 0, 255));
	_loading->loadImage("UI_하트", "images/ui/Ui_menu_goodFeeling.bmp", 24, 21, true, RGB(255, 0, 255));
	_loading->loadImage("UI_빈하트", "images/ui/Ui_menu_notFeeling.bmp", 24, 21, true, RGB(255, 0, 255));

	_loading->loadFrameImage("화면UI_timer", "images/ui/Ui_timer.bmp", 2070, 183, 9, 1, true, RGB(255, 0, 255));
	_loading->loadImage("화면UI_HpEnergyBar", "images/ui/Ui_Hp_Energy_bar.bmp", 90, 180, true, RGB(255, 0, 255));
	_loading->loadImage("화면UI_HpBar_Front", "images/ui/Ui_hp_energy_bar_front.bmp", 20, 132, true, RGB(255, 0, 255));
	_loading->loadImage("화면UI_EnergyBar_Front", "images/ui/Ui_hp_energy_bar_front.bmp", 20, 132, true, RGB(255, 0, 255));
	_loading->loadImage("화면UI_MainInventory", "images/ui/Ui_mainInventory.bmp", 655, 90, true, RGB(255, 0, 255));

	_loading->loadImage("메뉴창_인벤토리1", "images/ui/Ui_menu_inventory1.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴창_인벤토리2", "images/ui/Ui_menu_inventory2.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴창_인벤토리3", "images/ui/Ui_menu_inventory3.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴창_호감도", "images/ui/Ui_menu_feelingMenu.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴창_미니맵", "images/ui/Ui_menu_mapMenu.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴창_제작", "images/ui/Ui_menu_makingMenu.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴창_나가기", "images/ui/Ui_menu_exit.bmp", 700, 608, true, RGB(255, 0, 255));
	_loading->loadFrameImage("메뉴창_나가기메뉴_타이틀", "images/ui/Ui_menu_titleButton.bmp", 560, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("메뉴창_나가기메뉴_나가기", "images/ui/Ui_menu_exitButton.bmp", 424, 104, 2, 1, true, RGB(255, 0, 255));

	_loading->loadImage("상점UI_상점창", "images/ui/Ui_shop.bmp", 893, 595, true, RGB(255, 0, 255));
	_loading->loadImage("상점UI_상점창휠버튼", "images/ui/Ui_shop_button.bmp", 13, 22, true, RGB(255, 0, 255));
	_loading->loadImage("상점UI_동물상점창", "images/ui/Ui_animalShop.bmp", 500, 420, true, RGB(255, 0, 255));
	_loading->loadImage("상점UI_가방1", "images/ui/Ui_shop_bag1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("상점UI_가방2", "images/ui/Ui_shop_bag2.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("대화UI_대화창", "images/ui/Ui_dialog.bmp", 800, 284, true, RGB(255, 0, 255));
	_loading->loadImage("대화UI_선택", "images/ui/Ui_selectdialog.bmp", 800, 228, true, RGB(255, 0, 255));

	_loading->loadImage("UI_로딩화면", "images/ui/Ui_loadingScene.bmp", 1024, 768, true, RGB(255, 0, 255));
	_loading->loadImage("UI_키설명화면", "images/ui/Ui_keyExplanation.bmp", 800, 558, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//몬스터 로드입니다


	//---------------------------------------------------------------------------------------------
	//오브젝트 로드입니다
	_loading->loadFrameImage("오브젝트_농작물", "images/object/object_crops.bmp", 384, 1536, 8, 16, true, RGB(255, 0, 255));


	//----------------------------------------------------------------------------------------------
	//아이템 로드입니다
	_loading->loadFrameImage("아이템_tool", "images/item/item_tool.bmp", 240, 240, 5, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이템_seed", "images/item/item_seed.bmp", 288, 240, 6, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이템_crops", "images/item/item_crops.bmp", 288, 240, 6, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이템_animalitem", "images/item/item_animalitem.bmp", 112*3, 16*3, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이템_food", "images/item/item_food.bmp", 288, 48, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이템_rock", "images/item/item_rock.bmp", 96, 48, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이템_material", "images/item/item_material.bmp", 144, 48, 3, 1, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//NPC 로드입니다
	_loading->loadFrameImage("캐릭터_에비게일", "images/character/character_abigail.bmp", 64*3, 128*3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("캐릭터_에밀리", "images/character/character_emily.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("캐릭터_레아", "images/character/character_leah.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("캐릭터_마니", "images/character/character_marnie.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("캐릭터_피에르", "images/character/character_pierre.bmp", 64 * 3, 128 * 3, 4, 4, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터_초상화_에비게일", "images/character/character_portrait_abigail.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("캐릭터_초상화_에밀리", "images/character/character_portrait_emily.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("캐릭터_초상화_레아", "images/character/character_portrait_leah.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("캐릭터_초상화_마니", "images/character/character_portrait_marnie.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("캐릭터_초상화_피에르", "images/character/character_portrait_pierre.bmp", 160, 160, true, RGB(255, 255, 0));
	_loading->loadImage("캐릭터_호감도_에비게일", "images/character/character_feeling_abigail.bmp", 64,64, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터_호감도_에밀리", "images/character/character_feeling_emily.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터_호감도_레아", "images/character/character_feeling_leah.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터_호감도_마니", "images/character/character_feeling_marnie.bmp", 64, 64, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터_호감도_피에르", "images/character/character_feeling_pierre.bmp", 64, 64, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//동물 로드입니다
	_loading->loadFrameImage("동물_어린닭", "images/character/animal/animal_babyChicken.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_닭", "images/character/animal/animal_chicken.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_어린오리", "images/character/animal/animal_babyDuck.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_오리", "images/character/animal/animal_duck.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_어린토끼", "images/character/animal/animal_babyRabbit.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_토끼", "images/character/animal/animal_rabbit.bmp", 64 * 3, 128 * 3, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_어린소", "images/character/animal/animal_babyCow.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_소", "images/character/animal/animal_cow.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_어린젖소", "images/character/animal/animal_babyGoat.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_젖소", "images/character/animal/animal_goat.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_어린양", "images/character/animal/animal_babySheep.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_양", "images/character/animal/animal_sheep.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_어린돼지", "images/character/animal/animal_babyPig.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("동물_돼지", "images/character/animal/animal_pig.bmp", 128 * 3, 224 * 3, 4, 7, true, RGB(255, 0, 255));

	//----------------------------------------------------------------------------------------------
	//시작화면 로드입니다

	_loading->loadImage("타이틀배경", "images/title/title_backGround.bmp", WINSIZEX, WINSIZEY * 2, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀이미지1", "images/title/titleImage1.bmp", WINSIZEX, WINSIZEY / 2, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀이미지2", "images/title/titleImage2.bmp", WINSIZEX, WINSIZEY / 2, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀이미지3", "images/title/titleImage3.bmp", WINSIZEX, WINSIZEY / 2, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀구름1", "images/title/title_cloud1.bmp", 123 * 3, 54 * 3, true, RGB(0, 0, 255));
	_loading->loadImage("타이틀구름2", "images/title/title_cloud2.bmp", 64 * 3, 36 * 3, true, RGB(0, 0, 255));
	_loading->loadImage("타이틀구름3", "images/title/title_cloud3.bmp", 480, 344, true, RGB(0, 0, 255));
	_loading->loadImage("타이틀구름4", "images/title/title_cloud4.bmp", 123 * 3, 79 * 3, true, RGB(0, 0, 255));
	_loading->loadFrameImage("타이틀새", "images/title/title_bird.bmp", 104 * 3, 18 * 3, 4, 1, true, RGB(255, 0, 255));

	_loading->loadImage("타이틀", "images/title/title_stardewvalley.bmp", 398 * 2, 187 * 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타이틀시작", "images/title/title_newButton.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타이틀로드", "images/title/title_loadButton.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타이틀맵툴", "images/title/title_coop.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타이틀나가기", "images/title/title_exitButton.bmp", 148 * 2, 58 * 2, 2, 1, true, RGB(255, 0, 255));

	_loading->loadImage("로드화면", "images/title/title_loadSceneImage.bmp", 1024, 768, true, RGB(255, 0, 255));


	//이펙트 로딩입니다
	_loading->loadFrameImage("이펙트_호미질", "images/animation/animation_hoe.bmp", 384, 48, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("이펙트_수확", "images/animation/animation_cropsHarvesting.bmp", 288, 96, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("이펙트_돌제거", "images/animation/animation_rock.bmp", 384, 48, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("이펙트_풀제거", "images/animation/animation_grass.bmp", 336, 48, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("이펙트_물", "images/animation/animation_water.bmp", 480, 48, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("이펙트_나무제거", "images/animation/animation_removeTree.bmp", 2800, 160, 10, 1, true, RGB(255, 0, 255));
}
