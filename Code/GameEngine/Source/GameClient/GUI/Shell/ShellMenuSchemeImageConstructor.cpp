// cl: /DNDEBUG /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/Shell /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii_common
// stlport
// ??0ShellMenuSchemeImage@@QAE@XZ, retail 0x002004C3 (58B): Zero Hour's
// ShellMenuScheme.cpp constructor, compiled against the TU's own headers.
//
//   m_position.x = m_position.y = 0;
//
// is a chained assignment, so y at +8 is stored before x at +4, which is
// why retail writes +8, then +4.
//
//   m_size.x = m_size.x = 0;
//
// names x twice. It is a typo in the original, and BFME kept it: m_size.y at
// +0x10 is never written, which is exactly what retail does.
#define Matrix4x4 Matrix4
#include "zh_ascii.h"
#include "PreRTS.h"
#include "Common/INI.h"
#include "GameClient/ShellMenuScheme.h"

ShellMenuSchemeImage::ShellMenuSchemeImage( void )
{
	m_name.clear();
	m_position.x = m_position.y = 0;
	m_size.x = m_size.x = 0;
	m_image = NULL;
}
