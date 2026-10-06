// cl: /MD
// ?rva0027D1C6@Rva0027D1C6@@QAEPAV1@XZ, retail 0x0027D1C6, 41 bytes.
// Thiscall init: clears +0/+4/+8 to 0.0f, +0xc/+0x14 to 0,
// sets +0x10 from global float VA 0x00BC876C (data 0x007C876C).
// Callers 0x27F0DF/0x27F114, same Common family as Rva0027D244Init
// whose init returns this (mov eax,ecx early then stores via eax).
// No donor: honest address name. Returns this to hold base in eax.
extern float g_00BC876C;

class Rva0027D1C6
{
public:
	Rva0027D1C6 *rva0027D1C6();
private:
	float m_00;
	float m_04;
	float m_08;
	int m_0C;
	float m_10;
	int m_14;
};

Rva0027D1C6 *Rva0027D1C6::rva0027D1C6()
{
	float t = g_00BC876C;
	Rva0027D1C6 *s = this;
	s->m_0C = 0;
	s->m_14 = 0;
	s->m_10 = t;
	s->m_00 = 0.0f;
	s->m_04 = 0.0f;
	s->m_08 = 0.0f;
	return s;
}
