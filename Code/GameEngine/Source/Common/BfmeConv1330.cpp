// cl: /O1
// stlport
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv1330.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGoUDC 0x000F6476 (26B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME5 conversions.

// The lookup below is GameLogic::findObjectByID; GameLogicObjectLookup.h holds
// the declaration (its body stays in Thing/GameLogicFindObjectByID.cpp).
#include "../../../../reference/open-bfme-1/game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"

class BfmeSrcUDB
{
public:
	float bfmeCallUDB(int a, int b);
};

extern BfmeSrcUDB *g_bfmeObjUDB;
extern const float g_rva01075350;


class BfmeSrcUDC
{
public:
	void bfmeCloseUDC();
};

extern BfmeSrcUDC *g_bfmeObjUDC;

int bfmeGoUDC(void)
{
	if (g_bfmeObjUDC) {
		g_bfmeObjUDC->bfmeCloseUDC();
		g_bfmeObjUDC = 0;
	}
	return 1;
}

class BfmeSubUDD
{
public:
	void *bfmeFindUDD(int key);
};

class BfmeMgrUDD
{
public:
	char m_bfmePad[0x28];
	BfmeSubUDD *m_bfmeSub;
};

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
// BfmeMgrUDD above is this TU's own view of that address, so the read casts.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern char g_bfmeDefaultUDD[];

class BfmeThingUDD
{
public:
	void *bfmeGoUDD();
	char m_bfmePad[0x2c];
	int m_bfmeKey;
};


class BfmeRecUDE
{
public:
	virtual void bfmeV0UDE() = 0;
	virtual void bfmeV1UDE() = 0;
	virtual void bfmeV2UDE() = 0;
	virtual void bfmeV3UDE() = 0;
	virtual void bfmeV4UDE() = 0;
	virtual void bfmeV5UDE() = 0;
	virtual void bfmeV6UDE() = 0;
	virtual void bfmeV7UDE() = 0;
	virtual void bfmeV8UDE() = 0;
	virtual void bfmeV9UDE() = 0;
	virtual void *bfmeGetUDE() = 0;
};

// Retail's global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once
// in game/GameEngine/Source/GameLogic/System/GameLogic.cpp; Thing/GameLogicObjectLookup.h
// above already declares the real GameLogic view this TU calls through.
extern GameLogic *TheGameLogic;

class BfmeThingUDE
{
public:
	void *bfmeGoUDE();
	char m_bfmePad[0x60];
	int m_bfmeKey;
};

