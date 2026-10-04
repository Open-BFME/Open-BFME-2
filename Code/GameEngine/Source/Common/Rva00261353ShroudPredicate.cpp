// cl: /O1 /MD
// BFME1 semantic donor: game/GameEngine/Source/Common/BfmeConv815.cpp,
// revision 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, contains().
// Its synthetic receiver/finder names are not target identities.
// Target: the independent vtable reference at .rdata RVA 0x00807170
// names entry 0x00261353. The complete 21-byte body reads receiver +8,
// passes it to the matched Object::getShroudStatusForPlayer at 0x0028D2A2,
// compares that integer enum result with 1, and returns with RET4.

enum CellShroudStatus
{
    CELLSHROUD_CLEAR,
    CELLSHROUD_FOGGED,
    CELLSHROUD_SHROUDED,
    CELLSHROUD_COUNT
};

// Declaration-only callee view: no Object layout is inferred here.
class Object
{
public:
    CellShroudStatus getShroudStatusForPlayer(int playerIndex) const;
};

struct Rva00261353
{
    unsigned char opaque00[8];
    int playerIndex;
    bool test(Object *object);
};

bool Rva00261353::test(Object *object)
{
    return object->getShroudStatusForPlayer(playerIndex) == CELLSHROUD_FOGGED;
}
