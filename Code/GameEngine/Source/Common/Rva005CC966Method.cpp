// cl: /O1 /DNDEBUG /MD
// ?rva005CC966@Rva005CC966@@QAEXXZ @0x005CC966 30B evidence: Eva rva001DE2DA pin event pos 0; caller jmp 0x005CCB6B; global g_00DFDC30
struct Coord3D
{
	float x;
	float y;
	float z;
};
class Eva
{
public:
	void rva001DE2DA(int ev, const Coord3D *pos, int unused);
};
extern class Eva *TheEva;
class Rva005CC966
{
public:
	void rva005CC966();
	char m_pad[0x10];
	int m_event;
	Coord3D m_pos;
	unsigned char m_flag;
};
void Rva005CC966::rva005CC966()
{
	const Coord3D *pos = m_flag ? &m_pos : 0;
	TheEva->rva001DE2DA(m_event, pos, 0);
}
