// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// ?rva00062A58@BoundedShortGrid@@QAEFHH@Z @ 0x00062A58 (38B). Load twin of
// ?store@BoundedShortGrid@@QAEXHHF@Z in BoundedShortGrid.cpp: returns
// m_data[m_stride * b + a] with identical bounds checks returning 0.
// Layout m_stride +0x08 m_capacity +0x20 m_data +0x24 proven by store.
// Same object serves both in 0x00091D61. Callers at 0x00063260 0x000673D7
// 0x00091D81. /O1 shares the single ret via jmp like retail.

class BoundedShortGrid
{
public:
	short rva00062A58(int a, int b);

private:
	unsigned char m_unknown00[0x08];
	int m_stride;
	unsigned char m_unknown0C[0x20 - 0x0C];
	int m_capacity;
	short *m_data;
};

short BoundedShortGrid::rva00062A58(int a, int b)
{
	int idx = m_stride * b + a;
	if (idx < 0)
		return 0;
	if (idx >= m_capacity)
		return 0;
	if (m_data)
		return m_data[idx];
	return 0;
}
