// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??1Rva003560ED@@UAE@XZ @0x003560ED (112B)
// Derived dtor of Rva00355D66 clearing TheGameLogic +0x78 then calling
// TheDisplay slot 0x110 plus rowed W3DDisplay::rva0025D2F6 0x0025D2F6 then
// destroying StringBase narrow at +0x14/+0x10 via rowed releaseBuffer
// 0x00036410 then base 0x00355D66. Same recipe as Rva003563A7Dtor.
// Evidence: vtable 0x00814EA4 plus deleting caller 0x0035670B.
// The canonical frozen StringBase replaces the private copy; its switch
// declares the narrow teardown out of line, rowed at 0x00036410
// (StringBaseWideReleaseBuffer.cpp).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

#include "../../Include/GameClient/Display.h"

#include "GameLogicObjectLookupView.h"

// The canonical GameLogic header pads over the fields read here; they
// are reached through a view of the real TheGameLogic.
struct GameLogicFieldView
{
	char m_pad[0x78];
	bool m_flag78;
};

extern GameLogic *TheGameLogic;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"

class Rva00355D66 {
public:
	virtual ~Rva00355D66();
private:
	char m_pad[0x0c];
};

class Rva003560ED : public Rva00355D66 {
public:
	virtual ~Rva003560ED();
private:
	StringBase<char> m_s10;
	StringBase<char> m_s14;
};

Rva003560ED::~Rva003560ED()
{
	((GameLogicFieldView *)TheGameLogic)->m_flag78 = false;
	TheDisplay->stopMovie();
	((W3DDisplay *)TheDisplay)->rva0025D2F6();
}
