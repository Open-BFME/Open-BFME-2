// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv815.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingE63::isValid 0x00453124 (42B),
// BfmeThingD02::contains 0x00261353 (21B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

struct BfmeThing174
{
	unsigned char pad[0x50c];
	int m_val50C;
	int toInt(int dummy);
};


struct BfmeArg171
{
	unsigned char pad[0x10];
	float f10;
};

struct BfmeThing171
{
	unsigned char pad[0x500];
	int m_preAttackDelay;
	int scaleToInt(BfmeArg171 *arg);
};


class BfmeFinderD02
{
public:
	int find(int val);
};

struct BfmeThingD02
{
	unsigned char m_pad[0x8];
	int m_val8;
	bool contains(BfmeFinderD02 *finder);
};

bool BfmeThingD02::contains(BfmeFinderD02 *finder)
{
	return finder->find(m_val8) == 1;
}

class BfmeSub9BB
{
public:
	void doAction();
};

struct BfmeSub4_9BB
{
	unsigned char pad[0xc4];
	char m_flagC4;
};

struct BfmeThing9BB
{
	unsigned char pad[4];
	BfmeSub4_9BB *m_sub4;
	unsigned char pad2[0x34];
	char m_flag3C;
	char m_flag3D;
	void checkAndRun();
};


class BfmeObjEB2
{
public:
	void trigger(int a, int b);
};

class BfmeMgrEB2
{
public:
	BfmeObjEB2* find(int id);
};

class GameLogic;
extern GameLogic *TheGameLogic;

struct BfmeSubEB2
{
	unsigned char m_pad[0x7c];
	int m_id;
};

struct BfmeThingEB2
{
	unsigned char m_pad[0x8];
	BfmeSubEB2 *m_sub;
	void doTrigger();
};


class BfmeSubHelperCAB
{
public:
	int checkState(void *a, void *b, void *c);
};

struct BfmeThingCAB
{
	unsigned char m_pad[0x8];
	BfmeSubHelperCAB *m_helper;
	void *m_argC;
	void *m_attackType;
	bool isMatch(void *param);
};


struct BfmeItemE63
{
	unsigned char pad[0x14];
	void *m_p14;
	unsigned char pad2[0x24 - 0x18];
	char m_flag24;
	bool checkValid();
};

BfmeItemE63* __cdecl bfmeFindItemE63(int id);

struct BfmeThingE63
{
	unsigned char pad[8];
	int m_id;
	bool isValid();
};

bool BfmeThingE63::isValid()
{
	int id = m_id;
	BfmeItemE63 *item = bfmeFindItemE63(id);
	if (item && item->m_p14 && !item->m_flag24 && item->checkValid())
		return true;
	return false;
}
