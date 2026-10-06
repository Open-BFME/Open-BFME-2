// cl: /MD
//
// ?rva005E0D94@Rva005E0D94@@QAEXXZ @0x005E0D94 8B
// Chain forwarder to rowed 0x005E0CC7 via +8 member tail jmp.
// Evidence: rowed callee plus callers at 0x005CC345 0x005F57F5.
class Rva005E0CC7
{
public:
	void rva005E0CC7();
};

class Rva005E0D94
{
public:
	void rva005E0D94();
private:
	char m_pad00[8];
	Rva005E0CC7 *m_08;
};

void Rva005E0D94::rva005E0D94()
{
	return m_08->rva005E0CC7();
}
