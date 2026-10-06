// cl: /O1 /MD
// ?rva00094DD3@Rva00094DD3@@QAEXPAURva00094DD3Val@@@Z @0x00094DD3 18B evidence: leaf 2 callers in FUN_00495821; no callees; float at +0x50 int at +0x54
struct Rva00094DD3Val
{
	float m_00;
	int m_04;
};
class Rva00094DD3
{
public:
	void rva00094DD3(Rva00094DD3Val *out);
private:
	char m_pad00[0x50];
	float m_50;
	int m_54;
};
void Rva00094DD3::rva00094DD3(Rva00094DD3Val *out)
{
	out->m_00 = m_50;
	out->m_04 = m_54;
}
