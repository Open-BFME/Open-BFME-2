// cl: /MD
// ?rva00524A2D@Rva00524A2D@@QAEXHHHH@Z @0x00524A2D (31B): four-dword setter at +0x10
// Evidence: two callers 0x002D32E3 and 0x005C9619 neighbours Rva0052493FClear and
// Rva00524A4CClear both /O1 /MD honest Rva owner ret 0x10 four int args.
class Rva00524A2D
{
public:
	void rva00524A2D(int a, int b, int c, int d);

private:
	char m_pad[0x10];
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
};

void Rva00524A2D::rva00524A2D(int a, int b, int c, int d)
{
	m_10 = a;
	m_14 = b;
	m_18 = c;
	m_1c = d;
}
