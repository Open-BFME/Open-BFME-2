// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003C8C6EDo@ScriptActions@@QAEXABVAsciiString@@@Z @0x003C8C6E (95B).
// Unit evacuate via lookupUnitByValue plus kind flag 0x108/0x80 plus AI
// evacuate plus contain slot 0xA8. Evidence: callees rowed lookup 0x00358752
// aiEvacuate 0x002AE6B3, caller 0x003CC173. Precedent doNamedExitAll.
#include "ascii_string.h"

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class Object;
#include "../../../Include/GameLogic/Module/AIUpdate.h"

struct ObjectKind
{
	char m_pad[0x108];
	unsigned char m_flags;
};

template <int N> class ContainSlots : public ContainSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class ContainSlots<0>
{
};

class ContainModule : public ContainSlots<42>
{
public:
	virtual void slot42(int x) = 0;
};

class Object
{
public:
	virtual ~Object();
	void *m_04;
	char m_pad04[0x250 - 0x08];
	ContainModule *m_contain;
	char m_pad254[4];
	AIUpdateInterface *m_ai;
};

#include "../../../Include/GameLogic/Rva00358752Opaque.h"

class ScriptEngine;
extern class ScriptEngine *TheScriptEngine;

void ScriptActions::Rva003C8C6EDo(const AsciiString &unitName)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(unitName);
	if (!obj)
		return;
	ObjectKind *kind = (ObjectKind *)obj->m_04;
	if (!(kind->m_flags & 0x80))
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai) {
		ai->aiEvacuate(false, CMD_FROM_SCRIPT);
		return;
	}
	ContainModule *contain = obj->m_contain;
	if (!contain)
		return;
	contain->slot42(0);
}
