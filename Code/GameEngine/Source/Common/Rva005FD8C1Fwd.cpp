// cl: /MD /EHsc
// ?rva005FD8C1@Rva005FD8C1@@QAEXXZ @0x005FD8C1 8B
// Honest address name: __thiscall forwarder to rowed 0x005F9330.
// Target evidence: retail mov ecx,[ecx+4] jmp 0x005F9330, rowed callee ?rva005F9330@Rva005F9330@@QAEXXZ, caller call at 0x005E95EC with no pushes, chain lane from just-landed 0x005F9330.
class Rva005F9330
{
public:
	void rva005F9330();
};

struct Rva005FD8C1
{
	char m_pad0[4];
	Rva005F9330 *m_ptr4;
	void rva005FD8C1();
};

void Rva005FD8C1::rva005FD8C1()
{
	return m_ptr4->rva005F9330();
}
