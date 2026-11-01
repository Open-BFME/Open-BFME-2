// cl: /MD
// ?rva002B29BD@LivingWorldLogic@@QAEXXZ, retail 0x002B29BD, 27 bytes.
// Fires HideEndGame UI callback through the global target: invoke with
// owner (void*)13, name "HideEndGame", rest 0. Same recipe as the landed
// UiCallbackFirers. Callers at 0x002B8922 0x002B99F3, both LivingWorldLogic
// members (rva002B88EC, init) that enter it with the logic in ECX: a
// LivingWorldLogic member that does not read its receiver.
#include "../../Include/Common/Rva00222A8BTarget.h"
// The slot at VA 0x00DFE4CC is the Apt window manager pointer, defined as
// g_bfmeAptWindowManager in Rva005832D0MapName.cpp; this TU reads it through
// its own view type.
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class LivingWorldLogic
{
public:
	void rva002B29BD();
};
void LivingWorldLogic::rva002B29BD()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke((void *)13, "HideEndGame", 0, 0, 0, 0, 0, 0);
}
