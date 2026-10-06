// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva002A7611@Rva002A7611@@QAEXHH@Z @0x002A7611 51B
// Evidence: thiscall ret 8; walks the 12-byte BfmeE12 vector at +0x20
// (begin +0x20, finish +0x24), and on the first element whose second word
// equals the second argument and whose first word equals the first argument
// hands it to the rowed single-element erase ?erase@Rva002A75DA 0x002A75DA
// (its sole caller is this body) and stops. Sole caller 0x004B86FF. No donor
// body found in reference/open-bfme-1; the name is address-derived.

struct BfmeE12
{
	int a;
	int b;
	int c;
};

class Rva002A75DA
{
public:
	BfmeE12 *erase(BfmeE12 *position);
	BfmeE12 *m_start;
	BfmeE12 *m_finish;
};

class Rva002A7611
{
public:
	void rva002A7611(int a, int b);

private:
	unsigned char m_pad[0x20];
	Rva002A75DA m_list; // +0x20
};

void Rva002A7611::rva002A7611(int a, int b)
{
	for (BfmeE12 *it = m_list.m_start; it != m_list.m_finish; ++it)
	{
		if (it->b == b && it->a == a)
		{
			m_list.erase(it);
			return;
		}
	}
}
