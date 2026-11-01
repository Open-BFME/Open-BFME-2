// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva00290E67@Object@@QBEPBVAsciiString@@XZ retail 0x00290E67 68B.
// Object display-string selector: first non-empty among +0x41C +0x424 +0x420 else template+0x70.
// Evidence: same-this Object via findObjectByID callers 0x00267EB3 (ecx+0x258 AI) 0x003794E0 (Object*);
// AsciiString emptiness via rowed ?isEmpty@?$StringBase@D@@QBE_NXZ at 0x00001E2F x3;
// abuts ?findSpecialPowerModuleInterface@Object (0x00290E22+69); callee 0x0031D5F8 takes PBVAsciiString.
#include "ascii_string.h"


#include "../../../Include/Common/ThingTemplate.h"

struct Rva00290EABElem
{
	char m_bytes[0x5C];
};

struct Rva00290EABVec
{
	Rva00290EABElem *m_start;
	Rva00290EABElem *m_finish;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
	const Rva00290EABElem *rva00290EAB(int idx) const;

private:
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0xA8 - 0x08];
	Rva00290EABElem m_defaultA8;
	char m_pad104[0x108 - 0x104];
	Rva00290EABVec *m_vec108;
	char m_pad10C[0x41C - 0x10C];
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
	return &m_template->m_commandSetString;
}

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

const Rva00290EABElem *Object::rva00290EAB(int idx) const
{
	if (idx >= 0)
	{
		Rva00290EABVec *vec = m_vec108;
		if ((unsigned int)idx < (unsigned int)(vec->m_finish - vec->m_start))
		{
			_ReadWriteBarrier();
			return &vec->m_start[idx];
		}
	}
	return &m_defaultA8;
}




