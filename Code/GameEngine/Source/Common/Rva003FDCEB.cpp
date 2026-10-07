// cl: /O1 /MD
//
// ?rva003FDCEB@Rva003FDCEB@@QAEHXZ @0x003FDCEB 26B.
// Guarded tail: run the no-arg member at 0x003FB7DB, and if m_38 exceeds
// m_48 tail-jump to the 0x003FDC46 member (int return makes the tail a
// reliable jmp); else return m_38 already sitting in eax.
// Evidence: retail push esi / mov esi,ecx / call 0x3FB7DB /
// mov eax,[esi+0x38] / cmp eax,[esi+0x48] / jbe / mov ecx,esi+pop esi /
// jmp 0x3FDC46 / pop esi+ret.
class Rva003FDCEB
{
public:
	int rva003FDCEB();
	void rva003FB7DB();
	int rva003FDC46();
private:
	char m_pad00[0x38];
	unsigned int m_38;
	char m_pad3C[0xC];
	unsigned int m_48;
};

int Rva003FDCEB::rva003FDCEB()
{
	rva003FB7DB();
	if (m_38 > m_48)
		return rva003FDC46();
	return m_38;
}
