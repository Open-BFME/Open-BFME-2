// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva00594DC0@Rva00594DC0@@QAEXPAURva00594DC0Msg@@@Z, retail 0x00594DC0 71B.
// Network byte-order convert: htonl dword at +0 plus htons words at
// +4 +8 +0xa +6 via wsock32 IAT. Evidence: htonl FF15 htons edi call,
// callers 0x594E6D 0x5951C2 0x59527B 0x595313 with ecx plus 1 stack arg
// thiscall ret 4 prev 0x594D9C.

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) unsigned short __stdcall htons(unsigned short hostshort);

struct Rva00594DC0Msg
{
	unsigned long m_00;
	unsigned short m_04;
	unsigned short m_06;
	unsigned short m_08;
	unsigned short m_0a;
};

class Rva00594DC0
{
public:
	void rva00594DC0(Rva00594DC0Msg *msg);
};

void Rva00594DC0::rva00594DC0(Rva00594DC0Msg *msg)
{
	msg->m_00 = htonl(msg->m_00);
	msg->m_04 = htons(msg->m_04);
	msg->m_08 = htons(msg->m_08);
	msg->m_0a = htons(msg->m_0a);
	msg->m_06 = htons(msg->m_06);
}
