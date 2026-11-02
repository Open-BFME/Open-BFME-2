// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?findModuleInterfaceMask@ModuleFactory@@QAEHABVAsciiString@@W4ModuleType@@@Z @0x00256F39 46B
// ModuleFactory helper: empty name returns 0; else findModuleTemplate (rowed
// 0x0025674F) and return the int at template+0x0C, 0 when missing. isEmpty
// via rowed StringBase 0x00001E2F. Evidence: unlock lane; callers 0x0033D8CC
// and 0x0033D8FB in 0x0033D865; this-calls protected ModuleFactory method.
#include "ascii_string.h"
enum ModuleType
{
	MODULE_TYPE_INVALID = 0
};
#include "../../Include/Common/ModuleFactoryClass.h"
// ?findModuleInterfaceMask@ModuleFactory@@QAEHABVAsciiString@@W4ModuleType@@@Z
int ModuleFactory::findModuleInterfaceMask(const AsciiString &name, ModuleType type)
{
	if (!name.isEmpty())
	{
		const ModuleTemplate *moduleTemplate = findModuleTemplate(name, type);
		if (moduleTemplate != 0)
			return moduleTemplate->m_tag0C;
	}
	return 0;
}
