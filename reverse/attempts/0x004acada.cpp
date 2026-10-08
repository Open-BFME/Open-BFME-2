// ?rva004ACADA@PartTheHeavensUpdate@@AAEXXZ
// partial score=0.95 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ?rva004ACADA@PartTheHeavensUpdate@@AAEXXZ, retail 0x004ACADA, 217 bytes.
// Private rebuild helper called from update (0x004ACBB3) and loadPostProcess
// (0x004ACBF3). Evidence: LINK BONUS names this mangling; prev/next are
// PartTheHeavensUpdateXfer/Update; callees are rowed isEmpty/set,
// AudioEventRTS ctor/dtor, Curve pin 0x00504BA9, Shadow row 0x00330995,
// g_00DEC2D4 virtual slot 0x10; float literal 2.0f.
#include "ascii_string.h"

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

class Rva00504BA9Curve
{
public:
	float rva00504BA9(float v);
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
	void rva00330995(int v);
	unsigned char m_pad00[8];
	Coord3D m_pos08;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_pos38;
};

class PartTheHeavensUpdateModuleData
{
public:
	void *m_vtable;
	int m_unused04;
	AsciiString m_str08;
	int m_color0C;
	Rva00504BA9Curve m_curve10;
};

class AudioManager0029E159
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3();
	virtual Shadow *createEmitter(int a, AudioEventRTS *b, AudioEventRTS *c);
};

extern AudioManager0029E159 *g_00DEC2D4;

class Thing;
class ModuleData;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
protected:
	const void *m_vtable;
	PartTheHeavensUpdateModuleData *m_moduleData;
	Object *m_object;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	PartTheHeavensUpdate(Thing *thing, const ModuleData *moduleData);
private:
	void rva004ACADA();
	unsigned int m_startFrame;
	Shadow *m_shadow;
};

void PartTheHeavensUpdate::rva004ACADA()
{
	if (m_shadow != 0)
		return;
	PartTheHeavensUpdateModuleData *data = m_moduleData;
	if (((const StringBase<char> &)data->m_str08).isEmpty())
		return;
	AudioEventRTS ev;
	float v = data->m_curve10.rva00504BA9(0.0f);
	((StringBase<char> &)ev.m_first).set((const StringBase<char> &)data->m_str08);
	float v2 = v * 2.0f;
	int type = 0x40;
	ev.m_unknown8 = type;
	ev.m_floatC = v2;
	ev.m_float10 = v2;
	ev.m_float14 = 0.0f;
	ev.m_float18 = 0.0f;
	ev.m_byte25 = 0;
	ev.m_byte26 = 1;
	AudioManager0029E159 *mgr = g_00DEC2D4;
	m_shadow = mgr->createEmitter(type, &ev, &ev);
	if (m_shadow != 0)
	{
		const Coord3D *pos = &m_object->m_pos38;
		Coord3D *dest = &m_shadow->m_pos08;
		*dest = *pos;
		m_shadow->rva00330995(data->m_color0C);
	}
}
