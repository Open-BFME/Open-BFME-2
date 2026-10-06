// cl: /MD
//
// ?rva0056AA32@Rva0056AA32@@QAEHPBVRva004E0625@@@Z @0x0056AA32 34B.
// Guarded equality: 0 when the +0x10 count is zero, else whether the rowed
// const 0x004E0625 query equals it (nested if shares one false target).
class Rva004E0625
{
public:
	int rva004E0625() const;
};

class Rva0056AA32
{
public:
	int rva0056AA32(const Rva004E0625 *arg);
private:
	char m_pad[0x10];
	int m_10;	// +0x10
};

int Rva0056AA32::rva0056AA32(const Rva004E0625 *arg)
{
	if (m_10 != 0) {
		if (arg->rva004E0625() == m_10)
			return 1;
	}
	return 0;
}
