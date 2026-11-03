// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Draw_Sentence@Render2DSentenceClass@@QAEXK@Z, retail 0x00104D97 (16 bytes,
// RET 4): BFME 2's one-colour Draw_Sentence, which forwards its colour to all
// four corners of the four-colour overload (pinned 0x00155B00, the 2187-byte
// body W3DDisplayString::draw calls). The copy sits among the W3D GameClient
// bodies rather than in render2dsentence.cpp's run, the placement of a header
// inline emitted out of line by a W3D unit; Zero Hour's out-of-line
// one-colour body (kept unmatched in render2dsentence.cpp) is not in retail.
// No retail caller of this copy was found. View of only the two overloads.
typedef unsigned long uint32;

#include "../../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

void Render2DSentenceClass::Draw_Sentence(uint32 color)
{
	Draw_Sentence(color, color, color, color);
}
