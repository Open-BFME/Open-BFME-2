// cl: /MD /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// Ghidra FUN_00814ea1, 00414EA1..00414F27 RET4. The version pair is
// transferred through slot 28, the +1C vector through the 280-byte cdecl
// helper 00414C92, and +2C and the player index through slot 7C.
// ThePlayerList and getPlayerFromMask are established providers. The owner
// and the +1C element identity remain address-derived.
struct Rva00414EA1Version { unsigned char version, current; };
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/Common/Player.h"
#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
struct Rva00414EA1Vector { void *begin, *end, *capacity; };
Xfer *Rva00414C92(Xfer *xfer, Rva00414EA1Vector *values);
// DoXfer is a virtual: slot 3 of vtable 0x00C3A09C, which the ctors 0x004147CF
// and 0x004148C0 store at +0; WorldBuilder's twin is slot 3 of the table its
// twin ctors install.
#include "ScoredKillEvaAnnouncerView.h"
void ScoredKillEvaAnnouncer::DoXfer(Xfer *xfer)
{
    Rva00414EA1Version version = {1, 1};
    (*xfer == reinterpret_cast<Xfer::Version &>(version));
    Rva00414C92(xfer, reinterpret_cast<Rva00414EA1Vector *>(&trackers));
    (*xfer == seenPlayers);
    int playerIndex = localPlayer ? localPlayer->m_playerIndex : -1;
    (*xfer == playerIndex);
    if (xfer->IsLoading())
    {
        if (playerIndex == -1)
            localPlayer = 0;
        else
            localPlayer = ThePlayerList->getPlayerFromMask(1 << playerIndex);
    }
}
