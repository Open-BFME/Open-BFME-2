// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?xfer@SiegeEngineContain@@MAEXPAVXfer@@@Z, retail 0x0047C322, 464 bytes.
// Slot 3 of ??_7SiegeEngineContain 0x00C470F8 (slot 0 the rowed ??_G
// 0x0047C2D6). The rowed TransportContain::xfer 0x00466DBC first, then the
// light-CRC out and Version(1,1). The rider list at +0x11C: saving writes
// the count kept at +0x120 and each rider's ObjectID (Object+0x74);
// loading first destroys any riders still listed (rowed list<int>::erase
// 0x00438539, GameLogic::destroyObject 0x00242C09, list clear 0x0023DAA5),
// then reads the count and queues the ids in the list at +0x134 (rowed
// push_back 0x0005548F). Then the bool at +0x124 and the map<int,int> at
// +0x128 as ObjectID/int pairs (rowed operator[] 0x0028932C on load).
// Layout per the rowed SiegeEngineContainDtor view; member names not
// recovered.

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

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

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class TransportContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x11C - 0x04];
};

class SiegeEngineContain : public TransportContain
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	_STL::list<int> m_11C;
	unsigned int m_120;
	bool m_124;
	_STL::map<int, int> m_128;
	_STL::list<int> m_134;
};

// ?xfer@SiegeEngineContain@@MAEXPAVXfer@@@Z @0x0047C322
void SiegeEngineContain::xfer(Xfer *xfer)
{
	TransportContain::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	ObjectID id;
	if (xfer->IsStoring())
	{
		*xfer == m_120;
		for (_STL::list<int>::iterator it = m_11C.begin(); it != m_11C.end(); ++it)
		{
			id = ((Object *)*it)->getID();
			XferObjectID(xfer, &id);
		}
	}
	else
	{
		if (!m_11C.empty())
		{
			m_120 = 0;
			for (_STL::list<int>::iterator it = m_11C.begin(); it != m_11C.end(); )
			{
				Object *rider = (Object *)*it;
				it = m_11C.erase(it);
				TheGameLogic->destroyObject(rider);
			}
			m_11C.clear();
		}
		*xfer == m_120;
		for (unsigned int i = 0; i < m_120; ++i)
		{
			XferObjectID(xfer, &id);
			m_134.push_back(reinterpret_cast<const int &>(id));
		}
	}

	*xfer == m_124;

	if (xfer->IsStoring())
	{
		int count = m_128.size();
		*xfer == count;
		for (_STL::map<int, int>::iterator it = m_128.begin(); it != m_128.end(); ++it)
		{
			ObjectID key = (ObjectID)it->first;
			int value = it->second;
			XferObjectID(xfer, &key);
			*xfer == value;
		}
	}
	else
	{
		int count;
		*xfer == count;
		for (int i = 0; i < count; ++i)
		{
			ObjectID key;
			int value;
			XferObjectID(xfer, &key);
			*xfer == value;
			m_128[reinterpret_cast<const int &>(key)] = value;
		}
	}
}
