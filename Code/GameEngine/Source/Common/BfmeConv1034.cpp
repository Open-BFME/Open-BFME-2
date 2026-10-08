class BfmeN1034
{
public:
	int bfmeVal1034(void);
};

// The table lookup is the rowed Rva0070B380::lookup.
class EAStringC;
class Rva0070B380
{
public:
	void *lookup(const EAStringC &key);
};

class BfmeTab1034;

class BfmeF1034
{
public:
	int bfmeGo1034F(int k);

	char m_bfmePad[8];
	BfmeTab1034 *m_bfmeTab;
};

int BfmeF1034::bfmeGo1034F(int k)
{
	BfmeN1034 *n = (BfmeN1034 *)((Rva0070B380 *)m_bfmeTab)->lookup(*(const EAStringC *)k);

	if (n != 0)
		return n->bfmeVal1034();

	return -1;
}
