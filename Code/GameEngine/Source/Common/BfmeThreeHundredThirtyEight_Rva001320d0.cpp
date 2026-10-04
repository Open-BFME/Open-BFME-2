// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?bfmeBaseSJ@BfmeThingSJ@@QAEXH@Z is the donor's name for this ctor
// ??0BfmeThingSJ@@QAE@H@Z
// retail 0x001320D0, 89 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BfmeThreeHundredThirtyEight.cpp: the donor
// preamble and this one constructor, the donor's other definition omitted.
extern "C" unsigned char bfmeVftSJ[];

#include "wwstring.h"

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
};

class BfmeThingSJ : public GenBase009EB7D0
{
public:
	__declspec(noinline) void bfmeBaseSJ(int what);
	BfmeThingSJ(int what);
	virtual void handle();
	BfmeThingSJ *bfmeDropSJ(int what);
	int m_bfme14;
	StringClass m_bfmeName;
	Gen_00920A20 m_bfmeData;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
};

BfmeThingSJ::BfmeThingSJ(int what)
	: GenBase009EB7D0(),
	  m_bfme14(0),
	  m_bfmeName((const char *)(unsigned int)what, false),
	  m_bfmeData(0),
	  m_bfme30(0),
	  m_bfme34(0),
	  m_bfme38(0)
{
}
