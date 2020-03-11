#pragma once

enum ITEMKIND
{
	ITEMKIND_NULL,
	ITEMKIND_EQUIPMENT,
	ITEMKIND_TOOL,
	ITEMKIND_CROPS,
	ITEMKIND_SEED,
	ITEMKIND_FOOD,
	ITEMKIND_CRAFTABLE,
	ITEMKIND_ROCK,
	ITEMKIND_MATERIAL,
	ITEMKIND_ANIMALITEM,
	ITEMKIND_END
};
enum EQUIPMENTKIND
{
	EQUIPMENTKIND_NULL,
	EQUIPMENTKIND_WEAPON,
	EQUIPMENTKIND_HAT,
	EQUIPMENTKIND_RING,
	EQUIPMENTKIND_SHOES,
	EQUIPMENTKIND_END
};
enum TOOLKIND
{
	TOOLKIND_NULL,
	TOOLKIND_AXE,
	TOOLKIND_PICKAXE,
	TOOLKIND_HOE,
	TOOLKIND_WATERINGCAN,
	TOOLKIND_SCYTHE,
	TOOLKIND_END
};
enum CROPSKIND
{
	CROPSKIND_NULL=-1,
	CROPSKIND_SPRING_PARSNIP,
	CROPSKIND_SPRING_GREENBEAN,
	CROPSKIND_SPRING_CAULIFLOWER,
	CROPSKIND_SPRING_POTATO,
	CROPSKIND_SPRING_KALE,
	CROPSKIND_SUMMER_RADISH,				//무
	CROPSKIND_SUMMER_MELON,
	CROPSKIND_SUMMER_TOMATO,
	CROPSKIND_SUMMER_BLUEBERRY,
	CROPSKIND_SUMMER_HOTPEPPER,				//고추
	CROPSKIND_FALL_EGGPLANT,				//가지
	CROPSKIND_FALL_PUMPKIN,
	CROPSKIND_FALL_CRANBERRY,
	CROPSKIND_FALL_BOKCHOY,					//청경채
	CROPSKIND_FALL_YAM,						//마
	CROPSKIND_TREE_CHERRY,
	CROPSKIND_TREE_APRICOT,					//살구
	CROPSKIND_TREE_ORANGE,
	CROPSKIND_TREE_PEACH,
	CROPSKIND_TREE_POMEGRANATE,				//석류
	CROPSKIND_TREE_APPLE,
	CROPSKIND_LAWN,
	CROPSKIND_END
};

enum SEEDKIND
{
	SEEDKIND_NULL=-1,
	SEEDKIND_SPRING_PARSNIP,
	SEEDKIND_SPRING_GREENBEAN,
	SEEDKIND_SPRING_CAULIFLOWER,
	SEEDKIND_SPRING_POTATO,
	SEEDKIND_SPRING_KALE,
	SEEDKIND_SUMMER_RADISH,					//무
	SEEDKIND_SUMMER_MELON,
	SEEDKIND_SUMMER_TOMATO,
	SEEDKIND_SUMMER_BLUEBERRY,
	SEEDKIND_SUMMER_HOTPEPPER,				//고추
	SEEDKIND_FALL_EGGPLANT,					//가지
	SEEDKIND_FALL_PUMPKIN,
	SEEDKIND_FALL_CRANBERRY,
	SEEDKIND_FALL_BOKCHOY,					//청경채
	SEEDKIND_FALL_YAM,						//마
	SEEDKIND_TREE_CHERRY,
	SEEDKIND_TREE_APRICOT,					//살구
	SEEDKIND_TREE_ORANGE,
	SEEDKIND_TREE_PEACH,
	SEEDKIND_TREE_POMEGRANATE,				//석류
	SEEDKIND_TREE_APPLE,						
	SEEDKIND_LAWN,
	SEEDKIND_END
};

enum FOODKIND
{
	FOODKIND_NULL=-1,
	FOODKIND_SUGAR,
	FOODKIND_FLOUR,							//밀가루
	FOODKIND_RICE,
	FOODKIND_OIL,
	FOODKIND_VINEGAR,						//식초
	FOODKIND_END
};
enum CRAFRABLEKIND
{
	CRAFTABLEKIND_NULL=-1,
	CRAFTABLEKIND_END
};
enum ROCKKIND
{
	ROCKKIND_NULL=-1,
	ROCKKIND_STONE,
	ROCKKIND_XHAMSTER,
	ROCKKIND_END
};
enum ANIMALITEMKIND
{
	ANIMALITEMKIND_NULL=-1,
	ANIMALITEMKIND_EGG,
	ANIMALITEMKIND_MILK,
	ANIMALITEMKIND_GOATMILK,
	ANIMALITEMKIND_DUCKEGG,
	ANIMALITEMKIND_WOOL,
	ANIMALITEMKIND_TRUFFLE,
	ANIMALITEMKIND_RABBITFOOT,
	ANIMALITEMKIND_END
};
enum MATERIALKIND
{
	MATERIALKIND_NULL = -1,
	MATERIALKIND_WOOD,
	MATERIALKIND_BIGWOOD,
	MATERIALKIND_FIBER,
	MATERIALKIND_END
};


class item
{
protected:
	ITEMKIND _itemCategory;						//아이템 대분류
	int _itemDivision;							//아이템 중분류
	int _itemSection;							//아이템 소분류

	string _itemName;							//아이템 이름
	string _itemExplanation;					//아이템 설명
	int _itemNum;								//아이템 갯수
	image *_itemImg;							//아이템 이미지
	POINT _itemImgFrame;						//아이템 이미지 프레임

	int _sellValue;								//아이템 팔 가치
	int _buyValue;								//아이템 살 가치
	int _addHp;									//체력 회복 수치
	int _addActingPower;						//행동력 회복 수치

public:
	item();
	~item();

	virtual void init(int itemS0ection) { return; };
	void render(HDC hdc, int x, int y);
	void informationRender(HDC hdc, int x, int y);
	void getItmeRender(HDC hdc, int x, int y);
	string itemCategoryPrint(int itemDivision);

	ITEMKIND getItemCategory() { return _itemCategory; };
	int getItemDivision() { return _itemDivision; };
	int getItemSection() { return _itemSection; };

	string getItemName() { return _itemName; };
	string getItemExplanation() { return _itemExplanation; };
	int getItemNum() { return _itemNum; };
	image *getItemImg() { return _itemImg; };
	POINT getItemImageFrame() { return _itemImgFrame; };
	int getSellValue() { return _sellValue; };
	int getBuyValue() { return _buyValue; };
	int getAddHp() { return _addHp; };
	int getAddActingPower() { return _addActingPower; };

	void setItemCategory(ITEMKIND category) { _itemCategory = category; };
	void setItemDivision(int division) { _itemDivision = division; };
	void setItemSection(int section) { _itemSection = section; };

	void setItemName(string name) { _itemName = name; };
	void setItemExplanation(string explanation) { _itemExplanation = explanation; };
	void setItemNum(int num) { _itemNum = num; };
	void setItemImg(image *img) { _itemImg = img; };
	void setItemImageFrame(POINT frame) { _itemImgFrame = frame; };
	void setSellValue(int value) { _sellValue = value; };
	void setBuyValue(int value) { _buyValue = value; };
	void setAddHp(int hp) { _addHp = hp; };
	void setAddActingPower(int actingpower) { _addActingPower= actingpower; };
};

