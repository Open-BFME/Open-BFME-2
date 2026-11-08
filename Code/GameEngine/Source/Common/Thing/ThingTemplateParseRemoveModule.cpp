// cl: /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// Semantic donor: BFME1 6583b3c1ff21db4a561285717028fdafc780b7db
// game/GameEngine/Source/Common/Thing/ThingTemplateModuleRemovalParsers.cpp.
// Native33CD41..33CE18 Ghidra215; target field entryDBF4E8 names RemoveModule.
// Target name+64, replacement strings+94/+98, signed mode+5F8 and error
// texts are independently read from retail; donor supplies parser semantics.
// Target removeModuleInfo call uses the existing rowed113-byte four-list
// chain at33C8E8 under its established opaque spelling. The home TU supplies
// s_objectFieldParseTable. Shared BFME2 AsciiString owns direct36410 cleanup.
typedef int Int;
typedef bool Bool;

// The empty-string constant at retail 0x0107388B.

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
#include "Common/INIException.h"

struct FieldParse;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
#include "../../../Include/Common/INI/INI.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
enum ModuleParseMode
{
	MODULEPARSE_NORMAL,
	MODULEPARSE_ADD_REMOVE_REPLACE,
	MODULEPARSE_INHERITABLE,
	MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND
};

#include "../../../Include/Common/ThingTemplate.h"

class Rva0033C8E8 { public: bool removeModuleInfo(const AsciiString &,AsciiString &); };
// ?parseRemoveModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseRemoveModule(INI *ini, void *instance, void *store, const void *userData)
{
	ThingTemplate *self = (ThingTemplate *)instance;
	Int oldMode = (Int)self->m5F8;
	if (oldMode != 0)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m5F8 = 1;
	const char *modToRemove = ini->getNextToken();
	AsciiString removedModuleName;
	Bool removed = ((Rva0033C8E8 *)self)->removeModuleInfo(modToRemove, removedModuleName);
	if (!removed)
	{
		throw INIException(3, "RemoveModule %s was not found for %s.", modToRemove, self->getName().str());
	}

	self->m5F8 = oldMode;
}


