// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00290E67@Object@@QBEPBVAsciiString@@XZ retail 0x00290E67 68B.
// Object display-string selector: first non-empty among +0x41C +0x424 +0x420 else template+0x70.
// Evidence: same-this Object via findObjectByID callers 0x00267EB3 (ecx+0x258 AI) 0x003794E0 (Object*);
// AsciiString emptiness via rowed ?isEmpty@?$StringBase@D@@QBE_NXZ at 0x00001E2F x3;
// abuts ?findSpecialPowerModuleInterface@Object (0x00290E22+69); callee 0x0031D5F8 takes PBVAsciiString.
#include "ascii_string.h"


struct ThingTemplate
{
	char m_pad[0x70];
	AsciiString m_name70;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;

private:
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x41C - 0x08];
	AsciiString m_str41C;
	AsciiString m_str420;
	AsciiString m_str424;
};

const AsciiString *Object::rva00290E67() const
{
	if (!m_str41C.isEmpty())
		return &m_str41C;
	if (!m_str424.isEmpty())
		return &m_str424;
	if (!m_str420.isEmpty())
		return &m_str420;
	return &m_template->m_name70;
}
