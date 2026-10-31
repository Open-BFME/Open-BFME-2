// cl: /MD /EHs
//
// ??1Rva00383D71@@QAE@XZ @0x00383D71 271B base dtor: 6x Rva0038201D at +0x4,
// two 6x arrays via eh vector destructor at +0x4c/+0x94, 8x Rva0038204A at
// +0xdc. Callees rowed in Rva0046A93EDtor.cpp, arrays use rowed element
// dtors via 0x00629110. Callers 0x003844D7/0x0038454E tail-call as base.
class Rva0038201D
{
public:
	~Rva0038201D();
private:
	void *m_head;
	int m_count;
	int m_extra;
};

class Rva0038204A
{
public:
	~Rva0038204A();
private:
	void *m_head;
	int m_count;
	int m_extra;
};

// The members are map<unsigned char, short> and map<unsigned char, float>.
// Their tree destructors are the rowed 0x0038323E/0x00383276 (the views
// above); each map's own destructor is the 5-byte thunk 0x0038356C/0x00383571
// that the eh vector destructor receives for the two arrays.
namespace _STL
{
	template <class T> struct less {};
	template <class T> class allocator {};
	template <class T1, class T2> struct pair {};
	template <class K, class V, class C, class A> class map;
	template <> class map<unsigned char, short, less<unsigned char>, allocator<pair<const unsigned char, short> > >
	{
		Rva0038201D m_tree;
	};
	template <> class map<unsigned char, float, less<unsigned char>, allocator<pair<const unsigned char, float> > >
	{
		Rva0038204A m_tree;
	};
}
typedef _STL::map<unsigned char, short, _STL::less<unsigned char>, _STL::allocator<_STL::pair<const unsigned char, short> > > Rva0038356CMap;
typedef _STL::map<unsigned char, float, _STL::less<unsigned char>, _STL::allocator<_STL::pair<const unsigned char, float> > > Rva00383571Map;

class Rva00383D71
{
public:
	~Rva00383D71();
private:
	int m_00;
	Rva0038356CMap m_04;
	Rva0038356CMap m_10;
	Rva0038356CMap m_1c;
	Rva0038356CMap m_28;
	Rva0038356CMap m_34;
	Rva0038356CMap m_40;
	Rva0038356CMap m_4c[6];
	Rva0038356CMap m_94[6];
	Rva00383571Map m_dc;
	Rva00383571Map m_e8;
	Rva00383571Map m_f4;
	Rva00383571Map m_100;
	Rva00383571Map m_10c;
	Rva00383571Map m_118;
	Rva00383571Map m_124;
	Rva00383571Map m_130;
	char m_pad[24];
};

Rva00383D71::~Rva00383D71()
{
}
