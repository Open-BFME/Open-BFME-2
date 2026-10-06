// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?interpolateColorForHeight@W3DRadar@@IAEXPAURGBColor@@MMMM@Z @0x0004E1A8 338B via ZH donor W3DRadar.cpp callers at 0x0004FAFF
// stlport
#include "Common/AudioEventRTS.h"
#include "Common/Debug.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/Color.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Image.h"
#include "GameClient/Line2D.h"
#include "GameClient/TerrainVisual.h"
#include "GameClient/Water.h"
#include "W3DDevice/Common/W3DRadar.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameClient/W3DShroud.h"
#include "WW3D2/Texture.h"
#include "WW3D2/DX8Caps.h"
void W3DRadar::interpolateColorForHeight(RGBColor *color, Real height, Real hiZ, Real midZ, Real loZ)
{
	const Real howBright = 0.95f;
	const Real howDark = 0.60f;
	if (hiZ == midZ)
		hiZ = midZ + 0.1f;
	if (midZ == loZ)
		loZ = midZ - 0.1f;
	if (hiZ == loZ)
		hiZ = loZ + 0.2f;
	Real t;
	RGBColor colorTarget;
	if (height >= midZ)
	{
		t = (height - midZ) / (hiZ - midZ);
		colorTarget.red = color->red + (1.0f - color->red) * howBright;
		colorTarget.green = color->green + (1.0f - color->green) * howBright;
		colorTarget.blue = color->blue + (1.0f - color->blue) * howBright;
	}
	else
	{
		t = (midZ - height) / (midZ - loZ);
		colorTarget.red = color->red + (0.0f - color->red) * howDark;
		colorTarget.green = color->green + (0.0f - color->green) * howDark;
		colorTarget.blue = color->blue + (0.0f - color->blue) * howDark;
	}
	color->red = color->red + (colorTarget.red - color->red) * t;
	color->green = color->green + (colorTarget.green - color->green) * t;
	color->blue = color->blue + (colorTarget.blue - color->blue) * t;
	if (color->red < 0.0f)
		color->red = 0.0f;
	if (color->red > 1.0f)
		color->red = 1.0f;
	if (color->green < 0.0f)
		color->green = 0.0f;
	if (color->green > 1.0f)
		color->green = 1.0f;
	if (color->blue < 0.0f)
		color->blue = 0.0f;
	if (color->blue > 1.0f)
		color->blue = 1.0f;
}
