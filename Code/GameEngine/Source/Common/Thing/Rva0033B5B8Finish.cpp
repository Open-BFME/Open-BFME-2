// cl: /O1 /DNDEBUG /MD /EHsc
// ?Rva0033B5B8Build@@YAXPAVModuleInfo@@W4ModuleType@@HH@Z @0x0033B5B8 124B
// ModuleInfo entry loop: per 0x14-sized entry fetch name (rowed getNthName
// 0x001F12DF into an EH temp) plus data nested in the factory call (rowed
// getNthData 0x0033ACE8), then call our ModuleFactory create helper
// 0x002567B9 with the factory global. Temp destroyed via releaseBuffer
// 0x00036410. Evidence: chain lane (calls our helper); callers in 0x0033C965;
// getNth rows; factory global 0x9FE960. The unnamed temporary is what makes
// MSVC keep the hidden-return pointer in ebx across getNthData (a named local
// is rematerialized as lea and loses the byte).
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
// Retail's public ~StringBase<char> is the releaseBuffer body at 0x36410; an
// inline body here would be emitted as a COMDAT copy every other unit binds to.
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
class BFMERetailAsciiString : public StringBase<char>
{
public:
	~BFMERetailAsciiString();
};
class ModuleData;
enum ModuleType
{
	MODULE_TYPE_INVALID = 0
};
// class-gate: allow AsciiString reference-cast parameter only; no AsciiString
// member is constructed, assigned or destroyed here, so this view emits no
// COMDAT and cannot differ from the shared header at link.
class ModuleFactory
{
public:
	void rva002567B9(const AsciiString &name, int a, ModuleType type, int b, int c);
};
extern ModuleFactory *TheModuleFactory;
class ModuleInfo
{
public:
	BFMERetailAsciiString getNthName(int index) const;
	const ModuleData *getNthData(int index) const;
	char *m_begin;
	char *m_end;
};
// ?Rva0033B5B8Build@@YAXPAVModuleInfo@@W4ModuleType@@HH@Z
void Rva0033B5B8Build(ModuleInfo *info, ModuleType type, int c, int b)
{
	for (int i = 0; i < (info->m_end - info->m_begin) / 0x14; ++i)
	{
		TheModuleFactory->rva002567B9((const AsciiString &)info->getNthName(i), (int)info->getNthData(i), type, b, c);
	}
}
