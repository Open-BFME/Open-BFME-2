// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Size-optimised (/O1) instantiation of SimpleVecClass<Vector3>.
//
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "shattersystem.h"
#include "assetmgr.h"
#include "mesh.h"
#include "meshmdl.h"
#include "dynamesh.h"
#include "htree.h"
#include "plane.h"
#include "simplevec.h"
#include "wwstring.h"
#include "vp.h"
#include "meshmatdesc.h"
#include <stdlib.h>
#define SHATTER_DEBUG_LOG_ENABLED	0
#if (SHATTER_DEBUG_LOG_ENABLED)
#define SHATTER_DEBUG_SAY(x)			WWDEBUG_SAY(x)
#else
#define SHATTER_DEBUG_SAY(x)
#endif
#define SHATTER_PATTERN_FORMAT	"ShatterPlanes%d"
#define BPT_FRONT						0x01
#define BPT_BACK						0x02
#define BPT_ON							0x04
#define BPT_BOTH						0x08
#define BPT_EPSILON					0.0001f
#define BPT_COINCIDENCE_EPSILON	0.000001f

template bool SimpleVecClass<Vector3>::Uninitialised_Grow(int);
