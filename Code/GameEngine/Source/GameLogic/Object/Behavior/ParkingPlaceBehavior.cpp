// cl: /Ireference/shims/zh_outofline /Ireference/shims/updatemodule_ctor /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// BFME 2 has no ParkingPlaceBehavior module: retail game.dat carries no
// "ParkingPlaceBehavior" module-name string (only the UI label
// "GUI:ParkingPlacesFull"), while other module names such as "SlavedUpdate"
// are there, and the ledger holds no row for any of its methods. The Zero Hour
// port this unit carried (33 unrowed bodies) was a nonmatching
// reconstruction of code retail never had; its non-retail DamageInfo,
// BitFlags and vector<Coord3D> COMDATs kept the unit from linking. Only the
// two vector<RunwayInfo> members rowed here (size at 0x001610A0, operator[] at
// 0x006BD4B0) are retail bodies; the explicit instantiations below emit them.
// They keep Zero Hour's element name until the real element is identified.
// Zero Hour's header declares RunwayInfo private, which an explicit
// instantiation cannot name under cl 7.1, so this unit declares only the
// element (Zero Hour's 36-byte layout, which both bodies' strides confirm).
// BFME 2's AsciiString reaches PreRTS.h here even when the unit builds without this file's /FI flag.
#include "zh_ascii.h"
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <vector>
// BaseType.h's min and max macros would rewrite the unit's _STL::max overload.
#undef min
#undef max

class ParkingPlaceBehavior
{
public:
	struct RunwayInfo
	{
		Coord3D		m_start;
		Coord3D		m_end;
		ObjectID	m_inUseBy;
		ObjectID	m_nextInLineForTakeoff;
		Bool			m_wasInLine;
	};
};

namespace _STL {
template unsigned int vector<ParkingPlaceBehavior::RunwayInfo, allocator<ParkingPlaceBehavior::RunwayInfo> >::size() const;
template ParkingPlaceBehavior::RunwayInfo &vector<ParkingPlaceBehavior::RunwayInfo, allocator<ParkingPlaceBehavior::RunwayInfo> >::operator[](unsigned int);
}
