// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/GameEngine/Source/Common /Ireference/shims/bfmelist /Ireference/shims/moduledata
// ?rva003920F7@Rva003920F7@@QAEXIPBURva003920F7Src@@@Z @0x003920F7 50B unlock: if array at +8 null call pinned init 0x00392092 then bounds check index vs TheWritableGlobalData+0xA94 then copy 12B into element stride 0x1C; callers 0x00393468 etc; unblocks 0x0039321C/0x0039380F.

extern class GlobalData *TheWritableGlobalData;

class GlobalData
{
public:
	char m_pad00[0xA68];
	float m_minDistFromEdgeOfMapForBuild; // +0xA68 +0xA68
	float m_supplyBuildBorder; // +0xA6C +0xA6C
	float m_allowedHeightVariationForBuilding; // +0xA70 +0xA70
	char m_padA74[0x20];
	int m_maxLineBuildObjects; // +0xA94 +0xA94
	char m_padA98[0xFC];
	float m_sellPercentage; // +0xB94 +0xB94
	char m_padB98[0x688];
	float m_1220; // +0x1220 +0x1220
};

class Rva00391FC4;
class Rva00392092Target
{
public:
	void rva00392092();
private:
	int m_count00; // +0x00
	char m_pad04[0x4];
	Rva00391FC4 *m_array08; // +0x08
};

struct Rva003920F7Src
{
public:
	int a; // +0x00
	int b; // +0x04
	int c; // +0x08
};


#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
enum ObjectID { INVALID_OBJECT_ID = 0 };
class Rva004D9A3C
{
public:
	Rva004D9A3C();
	~Rva004D9A3C();
public:
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	unsigned char m_byte10;
	AsciiString m_name;										// +0x14
	int m_18;
};
class Rva003920F7
{
public:
	void rva003920F7(UnsignedInt index, const Rva003920F7Src *src);
};
class Rva0039205C : public Rva003920F7
{
public:
	void rva00392129(UnsignedInt index, Real angle);
	void rva0039215F(UnsignedInt index, const AsciiString &name);
	void rva00392196(UnsignedInt index, Int status);
	void rva003921C8(UnsignedInt index, unsigned char value);
	void rva00392CAC();

	union { unsigned count; Int m_count; };         // +0x00
	union { unsigned cost; Int m_cost; };           // +0x04
	Rva004D9A3C *array;                             // +0x08
	union { bool flagC; Bool m_0C; };               // +0x0C
	union { bool flagD; Bool m_0D; };               // +0x0D
	short padE;
	union { int status; Int m_status; };            // +0x10
	ObjectID objectID;                              // +0x14

	Rva0039205C()
	{
		status = -1;
		count = 0;
		array = 0;
		flagC = false;
		flagD = false;
		cost = 0;
		objectID = INVALID_OBJECT_ID;
	}
	~Rva0039205C();
	void *rva00392CC5(unsigned index);
	Rva004D9A3C *rva00392CF9(unsigned index);
	float rva00392D1D(unsigned index);
	unsigned char rva00392D49(unsigned index);
	int rva00392D71(int index);
};

void Rva003920F7::rva003920F7(unsigned int index, const Rva003920F7Src *src)
{
	Rva0039205C *info = static_cast<Rva0039205C *>(this);
	if (info->array == 0)
		((Rva00392092Target *)this)->rva00392092();
	if (index >= TheWritableGlobalData->m_maxLineBuildObjects)
		return;
	*(Rva003920F7Src *)(info->array + index) = *src;
}
