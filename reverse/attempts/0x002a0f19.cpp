// ?rva002A0F19@InGameUI@@QAEXPAURva002D752DNode@@PBUICoord2D@@HMM@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002A0F19@InGameUI@@QAEXPAURva002D752DNode@@PBUICoord2D@@HMM@Z
// Retail 0x002A0F19..0x002A1111 (504 bytes). BANKED NEAR MISS (score ~0.99):
// all instructions match; only the dead-parameter-slot packing differs (6
// operands): retail keeps `entry` in [ebp+0xC] (shared with the Anim2D new
// temporary) and the frame / len2 spills in [ebp+8]; this build puts entry in
// [ebp+8], the frame spill in [ebp+0xC] and len2 in [ebp+0x14]. Tried: local
// declaration orders, real ctor (throw()/EH), typed list<Rva0029B132 *>,
// separate push item, named frame local, frame expression forms, WB-style
// `entry || anim` check, ICoord2D delay pair. Vector2 operator[] for both the
// writes and the reads (WB twin shape) is what fixed the Normalize x87 code.
//
// InGameUI.cpp (WB twin 0x00DBEEE0, assert line 7972): spawns a floating
// Anim2D (frame delay random 20..30 at +0x2C/+0x30) and a 0x24-byte record
// (init 0x0029B132) at the screen position, with an end frame of now +
// LOGICFRAMES_PER_SECOND * duration, a random unit direction scaled by
// GlobalData random variables +0xD80/+0xD8C (velocity) and +0xD98, +0xDA4
// rounded into +0x20, advanced by `lead` seconds of velocity, and pushes it
// on the list at +0x8D0 (rowed list<int>::push_front 0x00392076). No retail
// caller or vtable reference remains.
#include <list>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct ICoord2D
{
	Int x, y;
};

class WWMath
{
public:
	static Real Random_Float();
	static Real Random_Float(Real min, Real max) { return (Random_Float() * (max - min)) + min; }
	static Real __fastcall Inv_Sqrt(Real value);
};

class Vector2
{
public:
	Vector2() {}
	Vector2(Real x, Real y) : X(x), Y(y) {}
	Real &operator[](int i) { return (&X)[i]; }
	const Real &operator[](int i) const { return (&X)[i]; }
	Real Length2() const { return X * X + Y * Y; }
	__forceinline void Normalize()
	{
		Real len2 = Length2();
		if (len2 != 0.0f)
		{
			Real oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
		}
	}
	Real X, Y;
};

Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);

class GameClientRandomVariable
{
public:
	Real getValue() const;
private:
	Real m_low, m_high;
	Int m_distributionType;
};

class GlobalData
{
public:
	unsigned char m_pad000[0xD80];
	GameClientRandomVariable m_floatingAnimSpeedX;	// +0xD80
	GameClientRandomVariable m_floatingAnimSpeedY;	// +0xD8C
	GameClientRandomVariable m_floatingAnimD98;	// +0xD98
	GameClientRandomVariable m_floatingAnimDA4;	// +0xDA4
};
extern GlobalData *TheWritableGlobalData;

class GameClient
{
public:
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
	virtual UnsignedInt getFrame();	// slot 31
};
extern GameClient *TheGameClient;

extern int g_Va00DBA4E4; // LOGICFRAMES_PER_SECOND

struct Rva002D752DNode;
class Rva002D752D;
class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;

class Anim2D
{
public:
	Anim2D(Rva002D752DNode *tmpl, Rva002D752D *collection);
	unsigned char m_pad00[0x2C];
	Int m_2C;
	Int m_30;
};

class Rva0029B132
{
public:
	Rva0029B132 *rva0029B132();
	Anim2D *m_anim;		// +0x00
	Real m_x;		// +0x04
	Real m_y;		// +0x08
	UnsignedInt m_endFrame;	// +0x0C
	Int m_10;		// +0x10
	Real m_vx;		// +0x14
	Real m_vy;		// +0x18
	Real m_1C;		// +0x1C
	Int m_20;		// +0x20
};

class InGameUI
{
public:
	void rva002A0F19(Rva002D752DNode *animTemplate, const ICoord2D *pos, Int value, Real durationInSeconds, Real lead);

private:
	unsigned char m_pad000[0x8D0];
	_STL::list<int> m_8D0;	// +0x8D0
};

#define INGAMEUI_FILE "C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\InGameUI.cpp"

void InGameUI::rva002A0F19(Rva002D752DNode *animTemplate, const ICoord2D *pos, Int value, Real durationInSeconds, Real lead)
{
	if (animTemplate == 0)
		return;
	if (pos == 0)
		return;
	if (durationInSeconds <= 0.0f)
		return;

	Anim2D *anim = new Anim2D(animTemplate, reinterpret_cast<Rva002D752D *>(TheAnim2DCollection));
	Int delay = GetGameClientRandomValue(20, 30, INGAMEUI_FILE, 7972);
	anim->m_2C = delay;
	anim->m_30 = delay;

	void *mem = operator new(sizeof(Rva0029B132));
	Rva0029B132 *entry = mem ? static_cast<Rva0029B132 *>(mem)->rva0029B132() : 0;
	if (entry == 0)
		return;

	entry->m_anim = anim;
	entry->m_endFrame = TheGameClient->getFrame() + g_Va00DBA4E4 * durationInSeconds;
	entry->m_10 = value;
	entry->m_x = pos->x;
	entry->m_y = pos->y;
	entry->m_20 = TheWritableGlobalData->m_floatingAnimDA4.getValue() + 0.5f;

	Vector2 dir;
	dir[0] = WWMath::Random_Float(-1.0f, 1.0f);
	dir[1] = WWMath::Random_Float(-1.0f, 1.0f);
	dir.Normalize();

	entry->m_vx = TheWritableGlobalData->m_floatingAnimSpeedX.getValue() * dir[0];
	entry->m_vy = TheWritableGlobalData->m_floatingAnimSpeedY.getValue() * dir[1];
	entry->m_1C = TheWritableGlobalData->m_floatingAnimD98.getValue();
	entry->m_x += entry->m_vx * lead;
	entry->m_y += entry->m_vy * lead;

	m_8D0.push_front(reinterpret_cast<const int &>(entry));
}
