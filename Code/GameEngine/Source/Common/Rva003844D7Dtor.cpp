// cl: /MD /EHs
// ??1Rva003844D7@@QAE@XZ @0x003844D7 119B derived dtor: 5 members at
// +0x154/+0x160/+0x16c/+0x178/+0x184 via rowed 0x00383276/0x0038323E/0x003832AE
// then base ??1Rva00383D71 at +0 rowed in Rva00383D71Dtor.cpp. Callers
// 0x0038535F 0x0038539E unclaimed thiscall. No vptr store so non-virtual QAE.
class Rva0038201D
{
public:
	~Rva0038201D();
private:
	char m_pad[12];
};

class Rva0038204A
{
public:
	~Rva0038204A();
private:
	char m_pad[12];
};

class Rva00382077
{
public:
	~Rva00382077();
private:
	char m_pad[12];
};

// The members are map<unsigned char, T> (T = int, short, float). Their tree
// destructors are the rowed 0x003832AE/0x0038323E/0x00383276 (the views
// above); each map's own destructor is the 5-byte thunk the unwind funclets
// jump to (0x00383567/0x0038356C/0x00383571), and the normal path expands it.
namespace _STL
{
	template <class T> struct less {};
	template <class T> class allocator {};
	template <class T1, class T2> struct pair {};
	template <class K, class V, class C, class A> class map;
	template <> class map<unsigned char, int, less<unsigned char>, allocator<pair<const unsigned char, int> > >
	{
		Rva00382077 m_tree;
	};
	template <> class map<unsigned char, short, less<unsigned char>, allocator<pair<const unsigned char, short> > >
	{
		Rva0038201D m_tree;
	};
	template <> class map<unsigned char, float, less<unsigned char>, allocator<pair<const unsigned char, float> > >
	{
		Rva0038204A m_tree;
	};
}
typedef _STL::map<unsigned char, int, _STL::less<unsigned char>, _STL::allocator<_STL::pair<const unsigned char, int> > > Rva00383567Map;
typedef _STL::map<unsigned char, short, _STL::less<unsigned char>, _STL::allocator<_STL::pair<const unsigned char, short> > > Rva0038356CMap;
typedef _STL::map<unsigned char, float, _STL::less<unsigned char>, _STL::allocator<_STL::pair<const unsigned char, float> > > Rva00383571Map;

class Rva00383D71
{
public:
	~Rva00383D71();
private:
	char m_pad[0x154];
};

class Rva003844D7 : public Rva00383D71
{
public:
	~Rva003844D7();
private:
	Rva00383567Map m_154;
	Rva0038356CMap m_160;
	Rva0038356CMap m_16c;
	Rva00383571Map m_178;
	Rva00383571Map m_184;
};

class Rva0038454E : public Rva00383D71
{
public:
	~Rva0038454E();
private:
	Rva00383571Map m_154;
	Rva00383571Map m_160;
	Rva00383571Map m_16c;
	Rva00383571Map m_178;
	Rva00383571Map m_184;
	Rva00383571Map m_190;
	Rva00383571Map m_19c;
	Rva00383571Map m_1a8;
	Rva0038356CMap m_1b4;
	Rva0038356CMap m_1c0;
	Rva00383571Map m_1cc;
	Rva00383571Map m_1d8;
	Rva00383571Map m_1e4;
	Rva00383571Map m_1f0;
	Rva00383571Map m_1fc;
};

Rva003844D7::~Rva003844D7()
{
}

Rva0038454E::~Rva0038454E()
{
}
