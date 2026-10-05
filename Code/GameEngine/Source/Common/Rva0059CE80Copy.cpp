// cl: /O1 /MD
// ?rva0059CE80@Rva0059CE80@@QAEXPBX@Z @0x0059CE80 30B
// Thiscall copies four dwords from src+0x24 to this+0x00. Called with
// lea ecx [esi+0xEC] plus push edi at 0x004FB255. Evidence unlock lane
// plus caller 0x004FB222 and sibling Rva0059BD2D pattern.
class Rva0059CE80
{
public:
	void rva0059CE80(const void *src);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

struct Src0059CE80
{
	char m_pad[0x24];
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
};

void Rva0059CE80::rva0059CE80(const void *src)
{
	const Src0059CE80 *s = (const Src0059CE80 *)src;
	m_00 = s->m_30;
	m_04 = s->m_28;
	m_08 = s->m_2c;
	m_0c = s->m_24;
}
