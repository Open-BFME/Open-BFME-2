// cl: /O1 /MD
//
// ?rva002B2579@Rva002BA8F1Logic@@QAEPAURva002B2579Result@@H@Z retail 0x002B2579 23 bytes.
// Null-gated forward: if id==0 return null else tail-jmp rowed
// Rva0020EEF4Outer::rva0020EEF4 via this+0xB0. Identity via pin plus callers
// 0x002DA20A 0x0040C470; prev/next share /O1 /MD.
class Rva0020EEF4Outer
{
public:
	int rva0020EEF4(int v);
};

struct Rva002B2579Result;

class Rva002BA8F1Logic
{
public:
	Rva002B2579Result *rva002B2579(int id);
private:
	char m_pad[0xB0];
	Rva0020EEF4Outer *m_B0;
};

Rva002B2579Result *Rva002BA8F1Logic::rva002B2579(int id)
{
	if (id == 0)
		return 0;
	return (Rva002B2579Result *)m_B0->rva0020EEF4(id);
}
