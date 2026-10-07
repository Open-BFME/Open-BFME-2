// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva001EDE45@Rva001EDE45@@QAEPAXXZ @0x001EDE45 7B:
// lea eax,[ecx+0x12fc]; ret. Honest address-name thiscall returning the
// address at +0x12fc; caller 0x00224FD4 unproven so Class=Rva001EDE45.
// Evidence: abuts prev 0x001EDE3A/11 and next 0x001EDE4C/23; no callees.

class Rva001EDE45
{
public:
	void *rva001EDE45();
private:
	char m_pad[0x12FC];
};

void *Rva001EDE45::rva001EDE45()
{
	return &m_pad[0x12FC];
}
