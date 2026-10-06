// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva002C5398@@UAE@XZ retail 0x002C5398 112B
// Own vptr BFF658; under EH state 1 this object runs the rowed
// ?rva002C124C@Rva002C124C@@UAEHXZ 0x002C124C and
// ?freeStaticStrings@GameWindowManager@@UAEXXZ 0x00315ACC as qualified
// (non-virtual) calls, then the 0x00DFDC14 singleton theBfmeDfdc14 is deleted
// through its slot-0 deleting dtor with the global ??3@YAXPAX@Z and cleared;
// then the STLport list base at +0x30 (rowed 0x004EC395) and the rowed base
// dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74. Names address-derived.

namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class A> class _List_base
	{
	public:
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

class Rva002C124C
{
public:
	virtual int rva002C124C();
};

class GameWindowManager
{
public:
	virtual void freeStaticStrings();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[8];
};

class Rva002C5398 : public GameEngineDeletingBase
{
public:
	virtual ~Rva002C5398();

private:
	char m_pad0C[0x30 - 0x0C];
	_STL::_List_base<int, _STL::allocator<int> > m_list; // +0x30
};

Rva002C5398::~Rva002C5398()
{
	reinterpret_cast<Rva002C124C *>(this)->Rva002C124C::rva002C124C();
	reinterpret_cast<GameWindowManager *>(this)->GameWindowManager::freeStaticStrings();
	::delete reinterpret_cast<Rva002C5398Owned *>(theBfmeDfdc14);
	theBfmeDfdc14 = 0;
}
