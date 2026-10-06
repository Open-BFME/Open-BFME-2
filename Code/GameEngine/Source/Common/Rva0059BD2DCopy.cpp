// cl: /MD
// ?rva0059BD2D@Rva0059BD2D@@QAEXPBX@Z @0x0059BD2D (43B)
// Thiscall copies six dwords from src+0x34 to this+0x0C. Called with
// lea ecx [esi+0xFC] plus push edi at 0x004FB261. Evidence unlock lane
// plus caller 0x004FB222.
class Rva0059BD2D
{
public:
	void rva0059BD2D(const void *src);

private:
	char m_pad00[0x0c];
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
};

struct Src0059BD2D
{
	char m_pad[0x34];
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
};

void Rva0059BD2D::rva0059BD2D(const void *src)
{
	const Src0059BD2D *s = (const Src0059BD2D *)src;
	m_0c = s->m_34;
	m_10 = s->m_38;
	m_14 = s->m_3c;
	m_18 = s->m_40;
	m_1c = s->m_44;
	m_20 = s->m_48;
}
