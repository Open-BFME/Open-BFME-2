// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C31F3Do@ScriptActions@@QAEXABVAsciiString@@0_N@Z @0x003C31F3 217B: lookup unit by value then AutoAbilityBehavior module via cached NameKey then CommandButton compare loop. Evidence: rowed lookupUnitByValue 0x358752 nameToKey 0x148E1A findModule 0x28B6D6 findCommandButton 0x31BE3C rva00290E67 0x290E67 rva0031D5F8 0x31D5F8 getCommandButton 0x409EE8 rva0045A748 0x45A748 StringBase copy 0x365F0 globals g_Va009FE16C TheNameKeyGenerator g_bfmeWorldRV AutoAbilityBehavior literal; caller 0x003CE5F9; ret 0xc stdcall.
#include "ascii_string.h"

enum NameKeyType { NK_NONE = 0 };

class Object;
class Module;
#include "../../../Include/GameClient/CommandButton.h"
#include "../../../Include/GameClient/ControlBar.h"
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
class Object
{
protected:
	Module *findModule(NameKeyType key) const;
public:
	const AsciiString *rva00290E67() const;
	friend void ScriptActions::Rva003C31F3Do(const AsciiString &, const AsciiString &, bool);
};
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../Include/GameLogic/Rva00358752Opaque.h"
class ScriptEngine;
extern class ScriptEngine *TheScriptEngine;
#include "../../../Include/Common/Rva0031D5F8.h"
#include "../../../Include/GameClient/CommandSet.h"
#include "../../../Include/GameLogic/Module/AutoAbilityBehavior.h"

void ScriptActions::Rva003C31F3Do(const AsciiString &unitName, const AsciiString &buttonName, bool flag)
{
	Object *obj = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue((AsciiString &)unitName);
	if (obj == 0)
		return;
	static NameKeyType autoKey = TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
	Module *module = obj->findModule(autoKey);
	if (module == 0)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(buttonName);
	if (button == 0)
		return;
	if (button->m_autoAbility == 0)
		return;
	void *cmdSet = ((Rva0031D5F8 *)((BfmeWorldRV *)TheControlBar))->rva0031D5F8(obj->rva00290E67());
	if (cmdSet == 0)
		return;
	for (int i = 0; i < 0x20; ++i) {
		const CommandButton *cb = ((CommandSet *)cmdSet)->getCommandButton(i);
		if (button != cb)
			continue;
		((AutoAbilityBehavior *)module)->rva0045A748((void *)button, flag);
	}
}
