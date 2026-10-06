// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// ?getCurrentFrameHeight@Anim2D@@QBEIXZ @0x002D6BEA 24B via ZH donor plus /G7 (packet 002D6xxx unlock; callers at 0x002737B1 0x00273A9D 0x002D6DDE; callee ?getFrame@Anim2DTemplate@@QBEPBVImage@@G@Z rowed in Anim2D.cpp; Image+0x28 height proves Height over Width)

#define ANIM2D_INLINE_SNAPSHOT_DTOR
#include "PreRTS.h"
#define DEFINE_ANIM_2D_MODE_NAMES
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Anim2D.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/Image.h"
#include "GameLogic/GameLogic.h"

// ------------------------------------------------------------------------------------------------
/** Return the "natural" height of the image for our current frame */
// ------------------------------------------------------------------------------------------------
UnsignedInt Anim2D::getCurrentFrameHeight( void ) const
{
	const Image *currentFrameImage = m_template->getFrame( m_currentFrame );

	if( currentFrameImage )
		return currentFrameImage->getImageHeight();

	return 0;

}  // end getCurrentFrameHeight
