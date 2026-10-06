// cl: /MD
// ?rva002CFD61@Rva002CFD61@@QAEXPAURva002CFD61Node@@@Z @0x002CFD61 53B.
// Tree erase with string cleanup: recurse right via +0xC, clear AsciiString
// at +0x10 via rowed 0x0048BA39, free node via rowed _free 0x00030830,
// walk left via +0x8, ret 4. Same 53B shape as the rowed AsciiString-set
// erase 0x00056CC3. Caller at 0x002D030B unblocks 0x002D02FD.
template <typename T>
class StringBase
{
public:
	void clear();
};

typedef StringBase<char> AsciiString;

extern "C" void __cdecl free(void *block);

struct Rva002CFD61Node
{
	unsigned char m_pad00[8];
	Rva002CFD61Node *m_left;
	Rva002CFD61Node *m_right;
	AsciiString m_value;
};

struct Rva002CFD61
{
	void rva002CFD61(Rva002CFD61Node *x);
};

void Rva002CFD61::rva002CFD61(Rva002CFD61Node *x)
{
	while (x != 0) {
		rva002CFD61(x->m_right);
		Rva002CFD61Node *y = x->m_left;
		x->m_value.clear();
		free(x);
		x = y;
	}
}
