// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// BFME1 donor6583b3c1ff21db4a561285717028fdafc780b7db:
// game/GameEngine/Source/GameClient/GUI/Rva00465430AptGameWindowDestructor.cpp.
// Donor supplies the two-base/string teardown structure. Target5126F5/90B
// independently installs C659E8/C659E4 at0/218; releases string270 through
// full133B36410; calls full111B5248D0 on the secondary base and full184B
// GameWindow314A0C on the primary base. The target secondary prefix is58B
// rather than the donor's34B, so its string is270 rather than24C.
// Existing APT screen destructor pins use this ABI spelling; the original
// target class name and fields beyond the consumed prefix remain unproven.
// All three providers are independently full-byte verified. The shared
// BFME2 AsciiString header deliberately supplies target36410 teardown.
class GameWindow {
public: GameWindow(); // call-only default ctor: keep the shared census provider
protected: virtual ~GameWindow();
private: unsigned char unknown[0x218-4];
};
class Rva005248D0 {
public: virtual ~Rva005248D0();
private: unsigned char unknown[0x58-4];
};
#include "ascii_string.h"
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: virtual ~_bfme_AptGameWindow();
private: AsciiString filename270;
};
_bfme_AptGameWindow::~_bfme_AptGameWindow() {}
