// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?xfer@EmotionTrackerUpdate@@MAEXPAVXfer@@@Z, retail 0x004B1ECB, 444 bytes.
// Slot 3 of ??_7EmotionTrackerUpdate 0x00C5667C (slot-2 name getter returns
// "EmotionTrackerUpdate"; the rowed dtor 0x004B1322 installs it). The rowed
// UpdateModule::xfer 0x0044DF9F, Version(1,2), twelve (bool, uint, ObjectID)
// triples from the parallel arrays at +0x24/+0x30/+0x60, each element of the
// pointer vector at +0x90 through its pinned xfer 0x004DD489 (remembering
// the index of the one at +0x9C when saving into +0xC4), ints at +0xC4 and
// +0xA0, before version 2 the ObjectID set at +0xA4 (rowed set<int>::insert
// on load), four raw bytes at +0xB0, an int at +0xB4, an ObjectID at +0xB8
// and from version 2 a uint at +0xBC and a bool at +0xC0. Member names not
// recovered.

#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
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

class Rva004DD489
{
public:
	void xfer(Xfer *xfer);
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	char m_unrecovered04[0x24 - 0x04];
};

class EmotionTrackerUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	enum { SLOT_COUNT = 12 };
	bool m_24[SLOT_COUNT];
	unsigned int m_30[SLOT_COUNT];
	ObjectID m_60[SLOT_COUNT];
	_STL::vector<Rva004DD489 *> m_90;
	Rva004DD489 *m_9C;
	int m_A0;
	_STL::set<int> m_A4;
	int m_B0;
	int m_B4;
	ObjectID m_B8;
	unsigned int m_BC;
	bool m_C0;
	int m_C4;
};

// ?xfer@EmotionTrackerUpdate@@MAEXPAVXfer@@@Z @0x004B1ECB
void EmotionTrackerUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	Xfer::Version version(1, 2);
	*xfer == version;

	for (int i = 0; i < SLOT_COUNT; ++i)
	{
		*xfer == m_24[i];
		*xfer == m_30[i];
		XferObjectID(xfer, &m_60[i]);
	}

	m_C4 = -1;
	int count = m_90.size();
	for (int j = 0; j < count; ++j)
	{
		Rva004DD489 *entry = m_90[j];
		if (xfer->IsStoring() && entry == m_9C)
			m_C4 = j;
		entry->xfer(xfer);
	}

	*xfer == m_C4;
	*xfer == m_A0;

	if (version.m_minimum < 2)
	{
		int size = m_A4.size();
		*xfer == size;
		if (xfer->IsLoading())
		{
			ObjectID id = INVALID_ID;
			for (int k = 0; k < size; ++k)
			{
				XferObjectID(xfer, &id);
				m_A4.insert(reinterpret_cast<const int &>(id));
			}
		}
		else
		{
			for (_STL::set<int>::iterator it = m_A4.begin(); it != m_A4.end(); ++it)
			{
				ObjectID id = (ObjectID)*it;
				XferObjectID(xfer, &id);
			}
		}
	}

	xfer->XferRawBytes(&m_B0, sizeof(m_B0));
	*xfer == m_B4;
	XferObjectID(xfer, &m_B8);

	if (version.m_minimum >= 2)
	{
		*xfer == m_BC;
		*xfer == m_C0;
	}
}
