// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00256F39@ModuleFactory@@QAEHABVAsciiString@@W4ModuleType@@@Z @0x00256F39 46B
// ModuleFactory helper: empty name returns 0; else findModuleTemplate (rowed
// 0x0025674F) and return the int at template+0x0C, 0 when missing. isEmpty
// via rowed StringBase 0x00001E2F. Evidence: unlock lane; callers 0x0033D8CC
// and 0x0033D8FB in 0x0033D865; this-calls protected ModuleFactory method.
#include "ascii_string.h"
enum ModuleType
{
	MODULE_TYPE_INVALID = 0
};
class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		int m_00;
		int m_04;
		int m_08;
		int m_tag0C;
	};
	int rva00256F39(const AsciiString &name, ModuleType type);
protected:
	const ModuleTemplate *findModuleTemplate(const AsciiString &name, ModuleType type);
};
// ?rva00256F39@ModuleFactory@@QAEHABVAsciiString@@W4ModuleType@@@Z
int ModuleFactory::rva00256F39(const AsciiString &name, ModuleType type)
{
	if (!name.isEmpty())
	{
		const ModuleTemplate *tmpl = findModuleTemplate(name, type);
		if (tmpl != 0)
			return tmpl->m_tag0C;
	}
	return 0;
}
