// ?rva002EAC9F@Rva002EAC9F@@QAEXPAVXfer@@@Z
// partial score=0.96 date=2026-10-04
// cl: /O1 /MD
// ?rva002EAC9F@Rva002EAC9F@@QAEXPAVXfer@@@Z @0x002EAC9F 154B queue of ObjectID xfer with size check
// Evidence: Version1 row 0x000053EE then Xfer slot 0x78 for ints at +0x800/+0x804 then size 0x200 check with Unexpected queue size throw then XferObjectID row 0x003060B2 over slots; callers 0x002F238F 0x002F239B
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
class DamageInfo;
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
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);
struct XferException
{
	char *text;
	int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;
class Rva002EAC9F
{
	ObjectID m_slots[0x200];
	unsigned int m_read;
	unsigned int m_write;
public:
	void rva002EAC9F(Xfer *xfer);
};
// ?rva002EAC9F@Rva002EAC9F@@QAEXPAVXfer@@@Z present-unmatched
void Rva002EAC9F::rva002EAC9F(Xfer *xfer)
{
	xfer->Version1();
	(*xfer == m_read) == m_write;
	unsigned int size = 0x200;
	*xfer == size;
	if (size != 0x200) {
		XferException error;
		bfmeFormatText(&error, 4, "Unexpected queue size");
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
	}
	unsigned int cur = m_read;
	while (cur != m_write) {
		XferObjectID(xfer, &m_slots[cur]);
		int next = (int)cur + 1;
		int d = (int)cur - 0x1FF;
		int mask = d ? -1 : 0;
		cur = (unsigned int)(next & mask);
	}
}
