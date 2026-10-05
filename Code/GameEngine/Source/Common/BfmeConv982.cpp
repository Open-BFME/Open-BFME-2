// Open-BFME5 conversions.
// cl: /O1 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv982.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeGo982C 0x000AA87E (48B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

#include "../../../../reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/basetype.h"

class BfmeZ982;

class BfmeY982
{
public:
	virtual void bfmeVY0982();
	virtual void bfmeVY1982();
	virtual void bfmeVY2982();
	virtual void bfmeVY3982();
	virtual void bfmeVY4982();
	virtual void bfmeVY5982();
	virtual BfmeZ982 *bfmeNext982B();

	BfmeY982 *bfmeConv982B();
};

class BfmeSrc982
{
public:
	virtual void bfmeVS0982();
	virtual void bfmeVS1982();
	virtual void bfmeVS2982();
	virtual void bfmeVS3982();
	virtual void bfmeVS4982();
	virtual void bfmeVS5982();
	virtual void bfmeVS6982();
	virtual void bfmeVS7982();
	virtual void bfmeVS8982();
	virtual void bfmeVS9982();
	virtual void bfmeVS10982();
	virtual void bfmeVS11982();
	virtual void bfmeVS12982();
	virtual void bfmeVS13982();
	virtual void bfmeVS14982();
	virtual void bfmeVS15982();
	virtual void bfmeVS16982();
	virtual void bfmeVS17982();
	virtual void bfmeVS18982();
	virtual void bfmeVS19982();
	virtual void bfmeVS20982();
	virtual void bfmeVS21982();
	virtual void bfmeVS22982();
	virtual void bfmeVS23982();
	virtual void bfmeVS24982();
	virtual void bfmeVS25982();
	virtual BfmeY982 *bfmeGet982B(int a);
};

class BfmeOut982
{
public:
	virtual void bfmeVO0982();
	virtual void bfmeVO1982();
	virtual void bfmeVO2982();
	virtual void bfmeVO3982();
	virtual void bfmeVO4982();
	virtual void bfmeVO5982();
	virtual void bfmeVO6982();
	virtual void bfmeVO7982();
	virtual void bfmeVO8982();
	virtual void bfmeVO9982();
	virtual void bfmeVO10982();
	virtual void bfmeVO11982();
	virtual void bfmeVO12982();
	virtual void bfmeVO13982();
	virtual void bfmeVO14982();
	virtual void bfmeVO15982();
	virtual void bfmeVO16982();
	virtual void bfmeVO17982();
	virtual void bfmeSend982B(BfmeZ982 *z);
};

// Retail spells the singleton at 0x012F076C TheScriptEngine; BfmeSrc982 is
// this TU's view of it, so the global carries its real name and the view is
// cast at the use.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
// Retail spells the build-assistant singleton at 0x012ED83C TheBuildAssistant
// (`extern BuildAssistant *TheBuildAssistant`, ZH Common/BuildAssistant.h); this
// TU carries no header that declares it, so the type is forward-declared under
// its defining name and the global keeps it. BfmeOut982 is the local view, cast
// at the use, exactly as TheScriptEngine is above.
class BuildAssistant;
extern BuildAssistant *TheBuildAssistant;


class BfmeT982
{
public:
	void bfmeTouch982C();
};

class BfmeHub982
{
public:
	void bfmeBegin982C();
	void bfmeEnd982C();
};

extern BfmeHub982 *g_bfmeHub982;

void bfmeStep982C(void);

void bfmeGo982C(BfmeT982 *t)
{
	if (!t)
		return;

	bfmeStep982C();

	if (!g_bfmeHub982)
		return;

	g_bfmeHub982->bfmeBegin982C();
	t->bfmeTouch982C();
	g_bfmeHub982->bfmeEnd982C();
}

int __cdecl bfmeHelpWI(int color);

struct Rva007845D0Transform
{
	float m[6];
};

extern Rva007845D0Transform g_Rva00F06914Transform;
extern Rva007845D0Transform g_Rva00F0692CTransform;

class Rva007845D0Backend
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(int a, int b);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(int x, int y);
	virtual void slot38(int x, int y, int a, int b);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(float a, float b);
};


class Rva007845D0
{
public:
	void method(void);

	char m_pad00[8];
	Rva007845D0Backend *m_backend;
	Region2D m_region;
	float m_width;
	float m_height;
	int m_color;
	int m_align;
	bool m_byte2c;
	bool m_byte2d;
	bool m_byte2e;
};

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeHub982@@3PAVBfmeHub982@@A=?g_00DE6170@@3PAVRva0011018B@@A")
