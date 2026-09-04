// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Retail 0x007304B0. Store a 16-bit value at m_data[m_stride * b + a] with
// bounds checks against m_capacity.

class BoundedShortGrid
{
public:
	void store(int a, int b, short v);

private:
	unsigned char m_unknown00[0x08];
	int m_stride;
	unsigned char m_unknown0C[0x20 - 0x0C];
	int m_capacity;
	short *m_data;
};

// ?store@BoundedShortGrid@@QAEXHHF@Z
void BoundedShortGrid::store(int a, int b, short v)
{
	int idx = m_stride * b + a;
	if (idx < 0)
		return;
	if (idx >= m_capacity)
		return;
	if (!m_data)
		return;
	m_data[idx] = v;
}
