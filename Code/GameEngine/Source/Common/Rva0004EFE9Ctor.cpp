// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// stlport46
//
// ??0Rva004EFE9@@QAE@PAURva0004F7F4Owner@@U?$_List_iterator@PAVSnapshot@@U?$_Nonconst_traits@PAVSnapshot@@@_STL@@@_STL@@PBD@Z
// retail 0x0004EF5D..0x0004EFE9 (140 bytes, EH, RET 0xC): the constructor of
// the snapshot whose destructor 0x0004EFE9, scalar deleting destructor
// 0x0004F7D8 and slot 1 0x0004F7F4 are rowed (Rva0004EFE9Dtor.cpp); its one
// caller is 0x0004F8A6. Target evidence: the rowed base constructor
// Rva002D76A6 0x002D76A6, the table 0x00BC4DDC, the owner at +0x0C and its
// snapshot-list position at +0x10 (the node's value is set to this), three
// zeroed reals at +0x14 and the +0x20 radar event reference, assigned from
// theRadarWindowOverrideSource's rowed 0x002D508B for the name (rowed
// RadarEventRefSlot::operator= 0x0004E490; the temporary dies through the
// rowed RadarEventRef::release). The destructor unit spells the base by its
// destructor; names are address-derived.

class RadarEventRef
{
public:
	void release();
};

class RadarEventRefSlot
{
public:
	RadarEventRefSlot() : m_ref(0) {}
	~RadarEventRefSlot()
	{
		if (m_ref)
			m_ref->release();
	}
	RadarEventRefSlot &operator=(const RadarEventRefSlot &other);
private:
	RadarEventRef *m_ref;
};

class RadarWindowOverrideSource
{
public:
	RadarEventRefSlot rva002D508B(const char *name);
};
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

// The owner's +0x1500 snapshot list (Rva0004EFE9Dtor.cpp): a node is
// {next, prev, value}.
class Snapshot;
namespace _STL
{
	template <class T> struct _Nonconst_traits {};
	template <class T> struct _List_node
	{
		_List_node *_M_next;
		_List_node *_M_prev;
		T _M_data;
	};
	template <class T, class Traits> struct _List_iterator
	{
		_List_iterator(const _List_iterator &x) : _M_node(x._M_node) {}
		T &operator*() const { return _M_node->_M_data; }
		_List_node<T> *_M_node;
	};
}
typedef _STL::_List_iterator<Snapshot *, _STL::_Nonconst_traits<Snapshot *> > Rva0004EFE9Position;
struct Rva0004F7F4Owner;

class Rva002D76A6
{
public:
	Rva002D76A6();
	virtual ~Rva002D76A6();
private:
	int m_04;
	int m_08;
};

class Rva004EFE9 : public Rva002D76A6
{
public:
	Rva004EFE9(Rva0004F7F4Owner *owner, Rva0004EFE9Position position, const char *name);
	virtual ~Rva004EFE9();
	virtual void rva0004F7F4();			// table 0x00BC4DDC slot 1 (Rva0004EFE9Dtor.cpp)
private:
	Rva0004F7F4Owner *m_owner;			// +0x0C
	Rva0004EFE9Position m_position;			// +0x10
	float m_14;					// +0x14
	float m_18;
	float m_1C;
	RadarEventRefSlot m_reference;			// +0x20
};

Rva004EFE9::Rva004EFE9(Rva0004F7F4Owner *owner, Rva0004EFE9Position position, const char *name)
	: m_owner(owner), m_position(position), m_14(0.0f), m_18(0.0f), m_1C(0.0f)
{
	*position = (Snapshot *)this;
	m_reference = theRadarWindowOverrideSource->rva002D508B(name);
}
