// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// ?getUnitDirectionVector2D@Thing@@QBEPBUCoord3D@@XZ @0x0030A25F 67B.
//
// Thing::getUnitDirectionVector2D cached 2D direction. Donor BFME1
// Code/GameEngine/Source/Common/Thing/Thing.cpp:186 and ZH GeneralsMD
// Code/GameEngine/Source/Common/Thing/Thing.cpp:100 share the body.
// Callees Cos 0x0002FBC0 and Sin 0x0002FBB0 rowed. Caller void overload
// 0x0030A2A2 plus 40plus callers. Layout from donor Thing.h matches retail
// angle +0x44 dirVector +0x48 flags +0x5c.
#include "PreRTS.h"
#include "Common/Thing.h"
#include "Lib/Trig.h"
const Coord3D* Thing::getUnitDirectionVector2D() const
{
	if (!(m_cacheFlags & VALID_DIRVECTOR))
	{
		Real angle = getOrientation();
		m_cachedDirVector.x = Cos(angle);
		m_cachedDirVector.y = Sin(angle);
		m_cachedDirVector.z = 0;
		m_cacheFlags |= VALID_DIRVECTOR;
	}
	return &m_cachedDirVector;
}
