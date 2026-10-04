// ?xfer@Rva004DD489@@UAEXPAVXfer@@@Z
// partial score=0.99 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?xfer@Rva004DD489@@UAEXPAVXfer@@@Z @ 0x004DD489 400B
// Slot 3 xfer called by EmotionTrackerUpdate::xfer 0x004B1ECB for entries in m_90; ObjectID at +0x08 via XferObjectID; maps int-int at +0x14 and ushort-int at +0x20.
// ?xfer@Rva004DD489@@UAEXPAVXfer@@@Z present-unmatched
#include <map>
#include <set>
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
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *id);
struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};
class Rva004DD489
{
public:
	virtual void xfer(Xfer *xfer);
private:
	int m_04;
	ObjectID m_08;
	unsigned short m_0C;
	unsigned int m_10;
	_STL::map<int, int> m_14;
	_STL::map<unsigned short, int, Gen_lt_00940b40> m_20;
	unsigned int m_2C;
	unsigned int m_30;
};
void Rva004DD489::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	XferObjectID(xfer, &m_08);
	*xfer == m_0C;
	*xfer == m_10;
	int count = (int)m_14.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		int key = 0;
		unsigned int val = 0;
		for (int i = 0; i < count; ++i) {
			XferObjectID(xfer, (ObjectID*)&key);
			*xfer == val;
			m_14[key] = (int)val;
		}
	} else {
		for (_STL::map<int, int>::iterator it = m_14.begin(); it != m_14.end(); ++it) {
			ObjectID key = (ObjectID)(*it).first;
			unsigned int val = (unsigned int)(*it).second;
			XferObjectID(xfer, &key);
			*xfer == val;
		}
	}
	count = (int)m_20.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		unsigned short key2 = 0;
		unsigned int val2 = 0;
		for (int j = 0; j < count; ++j) {
			*xfer == key2;
			*xfer == val2;
			m_20[key2] = (int)val2;
		}
	} else {
		for (_STL::map<unsigned short, int, Gen_lt_00940b40>::iterator jt = m_20.begin(); jt != m_20.end(); ++jt) {
			unsigned short key2 = (*jt).first;
			unsigned int val2 = (unsigned int)(*jt).second;
			*xfer == key2;
			*xfer == val2;
		}
	}
	*xfer == m_2C;
	*xfer == m_30;
}
