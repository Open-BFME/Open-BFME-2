// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva00203FA8@ScriptEngine@@QAEXH@Z at retail 0x00203FA8 (39B).
// Clears the object of the first m_namedObjects record (+0x1A120) whose
// object equals the argument, then stops: Zero Hour's named-object loop in
// notifyOfObjectDestruction, whose caller rva00356FAF passes the dead object
// as the int argument. Same ecx-plus-stack-arg callee-cleanup member shape as
// the rowed neighbour setSequentialTimer at 0x00203FCF (ends ret 4).
#include "../../../Include/GameLogic/ScriptEngine.h"
#include "../../../Include/GameLogic/Rva0020A227Element.h"

void ScriptEngine::rva00203FA8(int needle)
{
	Rva0020A227Element *rec = m_namedObjects.begin();
	Rva0020A227Element *end = m_namedObjects.end();
	for (; rec != end; ++rec) {
		if ((Object *)needle == rec->obj) {
			rec->obj = 0;
			break;
		}
	}
}
