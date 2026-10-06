// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00529130@Rva00529130@@QAEXH@Z @0x00529130 27B
// Chain on 0x0052906B: __thiscall setter beside Rva0052906BUpdate. Forwards
// its int arg to rowed Rva0052906BUpdate, caches it at +0x10 and sets the
// byte at +0x0C. Evidence: caller 0x00529CB6 in 0x00529B6E; neighbour
// Rva0052906BUpdate.cpp shares the TU flags.
void __cdecl Rva0052906BUpdate(int rank);

class Rva00529130
{
public:
	void rva00529130(int rank);

private:
	char m_pad00[0x0C];
	unsigned char m_flag0C;
	char m_pad0D[0x03];
	int m_rank10;
};

void Rva00529130::rva00529130(int rank)
{
	Rva0052906BUpdate(rank);
	m_rank10 = rank;
	m_flag0C = 1;
}
