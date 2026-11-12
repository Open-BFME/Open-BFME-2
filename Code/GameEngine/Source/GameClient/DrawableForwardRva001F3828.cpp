// cl: /O1 /DNDEBUG /MD
// ?rva001F3828@Rva001F3828@@QAE_NHH@Z @0x001F3828 34B
//
// ?rva001F3828@Rva001F3828@@QAE_NHH@Z @0x001F3828 34B.
// Guarded forward: asks TheGameClient (global 0x00DFE77C, GameClient view
// per GameLogicBindObjectAndDrawable) slot 0x40 for the +0xB0 key; on null
// returns false, else tail-jumps to the unrowed thiscall at 0x002788C7 on
// the returned object (pinned from the emitted spelling) and returns its
// bool. The two int params are forwarded unchanged to the worker (Drawable
// rva002788C7(int,int)): passing the same stack arguments through is what makes cl 7.1
// emit the tail JMP (a worker call without them is call+ret, 36B).
#include "../../Include/GameClient/GameClientClass.h"
#include "../../Include/GameClient/Drawable.h"

class Rva001F3828
{
public:
	bool rva001F3828(int a, int b);
private:
	char m_pad00[0xB0];
	DrawableID m_drawableID;
};

bool Rva001F3828::rva001F3828(int a, int b)
{
	Drawable *drawable = TheGameClient->findDrawableByID(m_drawableID);
	if (drawable == 0)
		return false;
	return drawable->rva002788C7(a, b);
}
