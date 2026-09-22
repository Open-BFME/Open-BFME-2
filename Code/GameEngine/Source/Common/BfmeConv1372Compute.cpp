// cl: /G7

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

int BfmePartVID::bfmeComputeVID()
{
	return ((m_bfme1C + 1 - m_bfme18) * m_bfme08) * 4 + 0x20;
}

int BfmePartBVID::bfmeComputeBVID()
{
	return (m_bfme10 - m_bfme0C + 8) / 8 + 0x18;
}
