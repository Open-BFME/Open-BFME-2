// cl: /MD
// ?rva000EA21A@Rva000EA21A@@QAEX_N@Z retail 0x000EA21A 51B unlock lane.
// Evidence: byte-store loop over +0x604 stride 0xE8 with count at +0x44540
// and dirty flag at +0x44544; same shape as Rva000E6FE3 in the neighbour TU
// Code/GameEngine/Source/Common/Rva000E6FE3.cpp; caller at 0x000682C9 forwards
// the same 4-byte arg and tail-jmps to that twin.
struct Rva000EA21AElem
{
	unsigned char flag;
	unsigned char pad[3];
	unsigned char data[0xE4];
};

class Rva000EA21A
{
public:
	void rva000EA21A(bool v);
	unsigned char m_pad0[0x604];
	Rva000EA21AElem m_elems[1199];
	unsigned char m_gap[0xA4];
	int m_count;
	unsigned char m_dirty;
};

void Rva000EA21A::rva000EA21A(bool v)
{
	for (int i = 0; i < m_count; i++)
		m_elems[i].flag = v;
	m_dirty = 1;
}
