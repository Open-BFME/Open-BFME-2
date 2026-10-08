// cl: /O1 /DNDEBUG /MD /GX
//
// W3DProjectileStreamDraw.cpp: setFullyObscuredByShroud and xfer, which retail
// links from this TU (tu_map approved), folded from two split units with these
// exact flags. Both views had a 0xC-byte base; it is DrawModule here.
//
//
// ?setFullyObscuredByShroud@W3DProjectileStreamDraw@@UAEX_N@Z, retail 0x000D1124, 130 bytes.
// Vslot 35 (offset 0x8C) of vtable 0x007CE010 (class of ??0W3DProjectileStreamDraw@@QAE@PAVThing@@PBVModuleData@@@Z).
// Donor: Zero Hour W3DProjectileStreamDraw::setFullyObscuredByShroud (W3DProjectileStreamDraw.cpp):
// true branch loops m_allLines[0..m_linesValid) calling Peek_Scene (+0x48) then Remove (+0x40);
// false branch loops calling Peek_Scene then W3DDisplay::m_3DScene->Add_Render_Object (+0x8).
// Layout from rowed ctor 0xD1370 (DrawModule base size 0xC, texture +0x0C, 0x14 lines +0x10, count +0x60).
// No direct callees (all virtual); scene global at data 0x009E1B34 via W3DDisplay::m_3DScene.
// ?xfer@W3DProjectileStreamDraw@@MAEXPAVXfer@@@Z @0x000D11A6 44B
// Slot 3 (offset 0x0C) of vtable 0x007CE010 (class of ??0W3DProjectileStreamDraw@@QAE@PAVThing@@PBVModuleData@@@Z).
// Donor: ZH W3DProjectileStreamDraw::xfer (W3DProjectileStreamDraw.cpp: Version(1,1) then DrawModule::xfer, no data).
// Retail: Version(1,1) via Xfer slot 0x28 then base DrawModule::xfer via rowed 0x004CBF58.

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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class DrawModule;

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

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

class SegmentedLineClass;

class SceneClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void Add_Render_Object(SegmentedLineClass *line);
	virtual void Remove_Render_Object(SegmentedLineClass *line);
};

class SegmentedLineClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void Remove();
	virtual void slot17();
	virtual SceneClass *Peek_Scene();
};

// W3DDisplay::m_3DScene is an RTS3DScene (W3DLaserDrawDestructor.cpp defines it).
class RTS3DScene : public SceneClass
{
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class W3DProjectileStreamDraw : public DrawModule
{
public:
	W3DProjectileStreamDraw(Thing *thing, const ModuleData *moduleData);
	virtual void setFullyObscuredByShroud(bool fullyObscured);

protected:
	virtual void xfer(Xfer *xfer);

private:
	void *m_pad0C;
	SegmentedLineClass *m_allLines[0x14];
	int m_linesValid;
};

void W3DProjectileStreamDraw::setFullyObscuredByShroud(bool fullyObscured)
{
	if (fullyObscured) {
		for (int lineIndex = 0; lineIndex < m_linesValid; ++lineIndex) {
			SegmentedLineClass *deadLine = m_allLines[lineIndex];
			if (deadLine && deadLine->Peek_Scene())
				deadLine->Remove();
		}
	} else {
		for (int lineIndex = 0; lineIndex < m_linesValid; ++lineIndex) {
			SegmentedLineClass *deadLine = m_allLines[lineIndex];
			if (deadLine && !deadLine->Peek_Scene())
				W3DDisplay::m_3DScene->Add_Render_Object(deadLine);
		}
	}
}

void W3DProjectileStreamDraw::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	DrawModule::xfer(xfer);
}
