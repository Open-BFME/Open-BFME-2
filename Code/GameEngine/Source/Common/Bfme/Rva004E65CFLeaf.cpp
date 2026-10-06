// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva004E65CF@Rva004E65CF@@QAEXXZ @0x004E65CF 191B
// Leaf method on the 0x004E669A class (same this, +4/+8/+0xC/+0x1C): builds an
// AudioEventRTS temp from the +4 param-block string, scales the +0xC float by
// 2.0f into two audio floats, plays it through g_00DEC2D4 slot 8 into +0x1C,
// then on success zeroes decal+0x20, applies texture 0xFFFF8000, copies rope
// position into decal+8 and sets +0x64/opacity. Evidence: rowed AudioEventRTS
// ctor 0x00079514 plus StringBase set 0x000366F0 plus dtor 0x000793FA, manager
// at 0x009EC2D4 slot 8, float 2.0f at 0x007C28F4, pins for SetTexture 0x330995
// plus BFMERopeDrawable::getPosition 0x2763E6, rowed Shadow::setOpacity
// 0x3308F6, caller 0x004E6739, neighbours in same Bfme dir.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class AudioEventRTS
{
public:
	AudioEventRTS();
	~AudioEventRTS();
	AsciiString m_first;
	AsciiString m_second;
	int m_unknown8;
	float m_floatC;
	float m_float10;
	float m_float14;
	float m_float18;
	float m_float1C;
	float m_float20;
	unsigned char m_byte24;
	unsigned char m_byte25;
	unsigned char m_byte26;
};

struct Rva004E65CFParams
{
	AsciiString m_sound;
	AsciiString m_font;
	int m_size;
	unsigned char m_bold;
	char m_pad0D[3];
	int m_color;
};

struct Rva004E65CFFloatSrc
{
	char m_pad00[8];
	float m_f08;
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class Shadow
{
public:
	void setOpacity(int value);
};

class Rva00330995
{
public:
	void SetTexture(void *p);
	char m_pad00[8];
	Coord3D m_pos08;
	char m_pad14[12];
	float m_f20;
	char m_pad24[64];
	unsigned char m_b64;
};

class Rva004E65CFMgr
{
public:
	virtual ~Rva004E65CFMgr() {}
	virtual void s04() = 0;
	virtual Rva00330995 *play(AudioEventRTS *ev) = 0;
};

extern Rva004E65CFMgr *g_00DEC2D4;
extern float g_Va00BC28F4;
// g_Va00BC28F4: matched references place it at VA 0xbc28f4 (retail .rdata value 2.0f).
float g_Va00BC28F4 = 2.0f;

class Rva004E65CF
{
	void *m_00;
	Rva004E65CFParams *m_04;
	BFMERopeDrawable *m_08;
	Rva004E65CFFloatSrc *m_0C;
	void *m_10;
	int m_14;
	int m_18;
	Rva00330995 *m_1C;
public:
	void rva004E65CF();
};

void Rva004E65CF::rva004E65CF()
{
	AudioEventRTS ev;
	ev.m_first = m_04->m_sound;
	Rva004E65CFFloatSrc *p = m_0C;
	Rva004E65CFMgr *mgr = g_00DEC2D4;
	ev.m_byte25 = 0;
	ev.m_byte26 = 1;
	ev.m_unknown8 = 0x2000;
	float f = p->m_f08 * g_Va00BC28F4;
	ev.m_float10 = f;
	ev.m_floatC = f;
	m_1C = mgr->play(&ev);
	if (m_1C)
	{
		m_1C->m_f20 = 0.0f;
		m_1C->SetTexture((void *)0xFFFF8000);
		const Coord3D *pos = m_08->getPosition();
		Rva00330995 *decalForDest = m_1C;
		Coord3D *dest = &decalForDest->m_pos08;
		*dest = *pos;
		m_1C->m_b64 = 1;
		((Shadow *)m_1C)->setOpacity(0x80);
	}
}
// ?g_00DEC2D4@@3PAVRva004E65CFMgr@@A: the global at VA 0xdec2d4 is ?g_00DEC2D4@@3PAVAudioManager0029E159@@A.
#pragma comment(linker, "/alternatename:?g_00DEC2D4@@3PAVRva004E65CFMgr@@A=?g_00DEC2D4@@3PAVAudioManager0029E159@@A")
