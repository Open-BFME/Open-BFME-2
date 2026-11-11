// cl: /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// Semantic donor: BFME1 6583b3c1ff21db4a561285717028fdafc780b7db
// game/GameEngine/Source/Common/Thing/ThingTemplateModuleRemovalParsers.cpp.
// Native33CE18..33CF2F Ghidra279; target field entryDBF4F8 names ReplaceModule.
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

#include "../../../Include/Common/Rva0033C8E8.h"


// ?parseReplaceModule@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
//
// removeModuleInfo takes the module name as a const AsciiString reference, so the
// token converts through a temporary that dies right after the call.
void ThingTemplate::parseReplaceModule(INI *ini, void *instance, void *store, const void *userData)
{
	ThingTemplate *self = (ThingTemplate *)instance;

	ModuleParseMode oldMode = (ModuleParseMode)self->m5F8;
	if (oldMode != MODULEPARSE_NORMAL)
		throw INIException(3, "Expected oldMode to be MODULEPARSE_NORMAL");

	self->m5F8 = MODULEPARSE_ADD_REMOVE_REPLACE;

	const char *modToRemove = ini->getNextToken();
	AsciiString removedModuleName;
	Bool removed = ((Rva0033C8E8 *)self)->removeModuleInfo(modToRemove, removedModuleName);
	if (!removed)
		throw INIException(3, "ReplaceModule %s was not found for %s, cannot continue.", modToRemove, self->getName().str());

	self->m094 = removedModuleName;
	self->m098 = modToRemove;
	ini->initFromINI(self, s_objectFieldParseTable);
	self->m094.clear();
	self->m098.clear();

	self->m5F8 = oldMode;
}
