// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// ?getCurrentFrameWidth@Anim2D@@QBEIXZ @0x002D6BD2 24B via ZH donor plus /G7, the twin of the
// landed getCurrentFrameHeight TU: the banked attempt's only gap was the xor eax,eax the default
// P6 model emits before mov ax,[ecx+4] (partial-register stall avoidance), which /G7 drops.
// Callee ?getFrame@Anim2DTemplate@@QBEPBVImage@@G@Z rowed in Anim2D.cpp; Image+0x24 width
// proves Width over Height.

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
/** Return the "natural" width of the image for our current frame */
// ------------------------------------------------------------------------------------------------
UnsignedInt Anim2D::getCurrentFrameWidth( void ) const
{
	const Image *currentFrameImage = m_template->getFrame( m_currentFrame );

	if( currentFrameImage )
		return currentFrameImage->getImageWidth();

	return 0;

}  // end getCurrentFrameWidth
