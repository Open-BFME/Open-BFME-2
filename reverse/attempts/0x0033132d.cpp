// ?rva0033132D@Rva0033132D@@QAEXPBUCoord3D@@MPAPAXPAVRadiusDecal@@@Z
// partial score=0.94 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
#include "ascii_string.h"
// ?rva0033132D@Rva0033132D@@QAEXPBUCoord3D@@MPAPAXPAVRadiusDecal@@@Z @0x0033132D 300B: RadiusDecalTemplate::createRadiusDecal shape.
// Evidence: this+0 isEmpty StringBase-D row 0x1E2F, clear row 0x30DBA on arg4, AudioEventRTS ctor row 0x79514 plus dtor row 0x793FA, StringBase set row 0x366F0 x2, manager g_00DEC2D4 slot 8 create, Shadow setOpacity row 0x330995, neighbours RadiusDecal_rva00330F7D /O1.
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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Shadow
{
public:
	void rva00330995(int tex);
	char m_pad0[8];
	float m_posX;
	float m_posY;
	float m_posZ;
	char m_pad14[0xC];
	float m_radius;
};

class RadiusDecal
{
public:
	void clear();
	const void *m_template;
	Shadow *m_object;
	bool m_empty;
};

class DecalManager
{
public:
	virtual void *slot0();
	virtual void *slot1();
	virtual Shadow *create(AudioEventRTS *ev);
};

extern DecalManager *g_00DEC2D4;

// ?rva0033132D@Rva0033132D@@QAEXPBUCoord3D@@MPAPAXPAVRadiusDecal@@@Z present-unmatched
class Rva0033132D
{
public:
	void rva0033132D(const Coord3D *pos, float radius, void **texpp, RadiusDecal *decal);
private:
	AsciiString m_first;
	AsciiString m_second;
	int m_unknown8;
	char m_padC[0x14];
	float m_size20;
	float m_size24;
};

void Rva0033132D::rva0033132D(const Coord3D *pos, float radius, void **texpp, RadiusDecal *decal)
{
	if (((const StringBase<char> &)m_first).isEmpty() == true)
		return;
	if (pos == 0)
		return;
	if (m_size20 == 0.0f)
		return;
	if (m_size24 == 0.0f)
		return;
	decal->clear();
	decal->m_empty = false;
	AudioEventRTS ev;
	ev.m_first.set(m_first);
	ev.m_second.set(m_second);
	ev.m_floatC = m_size24;
	ev.m_float10 = m_size24;
	ev.m_byte25 = 1;
	ev.m_byte26 = 1;
	ev.m_unknown8 = m_unknown8;
	ev.m_float14 = 0.0f;
	ev.m_float18 = 0.0f;
	decal->m_object = g_00DEC2D4->create(&ev);
	if (!decal->m_object)
		return;
	decal->m_object->m_radius = radius;
	decal->m_object->rva00330995((int)(size_t)*texpp);
	Coord3D tmp;
	tmp.z = pos->z;
	tmp.y = pos->y + ev.m_float18;
	tmp.x = pos->x + ev.m_float14;
	*(Coord3D *)&decal->m_object->m_posX = tmp;
	decal->m_template = this;
}
