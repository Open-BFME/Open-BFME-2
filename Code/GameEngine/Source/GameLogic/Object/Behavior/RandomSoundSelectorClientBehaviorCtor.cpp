// cl: /O1 /DNDEBUG /MD /GX
//
// ??0RandomSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004CBC2B, 124 bytes. Behavior-side ctor over the rowed opaque
// intermediate base 0x252B68 (0x0C: vtable + 8 pad, DrawableModule-derived):
// two-phase +0x0C slot (BE2B78 first via sourced-before address-take,
// C5F368 second) plus vtable C5F378 plus float at +0x10 via
// GetGameClientRandomValueReal(0.0f, 1.0f, file, 0x62) (rowed 0x234111,
// x87 fld1/fldz + fstp, no /arch:SSE) plus conditional int at +0x14 via
// the global holder at 0xDFE77C (slot1F, int return; ScriptEngine_setFrame
// precedent) else zero. The rowed instance factory 0x252D2A (news 0x18)
// is the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

typedef float Real;
Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, int line);

class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);
	~Rva00252B68();

protected:
	const void *m_vtable;
	unsigned char m_pad[0x0C - 4];
};

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)0x00DFE77C)

class RandomSoundSelectorClientBehavior : public Rva00252B68
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_0C;
	float m_10;
	int m_14;
};

// ??0RandomSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x004CBC2B
RandomSoundSelectorClientBehavior::RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData)
	: Rva00252B68(thing, moduleData)
{
	int *slot0C = (int *)&m_0C;
	*slot0C = (int)0x00BE2B78;
	m_vtable = (const void *)0x00C5F378;
	m_0C = (const void *)0x00C5F368;
	m_10 = GetGameClientRandomValueReal(0.0f, 1.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable\\Behavior\\RandomSoundSelectorClientBehavior.cpp", 0x62);
	Rva00DFE77CHolder *holder = TheRva00DFE77C;
	if (holder != 0)
		m_14 = holder->slot1F();
	else
		m_14 = 0;
}
