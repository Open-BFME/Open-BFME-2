// cl: /MD
// ?rva001EB74B@Rva001EB74B@@QAE_NPAURva001EB6A5Out@@@Z, retail 0x001EB74B, 17 bytes.
// Chain from 0x001EB6A5: null-check wrapper over rowed 0x001EB6A5, if ptr at +0x10
// is null return false else tail-jmp to Rva001EB6A5::rva001EB6A5 forwarding out.
// Evidence: tail call to just-landed row, caller 0x00521560, prev Rva001EB73CCheck
// same null-wrapper shape.
struct Rva001EB6A5Out;
class Rva001EB6A5
{
public:
	bool rva001EB6A5(Rva001EB6A5Out *out);
};

class Rva001EB74B
{
public:
	bool rva001EB74B(Rva001EB6A5Out *out);
private:
	char m_pad[0x10];
	Rva001EB6A5 *m_ptr;
};

bool Rva001EB74B::rva001EB74B(Rva001EB6A5Out *out)
{
	if (m_ptr)
		return m_ptr->rva001EB6A5(out);
	return false;
}
