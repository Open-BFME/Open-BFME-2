// cl: /MD
// ?rva000E6FE3@Rva000E6FE3@@QAEX_N@Z retail 0x000E6FE3 51B unlock lane.
// Evidence: byte-store loop over +0x199C stride 0xA0 with count at +0x4FB58
// and dirty flag at +0x4FB5C; same offsets and stride as Rva000E76B8 in the
// neighbour TU Code/GameEngine/Source/Common/Rva000E76B8.cpp; caller at
// 0x000682D9 tail-jmps with the same 4-byte arg.
struct Rva000E6FE3Elem
{
	unsigned char flag;
	unsigned char pad[3];
	unsigned char data[0x9C];
};

class Rva000E6FE3
{
public:
	void rva000E6FE3(bool v);
	unsigned char m_pad0[0x199C];
	Rva000E6FE3Elem m_elems[1999];
	unsigned char m_gap[0x5C];
	int m_count;
	unsigned char m_dirty;
};

void Rva000E6FE3::rva000E6FE3(bool v)
{
	for (int i = 0; i < m_count; i++)
		m_elems[i].flag = v;
	m_dirty = 1;
}
