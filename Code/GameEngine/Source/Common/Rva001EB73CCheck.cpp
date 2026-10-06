// cl: /MD
// ?rva001EB73C@Rva001EB73C@@QAE_NXZ, retail 0x001EB73C, 15 bytes.
// Null-check wrapper over rowed 0x001EB435: if ptr at +0x10 is null return true
// else tail-jmp to Rva001EB435::rva001EB435. Evidence: tail call to rowed
// ?rva001EB435@Rva001EB435@@QAE_NXZ, caller 0x00521270, prev Rva001EB435Check
// documents this as null fast path.
class Rva001EB435
{
public:
	bool rva001EB435();
};

class Rva001EB73C
{
public:
	bool rva001EB73C();
private:
	char m_pad[0x10];
	Rva001EB435 *m_ptr;
};

bool Rva001EB73C::rva001EB73C()
{
	if (m_ptr)
		return m_ptr->rva001EB435();
	return true;
}
