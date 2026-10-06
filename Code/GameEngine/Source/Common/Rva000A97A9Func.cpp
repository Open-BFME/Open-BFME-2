// cl: /DNDEBUG /MD
// ?rva000A97A9@Rva000A97A9@@QAEXPAX@Z @0x000A97A9 32B
// Honest thiscall method: ecx=this with float at +0x1c and int at +0x20,
// dst void* written at +0x40(float copy) +0x44(int) +0x20(bits) +0x1c(=1).
// Evidence: unlock lane, callers 0x000AAC7B and 0x000AAD9D pass ecx=[esi+0x5c] and push esi.
class Rva000A97A9
{
public:
	void rva000A97A9(void *dst_);
private:
	char _pad[0x1c];
	float m_1c;
	int m_20;
};
struct Rva000A97A9Dst
{
	char _p0[0x1c];
	int m_1c;
	int m_20;
	char _p1[0x1c];
	float m_40;
	int m_44;
};
void Rva000A97A9::rva000A97A9(void *dst_)
{
	Rva000A97A9Dst *dst = (Rva000A97A9Dst *)dst_;
	dst->m_40 = m_1c;
	dst->m_44 = m_20;
	dst->m_20 = *(int *)&m_1c;
	dst->m_1c = 1;
}
