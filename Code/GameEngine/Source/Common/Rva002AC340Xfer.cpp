// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?xfer@Rva002AC340@@MAEXPAVXfer@@@Z @0x004213FC 171B
// Slot 3 (offset 0x0C) of vtable 0x007FDD6C (class of ??0Rva002AC340@@QAE@XZ):
// xfer with int at +4 and vector at +8. Retail does Version1, count from
// vector size, IsLightCRC/IsStoring branches, per-element xfer plus
// push_back on load. Evidence: vslot lane slot 3; donor TU Rva002AC340Ctor
// same vtable and flags; callees Version1 IsLightCRC IsStoring and
// push_back 0x004DFCB0 all rowed; neighbours share vector idiom.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

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

class Rva002AC340
{
public:
	Rva002AC340();
protected:
	virtual ~Rva002AC340();
	virtual void v1();
	virtual void v2();
	virtual void xfer(Xfer *xfer);
private:
	int m_04;
	_STL::vector<const ModuleData *> m_vec;
};
void Rva002AC340::xfer(Xfer *xfer)
{
	xfer->Version1();
	int count = (int)m_vec.size();
	if (xfer->IsLightCRC()) {
		*xfer == m_04;
		*xfer == count;
		return;
	}
	if (xfer->IsStoring()) {
		*xfer == count;
		for (unsigned i = 0; i < m_vec.size(); ++i)
			*xfer == (int &)m_vec[i];
	} else {
		*xfer == count;
		for (int i = 0; i < count; ++i) {
			const ModuleData *tmp;
			*xfer == (int &)tmp;
			m_vec.push_back(tmp);
		}
	}
}
