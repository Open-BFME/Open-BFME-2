// cl: /O1 /Oy- /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 002EE49B..002EE4DE, 67B, RET28; ECX is not an input.
// Seven stack words: object/footprint handle then two by-value Coord3D records.
// Existing parity test2EBBFB and world-to-cell2E7875 establish the same
// handle/bool/Coord3D call roles as rowed cell resolver2EBC14. Both 8B cell
// outputs feed the rowed ICoord2D equality operator4CAD. Original name unknown.

#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct ICoord2DBase
{
    int x, y;
};
struct ICoord2D : ICoord2DBase
{
    bool operator==(const ICoord2DBase &other) const;
};

bool __cdecl Rva002EBBFBIsOdd(void *object);
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool odd, const Coord3D *position);

bool __stdcall Rva002EE49BSameCell(void *object, Coord3D first, Coord3D second)
{
    bool odd = Rva002EBBFBIsOdd(object);
    ICoord2D firstCell, secondCell;
    return *Rva002E7875WorldToCell(&firstCell, odd, &first)
        == *Rva002E7875WorldToCell(&secondCell, odd, &second);
}
