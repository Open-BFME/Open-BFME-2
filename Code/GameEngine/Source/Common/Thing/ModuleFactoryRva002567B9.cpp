// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva002567B9@ModuleFactory@@QAEXABVAsciiString@@HW4ModuleType@@HH@Z @0x002567B9 49B
// ModuleFactory create helper: null first arg returns; else findModuleTemplate
// (rowed 0x0025674F); null template or null create fn at +8 returns; else call
// the cdecl create fn with the three pointer args. Evidence: unlock lane;
// caller 0x0033B604 in 0x0033B5B8; protected-method this-call proves
// ModuleFactory membership; AsciiString inherits StringBase<char> for the
// dual isEmpty/ABVAsciiString manglings.
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
		void (__cdecl *m_create08)(int a, int b, int c);
	};
	void rva002567B9(const AsciiString &name, int a, ModuleType type, int b, int c);
protected:
	const ModuleTemplate *findModuleTemplate(const AsciiString &name, ModuleType type);
};
// ?rva002567B9@ModuleFactory@@QAEXABVAsciiString@@HW4ModuleType@@HH@Z
void ModuleFactory::rva002567B9(const AsciiString &name, int a, ModuleType type, int b, int c)
{
	if (a == 0)
		return;
	const ModuleTemplate *tmpl = findModuleTemplate(name, type);
	if (tmpl == 0)
		return;
	if (tmpl->m_create08 == 0)
		return;
	tmpl->m_create08(a, c, b);
}
