// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?getUnitDirectionVector3D@Thing@@QBEXAAUCoord3D@@@Z @0x0030A8EE 62B
// Thing::getUnitDirectionVector3D: Zero Hour's body takes the transform's X column
// (Thing+8 is m_transform, so +8/+0x18/+0x28 are rows 0..2 of column 0) and normalizes it.
// Unlock 5: builds Coord3D from this+8/+0x18/+0x28 via movss, block-copies
// to out via 3x movsd, normalizes out via rowed 0x00005A70. Callers UNCLAIMED.
// Evidence: movss/movsd/fstp shape; SSE flags from next Rva0030A92C.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "thing.h"

void Thing::getUnitDirectionVector3D(Coord3D &dir) const
{
    Coord3D tmp;
    tmp.x = m_transform.Row[0].X;
    tmp.y = m_transform.Row[1].X;
    tmp.z = m_transform.Row[2].X;
    dir = tmp;
    dir.Normalize();
}
