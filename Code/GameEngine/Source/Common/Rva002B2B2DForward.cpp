// cl: /O1 /MD
//
// ?rva002B2B2D@Rva002BA8F1Logic@@QAEPAURva002B3740Item@@XZ retail 0x002B2B2D 18 bytes.
// Leaf forwarder: push this+0xB8 int, ecx = this+0xB0 view, call rowed
// Rva0020EAF6View::rva0020EAF6. Identity via pin plus callers 0x002B35F7
// 0x002B3669 0x002B3740 in Rva002BA8F1Logic methods; prev/next share /O1.
class Rva0020E89C;

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

struct Rva002B3740Item;

class Rva002BA8F1Logic
{
public:
	Rva002B3740Item *rva002B2B2D();
private:
	char m_pad[0xB0];
	Rva0020EAF6View *m_B0;
	int m_B4;
	int m_B8;
};

Rva002B3740Item *Rva002BA8F1Logic::rva002B2B2D()
{
	return (Rva002B3740Item *)m_B0->rva0020EAF6(m_B8);
}
