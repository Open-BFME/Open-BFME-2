// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva004601CC@SpawnBehavior@@UAEXXZ, retail 0x004601CC, 74 bytes.
// Identity: slot 12 of SpawnBehavior's SpawnBehaviorInterface vftable
// (0x008425AC), whose sub-object sits at SpawnBehavior +0x20 (m_replacementTimes
// +0x48 at this +0x28, as in the rowed onSpawnDeath). Each replacement time
// already due (GameLogic frame +0x40 past it) is spent on an orphan reclaim
// through the rowed 0x0045F9D8 and erased (list<int> erase 0x00438539) when
// one is found. The name is address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

// SpawnBehavior's primary bases (UpdateModule) fill +0x00..+0x1F; the
// SpawnBehaviorInterface follows at +0x20, so this override runs on that
// sub-object and reaches the primary members at this -0x20.
class SpawnBehaviorUpdateBase
{
public:
	virtual ~SpawnBehaviorUpdateBase();

private:
	unsigned char m_pad04[0x20 - 0x04];
};

class SpawnBehaviorInterface
{
public:
#define SBI_SLOT(n) virtual void spawnBehaviorInterfaceSlot##n();
	SBI_SLOT(00) SBI_SLOT(01) SBI_SLOT(02) SBI_SLOT(03) SBI_SLOT(04) SBI_SLOT(05)
	SBI_SLOT(06) SBI_SLOT(07) SBI_SLOT(08) SBI_SLOT(09) SBI_SLOT(10) SBI_SLOT(11)
#undef SBI_SLOT
	virtual void rva004601CC() = 0;
};

class SpawnBehavior : public SpawnBehaviorUpdateBase, public SpawnBehaviorInterface
{
public:
	Bool rva0045F9D8();
	virtual void rva004601CC();

private:
	unsigned char m_pad24[0x48 - 0x24];
	_STL::list<Int> m_replacementTimes;
};

// ?rva004601CC@SpawnBehavior@@UAEXXZ
void SpawnBehavior::rva004601CC()
{
	for (_STL::list<Int>::iterator it = m_replacementTimes.begin(); it != m_replacementTimes.end();)
	{
		if (TheGameLogic->getFrame() > *it && rva0045F9D8())
			it = m_replacementTimes.erase(it);
		else
			++it;
	}
}
