// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?rva0021193B@Rva0021193B@@QAEXUICoord2D@@@Z
// Retail 0x0021193B..0x00211C68 (813 bytes, ret 8, EH frame for the
// sound event temporary). Element lists are STLport-shaped vectors whose
// operator[] is spelled as STLport's *(begin() + n): that inline begin()
// call is what makes cl evaluate the rva003FBA0E receiver before the
// argument pushes (into ecx while eax still holds fadeOut) as retail does.
//
// Identity unknown (no retail caller or vtable reference; WB twin 0x00B62350
// carries only vector2.h asserts), hence the placeholder owner/name; the
// parameter may equally be two Ints (same code). A ring burst: for each of
// m_150 rings (1, 2, 4... elements) it places the next element of the +0x240
// list at the screen point (jittered by a random unit direction times the
// ring radius, m_154 / rings per ring) projected to the terrain through
// g_00DFEF18 slot 14, unhides it, clears its emissive colour, gives it start
// / fade-in / hold / fade-out frames (ring delay m_158 / rings, randomised
// 0.8..1, 0.2..0.35, 0.4..0.6, 0.85..1) through rowed 0x003FBA0E, plays the
// +0x15C sound there; the first element instead gets m_14C * 1.2 at +0x98.
// Then every element of the +0x234 list is unhidden, +0x98 reset from +0x9C
// and restarted through rowed 0x003FB9C8(m_158, 0); finally g_00DFE1E4 slot
// 17. The WB twin's Vector2 shape (operator[] writes and reads, *=,
// Random_Float(min, max)) is followed.
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

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
	Real &operator[](int i) { return (&X)[i]; }
	const Real &operator[](int i) const { return (&X)[i]; }
	Vector2 &operator*=(Real k) { X *= k; Y *= k; return *this; }
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

class RenderObjClass
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49)
	SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59)
	SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69)
	SLOT(70) SLOT(71) SLOT(72) SLOT(73) SLOT(74) SLOT(75) SLOT(76) SLOT(77) SLOT(78) SLOT(79)
	SLOT(80) SLOT(81) SLOT(82) SLOT(83) SLOT(84) SLOT(85) SLOT(86) SLOT(87) SLOT(88) SLOT(89)
	SLOT(90) SLOT(91) SLOT(92) SLOT(93) SLOT(94) SLOT(95) SLOT(96) SLOT(97) SLOT(98) SLOT(99)
	SLOT(100)
#undef SLOT
	virtual void Set_Hidden(Int onoff);	// +0x194
};

bool Rva0010E676_SetEmissive(RenderObjClass *object, float red, float green, float blue);

// One burst element (the 0x0021193B owner's +0x234 / +0x240 lists).
class Rva003FBA0E
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06();
	virtual void setPosition(const Coord3D *pos);	// +0x1C
	void rva003FBA0E(int a, int b, int c, int d, int e, float f);

	RenderObjClass *getRenderObject() const { return m_renderObject; }

	unsigned char m_pad04[0x08 - 0x04];
	RenderObjClass *m_renderObject;	// +0x08
	unsigned char m_pad0C[0x98 - 0x0C];
	Real m_98;			// +0x98
	Real m_9C;			// +0x9C
};

class Rva003FB9C8
{
public:
	void rva003FB9C8(int a, int b);
};

template <class T> class BurstVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T *begin() { return m_start; }
	T &operator[](UnsignedInt n) { return *(begin() + n); }

private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};

class Rva002D3627Host
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual void screenToTerrain(const ICoord2D *screen, Coord3D *world);	// +0x38
};
extern Rva002D3627Host *g_00DFEF18;

class Rva0027070CGlobal
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void slot17();	// +0x44
};
extern Rva0027070CGlobal *g_00DFE1E4;

class AudioManager
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
#undef SLOT
	virtual UnsignedInt addAudioEvent(const BfmeAudioEventPrefix136 *event);	// +0x64
};
extern AudioManager *TheAudio;

class Rva0021193B
{
public:
	void rva0021193B(ICoord2D pos);

private:
	unsigned char m_pad000[0x14c];
	Real m_14C;					// +0x14C
	Int m_ringCount;				// +0x150
	Int m_radius;					// +0x154
	Int m_frames;					// +0x158
	OpaqueRefElement4 m_sound;			// +0x15C
	unsigned char m_pad160[0x234 - 0x160];
	BurstVectorView<Rva003FBA0E *> m_234;		// +0x234
	BurstVectorView<Rva003FBA0E *> m_240;		// +0x240
};

void Rva0021193B::rva0021193B(ICoord2D pos)
{
	Int rings = m_ringCount;
	if (rings > 0)
	{
		Coord3D world;
		Int framesPerRing = m_frames / rings;
		Int radiusPerRing = m_radius / rings;
		Int radius = 0;
		Int delay = 0;
		Int index = 0;
		Int count = 1;
		for (Int ring = 0; ring < rings; ++ring, count *= 2)
		{
			for (Int j = 0; j < count; ++j, ++index)
			{
				ICoord2D screen = pos;
				Int startFrame = delay;
				if (index > 0)
				{
					Vector2 dir;
					dir[0] = WWMath::Random_Float(-1.0f, 1.0f);
					dir[1] = WWMath::Random_Float(-1.0f, 1.0f);
					dir.Normalize();
					dir *= (Real)radius;
					screen.x += (Int)dir[0];
					screen.y += (Int)dir[1];
					startFrame = (Int)(WWMath::Random_Float(0.8f, 1.0f) * delay);
				}
				else
				{
					m_240[index]->m_98 = 1.2f * m_14C;
				}
				g_00DFEF18->screenToTerrain(&screen, &world);
				m_240[index]->setPosition(&world);
				m_240[index]->getRenderObject()->Set_Hidden(0);
				Rva0010E676_SetEmissive(m_240[index]->getRenderObject(), 0.0f, 0.0f, 0.0f);
				Int fadeIn = startFrame + (Int)(WWMath::Random_Float(0.2f, 0.35f) * framesPerRing);
				Int hold = startFrame + (Int)(WWMath::Random_Float(0.4f, 0.6f) * framesPerRing);
				Int fadeOut = startFrame + (Int)(WWMath::Random_Float(0.85f, 1.0f) * framesPerRing);
				m_240[index]->rva003FBA0E(startFrame, fadeIn, hold, fadeOut, 0, 0.0f);
				if (m_sound.referent != 0 && TheAudio != 0)
				{
					BfmeAudioEventPrefix136 sound(m_sound, *(const BfmeEventPositionView *)&world, 1);
					TheAudio->addAudioEvent(&sound);
				}
			}
			radius += radiusPerRing;
			delay += framesPerRing;
		}

		for (UnsignedInt i = 0; i < m_234.size(); ++i)
		{
			m_234[i]->getRenderObject()->Set_Hidden(0);
			m_234[i]->m_98 = m_234[i]->m_9C;
			((Rva003FB9C8 *)m_234[i])->rva003FB9C8(m_frames, 0);
		}
	}
	g_00DFE1E4->slot17();
}
