// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME 1 donor 6583b3c1ff21db4a561285717028fdafc780b7db:
// game/GameEngine/Source/GameClient/GUI/GameWindowManager_winFindFont.cpp.
// Target identity: GameWindowManager vtable RVA 0x007C7C90 slot 76 is
// VA 0x00714CC1, following the matched winTextLabelToText at slot 75.
// Target 80B body converts the integer size to float, calls the matched
// FontLibrary::getFont at 0x002189E1 and destroys the by-value AsciiString.
// Use the existing BFME 2 callee declaration and canonical string ABI.
// This TU declares only the callable method, not the manager's full vtable.
#include "ascii_string.h"
class GameFont;
class FontLibrary
{
public:
    GameFont *getFont(const AsciiString *name, float size, bool bold);
};
extern FontLibrary *TheFontLibrary;
class GameWindowManager
{
public:
    GameFont *winFindFont(AsciiString fontName, int pointSize, bool bold);
};
GameFont *GameWindowManager::winFindFont(AsciiString fontName, int pointSize, bool bold)
{
    if (TheFontLibrary)
        return TheFontLibrary->getFont(&fontName, (float)pointSize, bold);
    return 0;
}
