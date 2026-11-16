// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /G7 /MD /EHsc
// ??1Rva0035615D@@UAE@XZ @0x003561BE 198B
// The destructor vtable and deleting-dtor anchor identify Rva0035615D.
// Target cleanup proves the +0x14/+0x18 references, +0x1c/+0x20 audio
// handles, and +0x24 flag; the constructor neighbor provides the +0x10
// AsciiString and 16-byte base extent. Unknown virtual slots are kept as
// slot-indexed views; no target method names are inferred from their offsets.
#include "ascii_string.h"

#include "../../Include/Common/GameAudio.h"

#include "../../Include/GameClient/Display.h"
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"

#include "GameLogicObjectLookupView.h"

// The canonical GameLogic header pads over the fields read here; they
// are reached through a view of the real TheGameLogic.
struct GameLogicFieldView
{
	unsigned char unknown[0x78];
	unsigned char field78;
};
extern GameLogic *TheGameLogic;

#include "../../Include/GameClient/Shell.h"
extern Shell *TheShell;

#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
#include "../../Include/Common/Rva0036CA00Str.h"
#include "../../Include/Common/Rva002390CBInlines.h"

#include "../../Include/Common/ProgressIndicator.h"

// The load-screen base derives from ProgressIndicator (its constructor 0x00355D4E
// calls the base constructor 0x00355C60), whose slot 1 is pure. LoadScreen.cpp,
// which owns this class's constructor, declares the base the same way, so both
// units emit the same table.
class Rva00355D66 : public ProgressIndicator {
public:
	virtual ~Rva00355D66();
private:
	char m_pad[0x10 - 0x08];
};

class Rva0035615D : public Rva00355D66 {
public:
	virtual ~Rva0035615D();
private:
	AsciiString m_s10;
	Rva0036CA00Str m_s14;
	Rva0036CA00Str m_s18;
	int m_handle1c;
	int m_handle20;
	bool m_flag24;
};

Rva0035615D::~Rva0035615D()
{
	if (m_handle1c != 1) {
		TheAudio->removeAudioEvent(m_handle1c);
		m_handle1c = 1;
	}
	if (m_handle20 != 1) {
		TheAudio->removeAudioEvent(m_handle20);
		m_handle20 = 1;
	}
	((GameLogicFieldView *)TheGameLogic)->field78 = 0;
	TheDisplay->stopMovie();
	((W3DDisplay *)TheDisplay)->rva0025D2F6();
	if (m_flag24)
		TheShell->showShell(true);
}
