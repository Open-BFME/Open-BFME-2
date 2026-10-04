// ??1Rva006609D0@@UAE@XZ, retail 0x0054FFA5, 156 bytes. Dedicated TU ported
// from the Open-BFME-1 donor
// game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva006609D0Destructor.cpp
// (reference/open-bfme-1). The donor body does not place at BFME 1's flags;
// compiled /Os it is byte-identical to retail once relocations are masked
// (unique hit on unclaimed .text). Only the placed body is defined here; the
// donor's other definitions are omitted.
//
// Open-BFME7: the destructor at 0x006609D0 (BFME 1 retail 197 B) of a
// 0xB4-byte network results object: after a clearing member call (retail
// 0x0054FC14) the members unwind in reverse -- the owning holder of a mutex
// lock at +0xB0 (its inline destructor is the eighth EH state) -- a
// GameResultsCounter at +0xA8, a red-black tree at +0x74, two deques at +0x44
// and +0x1C and three GameResultsCounters at +0x14, +0x0C and +0x04 -- and the
// base vtable is restored.  Member types are opaque address-derived shells
// sized from the offsets with out-of-line destructors.
//
// 6 callee pins read off retail's REL32 displacements, over only four distinct
// target addresses because retail folds them:
//  0x0054FC14 clearing member call (matched ?rva0054FC14);
//  0x0009990D lock-holder destructor (matched ?clear@Rva0009990D);
//  0x00613A20 counter destructor, reached from +0x04 +0x0C +0x14 and +0xA8
//      (matched ??1MutexClass);
//  0x0038A48B tree destructor (matched STLport string-pair Rb_tree dtor);
//  0x0054FF17 deque destructor, reached from both +0x1C and +0x44, body
//      unrowed.
// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/Thread

class GameResultsCounter
{
public:
	~GameResultsCounter();

private:
	char m_body[ 8 ];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};
};

struct Rva00660470Deque
{
	~Rva00660470Deque();
	char m_body[ 0x28 ];
};

struct Rva00660610Deque
{
	~Rva00660610Deque();
	char m_body[ 0x28 ];
};

struct Rva0064C290Tree
{
	~Rva0064C290Tree();
	char m_body[ 0x0C ];
};

struct Rva006609D0LockHolder
{
	~Rva006609D0LockHolder()
	{
		if( m_lock )
			delete m_lock;
	}

	MutexClass::LockClass *m_lock;
};

class Rva006609D0Base
{
public:
	virtual ~Rva006609D0Base() {}
};

class Rva006609D0 : public Rva006609D0Base
{
public:
	virtual ~Rva006609D0();

private:
	void bfmeClearVHX( void );

	GameResultsCounter m_counter04;
	GameResultsCounter m_counter0C;
	GameResultsCounter m_counter14;
	Rva00660470Deque m_deque1C;
	Rva00660610Deque m_deque44;
	char m_unreconstructed6C[ 8 ];
	Rva0064C290Tree m_tree74;
	char m_unreconstructed80[ 0xA8 - 0x80 ];
	GameResultsCounter m_counterA8;
	Rva006609D0LockHolder m_lockB0;
};

// ??1Rva006609D0@@UAE@XZ
Rva006609D0::~Rva006609D0()
{
	bfmeClearVHX();
}
