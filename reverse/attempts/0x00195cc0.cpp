// ?bfmeComputeBVID@BfmePartBVID@@QAEHXZ
// partial score=0.95 date=2026-09-22
// ?bfmeComputeVID@BfmePartVID@@QAEHXZ @0x00195BC0
// ?bfmeComputeBVID@BfmePartBVID@@QAEHXZ @0x00195CC0
// Shard TU: SizeVID lives in BfmeConv1372.cpp and calls these out-of-line;
// defining them there inlines and breaks it, so they live here.

class BfmePartVID
{
public:
	int bfmeComputeVID();

private:
	char m_pad00[8];
	int m_bfme08;
	char m_pad0C[0x0C];
	int m_bfme18;
	int m_bfme1C;
};

class BfmePartBVID
{
public:
	int bfmeComputeBVID();

private:
	char m_pad00[0x0C];
	int m_bfme0C;
	int m_bfme10;
};

// ?bfmeComputeVID@BfmePartVID@@QAEHXZ
int BfmePartVID::bfmeComputeVID()
{
	return ((m_bfme1C + 1 - m_bfme18) * m_bfme08) * 4 + 0x20;
}

// ?bfmeComputeBVID@BfmePartBVID@@QAEHXZ
int BfmePartBVID::bfmeComputeBVID()
{
	int top = m_bfme10;
	return (top - m_bfme0C + 8) / 8 + 0x18;
}
