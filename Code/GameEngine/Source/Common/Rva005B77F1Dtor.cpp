// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva005B77F1@@UAE@XZ @0x005B77F1 151B.
// Outer dtor over vtable 0x873918: clear list +0x14 then delete pointees in list +0xC via 0x005B72E7 plus erase then base GameEngineDeletingBase.
// Evidence: chain from 0x005B72E7 you landed; callers 0x005B7888 deleting dtor; lists via rowed list<int> clear erase base dtor.
#include <list>

void __cdecl operator delete(void *p);

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

// The constructor's existing pin names the same 17-byte SubsystemInterface
// initializer as this recovered provider. Both return the incoming this.
#pragma comment(linker, "/alternatename:??0GameEngineDeletingBase@@QAE@XZ=?baseConstruct@BFME2NativeNetwork@@QAEPAV1@XZ")

class Rva005B72E7
{
public:
	~Rva005B72E7();
};

class Rva005B77F1 : public GameEngineDeletingBase
{
public:
	Rva005B77F1();
	virtual ~Rva005B77F1();
private:
	_STL::list<int, _STL::allocator<int> > m_listC;
	int m_pad10;
	_STL::list<int, _STL::allocator<int> > m_list14;
	int m_at18;
	int m_at1c;
	bool m_at20;
	int m_at24;
	int m_at28;
	int m_at2c;
	int m_at30;
	bool m_at34;
	int m_at38;
	int m_at3c;
	int m_at40;
	int m_at44;
};

// 0x005B776E..0x005B77F1 is the default constructor for the adjacent
// verified destructor: same vtable and list offsets. The GameState drift
// name does not fit these scalar initializers, so retain the address name.
Rva005B77F1::Rva005B77F1()
{
	m_at38 = 0;
	m_at18 = 1;
	m_at1c = 1;
	m_at20 = true;
	m_at24 = m_at28 = m_at2c = -1;
	m_at30 = 2;
	m_at34 = false;
	m_at3c = 10;
	m_at40 = 0;
	m_at44 = 0;
}

Rva005B77F1::~Rva005B77F1()
{
	m_list14.clear();
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_listC.begin(); it != m_listC.end(); )
	{
		Rva005B72E7 *p = (Rva005B72E7 *)(int)*it;
		if (p != 0)
		{
			p->~Rva005B72E7();
			::operator delete(p);
		}
		it = m_listC.erase(it);
	}
}
