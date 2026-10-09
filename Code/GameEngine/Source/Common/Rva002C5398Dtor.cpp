// cl: /DNDEBUG /MD /EHsc
// ??1Rva002C5398@@UAE@XZ retail 0x002C5398 112B
// Own vptr BFF658; under EH state 1 this object runs the rowed
// ?winDestroyAll@GameWindowManager@@UAEHXZ 0x002C124C and
// ?freeStaticStrings@GameWindowManager@@UAEXXZ 0x00315ACC as qualified
// (non-virtual) calls, then the 0x00DFDC14 singleton theBfmeDfdc14 is deleted
// through its slot-0 deleting dtor with the global ??3@YAXPAX@Z and cleared;
// then the STLport list base at +0x30 (rowed 0x004EC395) and the rowed base
// dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74. Names address-derived.

namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator() {}
	};

	template <class T, class A> class _List_base
	{
	public:
		_List_base(const A &);
		~_List_base();
	private:
		void *m_node;
	};
}

class AudioManager;
extern AudioManager *theBfmeDfdc14;

class Rva002C5398Owned
{
public:
	virtual ~Rva002C5398Owned();
};

class GameWindowManager
{
public:
	virtual int winDestroyAll();
	virtual void freeStaticStrings();
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

class Rva002C5398 : public SubsystemInterface
{
public:
	Rva002C5398();
	virtual ~Rva002C5398();

private:
	int m_field0C;
	int m_field10;
	int m_field14;
	int m_field18;
	int m_field1C;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2C;
	_STL::_List_base<int, _STL::allocator<int> > m_list; // +0x30
	int m_field34;
	int m_field38;
	int m_field3C;
};

// ??0Rva002C5398@@QAE@XZ retail 0x002C5334 100B: base ctor 0x001B4E63, own
// vptr BFF658, list base ctor 0x004EC36C at +0x30, +0x3C = -1, then the
// pointer fields cleared. Its only caller is the derived ctor at 0x0008FC51.
Rva002C5398::Rva002C5398() : m_list(_STL::allocator<int>())
{
	m_field3C = -1;
	m_field0C = 0;
	m_field10 = 0;
	m_field14 = 0;
	m_field18 = 0;
	m_field1C = 0;
	m_field20 = 0;
	m_field24 = 0;
	m_field28 = 0;
	m_field2C = 0;
	m_field34 = 0;
	m_field38 = 0;
}

Rva002C5398::~Rva002C5398()
{
	reinterpret_cast<GameWindowManager *>(this)->GameWindowManager::winDestroyAll();
	reinterpret_cast<GameWindowManager *>(this)->GameWindowManager::freeStaticStrings();
	::delete reinterpret_cast<Rva002C5398Owned *>(theBfmeDfdc14);
	theBfmeDfdc14 = 0;
}
