// cl: /MD
// ??1Rva0023D377@@QAE@XZ, retail 0x0023D377, 8 bytes.
// Dtor tail-jmp to rowed ??1Rva00438FC5@@QAE@XZ at 0x00438FC5;
// add ecx,4 then jmp. Member at +4 with 4B pad at +0; empty dtor lets the
// compiler tail-call. Deleting dtor at 0x0023DACC calls this plus rowed
// operator delete 0x0002FD60. No donor: honest address name.
class Rva00438FC5
{
public:
	~Rva00438FC5();
};

class Rva0023D377
{
public:
	~Rva0023D377();
private:
	unsigned int m_00;
	Rva00438FC5 m_04;
};

Rva0023D377::~Rva0023D377()
{
}
