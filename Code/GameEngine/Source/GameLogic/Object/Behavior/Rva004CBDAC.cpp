// cl: /DNDEBUG /MD
//
// ?rva004CBDAC@Rva004CBDAC@@QAE_NHPAURva002C99FB@@@Z, retail 0x004CBDAC, 35 bytes.
// Indexed 8-byte record fetch: base+idx*8 checked at +0xC (second half of the
// 8-byte Rva002C99FB at +8), false when zero; else assign the record at +8
// through rowed operator= 0x002C99FB into out and true. Layout stride 8 plus
// rowed callee from retail; honest owner unknown.
// Evidence: callee rowed 0x002C99FB; caller at 0x004CBDFA in 0x004CBDCF.
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

class Rva004CBDAC
{
public:
	bool rva004CBDAC(int idx, Rva002C99FB *out);
};

bool Rva004CBDAC::rva004CBDAC(int idx, Rva002C99FB *out)
{
	char *p = (char *)this + idx * 8;
	if (*(int *)(p + 0x0C) != 0) {
		*out = *(Rva002C99FB *)(p + 8);
		return true;
	}
	return false;
}
