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
	CROPSKIND_SUMMER_RADISH,				//��
	CROPSKIND_SUMMER_MELON,
	CROPSKIND_SUMMER_TOMATO,
	CROPSKIND_SUMMER_BLUEBERRY,
	CROPSKIND_SUMMER_HOTPEPPER,				//����
	CROPSKIND_FALL_EGGPLANT,				//����
	CROPSKIND_FALL_PUMPKIN,
	CROPSKIND_FALL_CRANBERRY,
	CROPSKIND_FALL_BOKCHOY,					//û��ä
	CROPSKIND_FALL_YAM,						//��
	CROPSKIND_TREE_CHERRY,
	CROPSKIND_TREE_APRICOT,					//�챸
	CROPSKIND_TREE_ORANGE,
	CROPSKIND_TREE_PEACH,
	CROPSKIND_TREE_POMEGRANATE,				//����
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
	SEEDKIND_SUMMER_RADISH,					//��
	SEEDKIND_SUMMER_MELON,
	SEEDKIND_SUMMER_TOMATO,
	SEEDKIND_SUMMER_BLUEBERRY,
	SEEDKIND_SUMMER_HOTPEPPER,				//����
	SEEDKIND_FALL_EGGPLANT,					//����
	SEEDKIND_FALL_PUMPKIN,
	SEEDKIND_FALL_CRANBERRY,
	SEEDKIND_FALL_BOKCHOY,					//û��ä
	SEEDKIND_FALL_YAM,						//��
	SEEDKIND_TREE_CHERRY,
	SEEDKIND_TREE_APRICOT,					//�챸
	SEEDKIND_TREE_ORANGE,
	SEEDKIND_TREE_PEACH,
	SEEDKIND_TREE_POMEGRANATE,				//����
	SEEDKIND_TREE_APPLE,						
	SEEDKIND_LAWN,
	SEEDKIND_END
};

enum FOODKIND
{
	FOODKIND_NULL=-1,
	FOODKIND_SUGAR,
	FOODKIND_FLOUR,							//�а���
	FOODKIND_RICE,
	FOODKIND_OIL,
	FOODKIND_VINEGAR,						//����
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
	ITEMKIND _itemCategory;						//������ ��з�
	int _itemDivision;							//������ �ߺз�
	int _itemSection;							//������ �Һз�

	string _itemName;							//������ �̸�
	string _itemExplanation;					//������ ����
	int _itemNum;								//������ ����
	image *_itemImg;							//������ �̹���
	POINT _itemImgFrame;						//������ �̹��� ������

	int _sellValue;								//������ �� ��ġ
	int _buyValue;								//������ �� ��ġ
	int _addHp;									//ü�� ȸ�� ��ġ
	int _addActingPower;						//�ൿ�� ȸ�� ��ġ

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

