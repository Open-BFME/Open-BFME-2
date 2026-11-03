// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// readable body of ?Add_Outline@Render2DClass@@: Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp

// BFME emits the three-argument outline overload directly instead of routing
// it through the UV overload found in the Zero Hour source.  The four line
// endpoints and their one-pixel bias are otherwise the original Render2D
// implementation.

typedef unsigned long uint32;

#include "../../../../../reference/shims/wwmath/Vector2.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h
#include "../WWMath/RectClass.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
#include "Render2DClass.h"

// ?Add_Outline@Render2DClass@@QAEXABVRectClass@@MK@Z
void Render2DClass::Add_Outline(const RectClass &rect, float width, uint32 color)
{
	Add_Line(Vector2(rect.Left + 1, rect.Bottom),
		Vector2(rect.Left + 1, rect.Top + 1), width, color);
	Add_Line(Vector2(rect.Left, rect.Top + 1),
		Vector2(rect.Right - 1, rect.Top + 1), width, color);
	Add_Line(Vector2(rect.Right, rect.Top),
		Vector2(rect.Right, rect.Bottom - 1), width, color);
	Add_Line(Vector2(rect.Right, rect.Bottom),
		Vector2(rect.Left + 1, rect.Bottom), width, color);
}
