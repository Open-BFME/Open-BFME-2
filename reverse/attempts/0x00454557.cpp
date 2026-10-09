// ?xfer@GettingBuiltBehavior@@MAEXPAVXfer@@@Z
// partial score=0.95 date=2026-10-09
// ?xfer@GettingBuiltBehavior@@MAEXPAVXfer@@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00454557, 551B: GettingBuiltBehavior::xfer.
// Version (1, 9) through Xfer slot 0x28, the UpdateModule base xfer
// (0x0044DF9F), then the members in retail order: bool +0x30, float +0x28,
// bools +0x31/+0x32/+0x33, the audio handle +0x24 through TheAudio slot 0x160;
// v2 uint +0x2C and bool +0x34; v3 bools +0x35/+0x36; v4 int +0x38; v5 bool
// +0x3C; v6 a discarded int list (Rva0036ABAFXfer 0x0036ABAF) or, from v7, the
// work list at +0x40 (count, then each entry's object id, Coord3D and float;
// loads push_back through 0x00453B06); v8 bool +0x3D; v9 bool +0x3E.
// The Xfer view and its MSVC-grouped operator== slots follow the matched
// AutoHealBehaviorXfer.cpp (slot 0x28 Version, 0x60 Coord3D, 0x70 float,
// 0x78 unsigned int, 0x7C int, 0x90 bool). The work-list layout follows the
// matched destructor 0x0045448F (list at +0x40, 20-byte entries).

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

void XferObjectID( Xfer *xfer, ObjectID *value );

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

typedef unsigned int AudioHandle;

class AudioManager
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void xferAudioHandle( Xfer *xfer, AudioHandle *handle );
};

extern AudioManager *TheAudio;

// GettingBuiltBehavior work-list entry (20 bytes; copy ctor 0x004530ED).
class Rva004530ED
{
public:
	ObjectID m_id;
	Coord3DBase m_pos;
	float m_value;
};

namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator() {}
	};

	template <class T, class Alloc> class _List_base
	{
	public:
		_List_base( const Alloc &a );
		~_List_base();
		void *m_node;
	};

	template <class T, class Alloc = allocator<T> > class list : public _List_base<T, Alloc>
	{
	public:
		list() : _List_base<T, Alloc>( Alloc() ) {}
		void push_back( const T &value );
	};
}

Xfer *Rva0036ABAFXfer( Xfer *xfer, _STL::list<int, _STL::allocator<int> > *list );

struct GettingBuiltWorkNode
{
	GettingBuiltWorkNode *m_next;
	GettingBuiltWorkNode *m_prev;
	Rva004530ED m_value;
};

struct GettingBuiltWorkList
{
	int size() const
	{
		int n = 0;
		for( const GettingBuiltWorkNode *it = m_node->m_next; it != m_node; it = it->m_next )
			++n;
		return n;
	}
	GettingBuiltWorkNode *m_node;
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer( Xfer *xfer );
private:
	unsigned char m_pad[0x20];
};

class GettingBuiltBehavior : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AudioHandle m_audio24;
	float m_f28;
	unsigned int m_x2C;
	bool m_b30;
	bool m_b31;
	bool m_b32;
	bool m_b33;
	bool m_b34;
	bool m_b35;
	bool m_b36;
	int m_x38;
	bool m_b3C;
	bool m_b3D;
	bool m_b3E;
	GettingBuiltWorkList m_workList;
};

void GettingBuiltBehavior::xfer( Xfer *xfer )
{
	Xfer::Version version( 1, 9 );
	*xfer == version;

	UpdateModule::xfer( xfer );

	*xfer == m_b30;
	*xfer == m_f28;
	*xfer == m_b31;
	*xfer == m_b32;
	*xfer == m_b33;
	TheAudio->xferAudioHandle( xfer, &m_audio24 );

	if( version.m_minimum >= 2 )
	{
		*xfer == m_x2C;
		*xfer == m_b34;
	}

	if( version.m_minimum >= 3 )
	{
		*xfer == m_b35;
		*xfer == m_b36;
	}

	if( version.m_minimum >= 4 )
		*xfer == m_x38;

	if( version.m_minimum >= 5 )
		*xfer == m_b3C;

	if( version.m_minimum >= 6 )
	{
		if( version.m_minimum >= 7 )
		{
			if( xfer->IsLoading() )
			{
				int count = 0;
				*xfer == count;
				Rva004530ED entry;
				entry.m_id = INVALID_ID;
				entry.m_pos.x = 0.0f;
				entry.m_pos.y = 0.0f;
				entry.m_pos.z = 0.0f;
				entry.m_value = 0.0f;
				for( int i = 0; i < count; ++i )
				{
					XferObjectID( xfer, &entry.m_id );
					*xfer == entry.m_pos;
					*xfer == entry.m_value;
					((_STL::list<Rva004530ED, _STL::allocator<Rva004530ED> > *)&m_workList)->push_back( entry );
				}
			}
			else
			{
				int count = m_workList.size();
				*xfer == count;
				for( GettingBuiltWorkNode *node = m_workList.m_node->m_next; node != m_workList.m_node; node = node->m_next )
				{
					XferObjectID( xfer, &node->m_value.m_id );
					*xfer == node->m_value.m_pos;
					*xfer == node->m_value.m_value;
				}
			}
		}
		else
		{
			_STL::list<int, _STL::allocator<int> > unused;
			Rva0036ABAFXfer( xfer, &unused );
		}
	}

	if( version.m_minimum >= 8 )
		*xfer == m_b3D;

	if( version.m_minimum >= 9 )
		*xfer == m_b3E;
}
