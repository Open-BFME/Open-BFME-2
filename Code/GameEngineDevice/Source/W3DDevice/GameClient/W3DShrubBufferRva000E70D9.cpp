// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// W3DShrubBuffer method at retail 0x000E70D9 (103 bytes, ret 4). Open-BFME-1 twin: W3DShrubBuffer_resetMatchingRow.cpp
// (0x0071C940). BFME2 layout read from retail: record stride 0xA0 with the cursor parked 8 bytes into the row
// (+0x1960 so the first three floats land at -8/-4/0), key at row+0x50, count at +0x4FB58, dirty byte at +0x4FB5C.
// The BFME2 build clears the position and fade fields as floats.

typedef int Int;
typedef float Real;

class W3DShrubBuffer
{
public:
	void rva000E70D9(Int key);

private:
	char m_pad[0x4FB58];
	Int m_count;
	unsigned char m_dirty;
};

void W3DShrubBuffer::rva000E70D9(Int key)
{
	Int i = 0;
	if (m_count > 0)
	{
		char *row = (char *)this + 0x1960;
		do
		{
			if (*(Int *)(row + 0x50) == key)
			{
				*(Real *)(row - 8) = 0;
				*(Real *)(row - 4) = 0;
				*(Real *)row = 0;
				*(Int *)(row + 0x38) = -2;
				*(Real *)(row + 0x40) = 0;
				*(Real *)(row + 0x44) = 0;
				*(Real *)(row + 0x48) = 0;
				*(Real *)(row + 0x4C) = 1.0f;
				m_dirty = 1;
			}
			++i;
			row += 0xA0;
		} while (i < m_count);
	}
}
