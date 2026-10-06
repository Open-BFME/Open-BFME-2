// cl: /DNDEBUG /MD
// ?rva001D9A00@Rva001D9A00@@QAE_NXZ @0x001D9A00 79B unlock
// Same layout as sibling 0x001D98BD (+0xB0 type, +0x80/0x84 vector, +0x50/0x54
// +0x60/0x64 +0x70/0x74 vectors, +0x0C string). Case 2 checks the three
// pointer pairs, case 5 the +0x80 pair through its address, else the string
// non-empty via rowed isEmpty 0x00001E2F. Caller 0x0005D7A3.
// Neighbour FXBoneInfoAssign shares /O1 flags; no floats or EH.
template <typename T> class StringBase
{
public:
	bool isEmpty() const;
private:
	void *m_data;
};
struct VecPair
{
	void *beg;
	void *end;
};
class Rva001D9A00
{
public:
	bool rva001D9A00();
private:
	unsigned char m_pad00[0x0C];
	StringBase<char> m_str;
	unsigned char m_pad10[0x50 - 0x10];
	void *m_beg1;
	void *m_end1;
	unsigned char m_pad58[0x60 - 0x58];
	void *m_beg2;
	void *m_end2;
	unsigned char m_pad68[0x70 - 0x68];
	void *m_beg3;
	void *m_end3;
	unsigned char m_pad78[0x80 - 0x78];
	VecPair m_v4;
	unsigned char m_pad88[0xB0 - 0x88];
	int m_B0;
};

bool Rva001D9A00::rva001D9A00()
{
	switch (m_B0)
	{
	case 2:
		return m_beg1 != m_end1 || m_beg2 != m_end2 || m_beg3 != m_end3;
	case 5:
		{
			VecPair *v = &m_v4;
			return v->beg != v->end;
		}
	default:
		return !m_str.isEmpty();
	}
}
