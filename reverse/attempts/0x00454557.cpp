// ?xfer@GettingBuiltBehavior@@MAEXPAVXfer@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?xfer@GettingBuiltBehavior@@MAEXPAVXfer@@@Z, retail 0x00454557, 551 bytes:
// slot 3 of GettingBuiltBehavior's primary vtable 0x00C404FC (ctor 0x004542FA;
// slot 4 is its pool key 0x004543EB). Version (1, 9) through Xfer slot 0x28,
// the rowed UpdateModule::xfer 0x0044DF9F, then the fields the ctor lays out:
// bools +0x30..+0x33 and the float +0x28, the +0x24 audio handle through
// TheAudio (0x009FE6E8) slot 0x160 as in FoundationAIUpdateXfer.cpp; from
// version 2 the +0x2C count and +0x34; 3: +0x35, +0x36; 4: the +0x38 int;
// 5: +0x3C; 6: the work list at +0x40 (version 6 wrote a list<int> through
// the rowed 0x0036ABAF, read and dropped; from 7 a count then per entry the
// ObjectID via the rowed XferObjectID, its position and float, loaded
// entries appended through push_back 0x00453B06), and within it 8: +0x3D,
// 9: +0x3E. Field names are by offset; the entry type is the Rva004530ED of
// GettingBuiltBehaviorListSlots.cpp, its default ctor inline here as retail
// zeroes the entry in place.
//
// NEAR MISS: all calls, offsets and block order line up; cl here keeps
// `this` in ebx and the counts in a frame slot, where retail keeps `this`
// in edi, the loop register in ebx and both counts (and the version-6
// list<int>) in the dead `xfer` parameter slot [ebp+8].

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase
{
public:
	float x, y, z;
};
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

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual void _pad52() = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	virtual void _pad78() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0;
};

extern AudioManager *TheAudio;

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Coord3D : public Coord3DBase
{
};

class Rva004530ED
{
public:
	Rva004530ED()
	{
		m_id = INVALID_ID;
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
		m_10 = 0.0f;
	}
	Rva004530ED(const Rva004530ED &rhs);
	ObjectID m_id; // +0x00
	Coord3D m_pos; // +0x04
	float m_10; // +0x10
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T> struct _List_node
{
	_List_node *_M_next;
	_List_node *_M_prev;
	T _M_data;
};

template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
	~_List_base();
protected:
	_List_node<T> *m_node;
};

// STLport 4.5.3 list<T>: one pointer to the sentinel node.
template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
public:
	typedef _List_node<T> *iterator;
	list(const A &a = A()) : _List_base<T, A>(a) {}
	iterator begin() const { return this->m_node->_M_next; }
	iterator end() const { return this->m_node; }
	unsigned int size() const
	{
		unsigned int n = 0;
		for (iterator it = begin(); it != end(); it = it->_M_next)
			++n;
		return n;
	}
	void push_back(const T &x);
};
}

Xfer *Rva0036ABAFXfer(Xfer *xfer, _STL::list<int> *values);

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class GettingBuiltBehaviorInterface { public: virtual void interfaceSlot(); };

class GettingBuiltBehavior : public UpdateModule, public GettingBuiltBehaviorInterface
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	AudioHandle m_24; // +0x24
	float m_28; // +0x28
	unsigned int m_2C; // +0x2C
	bool m_30; // +0x30
	bool m_31; // +0x31
	bool m_32; // +0x32
	bool m_33; // +0x33
	bool m_34; // +0x34
	bool m_35; // +0x35
	bool m_36; // +0x36
	int m_38; // +0x38
	bool m_3C; // +0x3C
	bool m_3D; // +0x3D
	bool m_3E; // +0x3E
	_STL::list<Rva004530ED> m_40; // +0x40
};

void GettingBuiltBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 9);
	*xfer == version;
	UpdateModule::xfer(xfer);
	*xfer == m_30;
	*xfer == m_28;
	*xfer == m_31;
	*xfer == m_32;
	*xfer == m_33;
	TheAudio->xferAudioHandle(xfer, &m_24);
	if (version.m_minimum >= 2)
	{
		*xfer == m_2C;
		*xfer == m_34;
	}
	if (version.m_minimum >= 3)
	{
		*xfer == m_35;
		*xfer == m_36;
	}
	if (version.m_minimum >= 4)
		*xfer == m_38;
	if (version.m_minimum >= 5)
		*xfer == m_3C;
	if (version.m_minimum >= 6)
	{
		if (version.m_minimum >= 7)
		{
			if (xfer->IsLoading())
			{
				int count = 0;
				*xfer == count;
				Rva004530ED entry;
				for (int i = 0; i < count; ++i)
				{
					XferObjectID(xfer, &entry.m_id);
					*xfer == entry.m_pos;
					*xfer == entry.m_10;
					m_40.push_back(entry);
				}
			}
			else
			{
				int count = m_40.size();
				*xfer == count;
				for (_STL::list<Rva004530ED>::iterator it = m_40.begin(); it != m_40.end(); it = it->_M_next)
				{
					XferObjectID(xfer, &it->_M_data.m_id);
					*xfer == it->_M_data.m_pos;
					*xfer == it->_M_data.m_10;
				}
			}
		}
		else
		{
			_STL::list<int> dropped;
			Rva0036ABAFXfer(xfer, &dropped);
		}
		if (version.m_minimum >= 8)
			*xfer == m_3D;
		if (version.m_minimum >= 9)
			*xfer == m_3E;
	}
}
