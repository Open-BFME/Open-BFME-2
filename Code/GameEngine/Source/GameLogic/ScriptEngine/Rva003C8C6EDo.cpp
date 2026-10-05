// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?Rva003C8C6EDo@@YGXABVAsciiString@@@Z @0x003C8C6E (95B).
// Unit evacuate via lookupUnitByValue plus kind flag 0x108/0x80 plus AI
// evacuate plus contain slot 0xA8. Evidence: callees rowed lookup 0x00358752
// aiEvacuate 0x002AE6B3, caller 0x003CC173. Precedent doNamedExitAll.
#include "ascii_string.h"

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class Object;
class AICommandInterface
{
public:
	void aiEvacuate(bool expose, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	char m_pad00[0x20];
	AICommandInterface m_command;
};

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

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

class ScriptEngine;
extern ScriptEngine *g_Va009FE16C;

void __stdcall Rva003C8C6EDo(const AsciiString &unitName)
{
	Object *obj = ((Rva00358752Opaque *)g_Va009FE16C)->lookupUnitByValue(unitName);
	if (!obj)
		return;
	ObjectKind *kind = (ObjectKind *)obj->m_04;
	if (!(kind->m_flags & 0x80))
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai) {
		ai->m_command.aiEvacuate(false, CMD_FROM_SCRIPT);
		return;
	}
	ContainModule *contain = obj->m_contain;
	if (!contain)
		return;
	contain->slot42(0);
}
