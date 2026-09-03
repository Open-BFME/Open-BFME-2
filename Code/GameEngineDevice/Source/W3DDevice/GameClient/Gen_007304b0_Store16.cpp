// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Retail 0x007304B0. Store a 16-bit value at m_24[m_8 * b + a] with bounds checks.

class Gen_007304b0
{
public:
	void store(int a, int b, short v);

private:
	unsigned char m_pad8[0x08];
	int m_8;
	unsigned char m_pad20[0x20 - 0x0C];
	int m_20;
	short *m_24;
};

// ?store@Gen_007304b0@@QAEXHHF@Z
void Gen_007304b0::store(int a, int b, short v)
{
	int idx = m_8 * b + a;
	if (idx < 0)
		return;
	if (idx >= m_20)
		return;
	if (!m_24)
		return;
	m_24[idx] = v;
}
