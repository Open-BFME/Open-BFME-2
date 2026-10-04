// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -DBFME_STLP_NODE_ALLOC -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/RTS
// stlport
// ??_EShroudManagerImpl008FBA40Element@@QAEPAXI@Z
// retail 0x003A795A, 75 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp: the donor
// preamble and the element class, whose 0x68-byte layout is what the
// compiler-generated scalar deleting destructor encodes. The donor's other
// definitions are omitted; the delete[] below is the only construct that
// emits ??_E, exactly as the donor's own manager code does.
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

// The donor declares these, which is what makes the array path of the
// compiler-generated vector deleting destructor call operator delete[] rather
// than the scalar operator delete.
void *operator new[](unsigned int bytes);
void operator delete[](void *pointer);

class ShroudManagerImpl008FBA40Node;
class ShroudManagerImpl008FBA40;

struct ShroudManagerImpl008FBA40PlayerState
{
	unsigned short status;
	unsigned short counters[2];
};

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();
	void adjustPlayerCounter008FC1F0(int playerIndex, int counterIndex,
		int amount);
	void updatePlayerCells008FC300(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
	void updatePlayerCells008FC3B0(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
	void updatePlayerCells008FC450(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);

private:
	__forceinline void copyPlayerStatesFrom(
		const ShroudManagerImpl008FBA40Element &other)
	{
		for (int i = 0; i < 16; ++i)
			playerStates[i] = other.playerStates[i];
	}

	ShroudManagerImpl008FBA40Node *cellNodes;
	ShroudManagerImpl008FBA40PlayerState playerStates[16];
	int unknown64;
	friend class ShroudManagerImpl008FBA40;
};

template <class T>
void bfmeForceElementArrayDelete(T *pointer)
{
	delete[] pointer;
}

template void bfmeForceElementArrayDelete<ShroudManagerImpl008FBA40Element>(
	ShroudManagerImpl008FBA40Element *);
