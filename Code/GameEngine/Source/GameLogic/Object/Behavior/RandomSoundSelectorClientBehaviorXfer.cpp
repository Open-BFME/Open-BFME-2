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
