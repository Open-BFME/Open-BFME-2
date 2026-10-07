// ?rva000E912A@Rva000E912A@@QAEXPAURva000E912AVec@@MH@Z
// partial score=0.68 date=2026-10-07
// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD
// ?rva000E912A@Rva000E912A@@QAEXPAURva000E912AVec@@MH@Z @0x000E912A 164B.
// Walks 2000 records of 0xA0 from +0x1958 while count at +0x4FB58 is
// positive. A non-negative key at +0x40 whose xyz is inside the squared
// radius calls thiscall 0x000E90DB with the record argument at +0x58.

struct Rva000E912AVec
{
	float m_x;
	float m_y;
	float m_z;
};

struct Rva000E912ARec
{
	float m_x;
	float m_y;
	float m_z;
	char m_pad0C[0x40 - 0x0C];
	int m_key;
	char m_pad44[0x58 - 0x44];
	int m_arg;
	char m_tail[0xA0 - 0x5C];
};

class Rva000E912A
{
public:
	void rva000E90DB(int arg, int extra);
	void rva000E912A(Rva000E912AVec *point, float radius, int extra);

	char m_pad[0x1958];
	Rva000E912ARec m_rec[2000];
	int m_count;
};

void Rva000E912A::rva000E912A(Rva000E912AVec *point, float radius, int extra)
{
	for (int index = 0; index < m_count; ++index)
	{
		Rva000E912ARec *rec = &m_rec[index];
		if (rec->m_key < 0)
			continue;
		float px = *(volatile float *)&point->m_x;
		float pz = *(volatile float *)&point->m_z;
		float rx = rec->m_x;
		float rz = rec->m_z;
		float py = *(volatile float *)&point->m_y;
		float ry = rec->m_y;
		float dx = rx - px;
		float dz = rz - pz;
		float dy = ry - py;
		float dist = dz * dz + dy * dy + dx * dx;
		if (radius * radius > dist)
			rva000E90DB(rec->m_arg, extra);
	}
}
