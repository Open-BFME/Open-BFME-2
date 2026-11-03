// cl: /Ireference/shims/bfme2_ascii /MD
// ?removeModuleInfo@Rva0033C8E8@@QAE_NABVAsciiString@@AAV2@@Z @0x0033C8E8 113B:
// chain over four 12B vectors at +0x2e4/+0x2f0/+0x2fc/+0x308 via the rowed
// 0x33C807 tag find-erase; ORs the four bool results. Caller passes the same
// two AsciiString params through; ret 8 matches.

#include "ascii_string.h"


#include "../../../Include/Common/ModuleInfoClass.h"

class Rva0033C8E8
{
public:
	bool removeModuleInfo(const AsciiString &tag, AsciiString &out);

private:
	char m_pad[0x2E4];
	ModuleInfo m_v0;
	ModuleInfo m_v1;
	ModuleInfo m_v2;
	ModuleInfo m_v3;
};

bool Rva0033C8E8::removeModuleInfo(const AsciiString &tag, AsciiString &out)
{
	bool found = false;
	if (m_v0.clearModuleDataWithTag(tag, out))
		found = true;
	if (m_v1.clearModuleDataWithTag(tag, out))
		found = true;
	if (m_v2.clearModuleDataWithTag(tag, out))
		found = true;
	if (m_v3.clearModuleDataWithTag(tag, out))
		found = true;
	return found;
}
