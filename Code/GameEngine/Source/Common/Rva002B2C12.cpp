// cl: /O1 /MD
// ?rva002B2C12@Rva002B2C12@@QAEHPAVRva00318C32@@0@Z @0x002B2C12 46B.
class Rva00318C32
{
public:
	int rva00318C32();
};

class Rva0020EC99Helper
{
public:
	int rva0020EC99(Rva00318C32 *a1, int t2, int t1, int z1, int z2);
};

class Rva002B2C12
{
public:
	int rva002B2C12(Rva00318C32 *a1, Rva00318C32 *a2);

private:
	unsigned char m_pad00[0xB0];
	Rva0020EC99Helper *m_b0;
};

int Rva002B2C12::rva002B2C12(Rva00318C32 *a1, Rva00318C32 *a2)
{
	return m_b0->rva0020EC99(a1, a1->rva00318C32(), a2->rva00318C32(), 0, 0);
}
