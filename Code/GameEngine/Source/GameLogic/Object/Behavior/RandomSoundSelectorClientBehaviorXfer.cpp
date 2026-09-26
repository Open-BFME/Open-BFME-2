// cl: /O1 /DNDEBUG /MD
//
// ?xfer@RandomSoundSelectorClientBehavior@@MAEXPAVXfer@@@Z, retail 0x004CBD7C, 48 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085F378 (same primary as rowed ctor 0x004CBC2B):
// base ObjectModule xfer via rowed 0x00560AE1, then Version1 via rowed 0x000053EE,
// then float at +0x10 via Xfer slot 0x70 plus uint at +0x14 via Xfer slot 0x78.
// Layout is the rowed 0x18-byte class (opaque Rva00252B68 base 0x0C plus secondary
// vptr at +0x0C giving +0x10 start; factory 0x00252D2A news 0x18 is sole caller of
// the ctor); donor is BFME1 RandomSoundSelectorClientBehavior (float m_randomSelection
// plus uint m_lastFrame) which reroll 0x004CBCF2 and getSelectedValue 0x004CBD44 prove.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

typedef float Real;
Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, int line);

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

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad[0x1DD];
	bool m_rerollOnEveryFrame;
};

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SoundSelectorSecondary
{
public:
	virtual void secondarySlot();
};

class RandomSoundSelectorClientBehavior : public ObjectModule, public SoundSelectorSecondary
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void reroll();

	float m_randomSelection;
	unsigned int m_lastFrame;
};

void RandomSoundSelectorClientBehavior::xfer(Xfer *xfer)
{
	ObjectModule::xfer(xfer);
	xfer->Version1();
	*xfer == m_randomSelection;
	*xfer == m_lastFrame;
}

void RandomSoundSelectorClientBehavior::reroll()
{
	RandomSoundSelectorClientBehaviorModuleDataView *moduleData =
		(RandomSoundSelectorClientBehaviorModuleDataView *)m_moduleData;
	if (!moduleData->m_rerollOnEveryFrame)
		return;
	Rva00DFE77CHolder *holder = TheRva00DFE77C;
	if (holder == 0)
		return;
	if (holder->slot1F() == (int)m_lastFrame)
		return;
	m_randomSelection = GetGameClientRandomValueReal(
		0.0f,
		1.0f,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable\\Behavior\\RandomSoundSelectorClientBehavior.cpp",
		0x74);
	m_lastFrame = TheRva00DFE77C->slot1F();
}
