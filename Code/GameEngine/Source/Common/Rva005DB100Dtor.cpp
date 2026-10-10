// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ??1Rva005DB100@@UAE@XZ @0x005DB100 69B
// retail 0x005DB100 69 bytes unlock dtor vtable 0x008766A4 plus ReleaseTreeHintRef at +0x38+0xAC
// via rowed Release 0x0007DEEF and rowed base dtor 0x0039AD56 caller deleting dtor 0x005DB1EB
// neighbours prev 0x005DB023 Chain and next 0x005DB82B Disp0 setters

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva005DB100Mid { char m_pad[172]; TargetRef00217D4C m_hint; };

class Rva0039AD56
{
public:
	virtual ~Rva0039AD56();
};

class Rva005DB100 : public Rva0039AD56
{
public:
	virtual ~Rva005DB100();
private:
	char m_pad04[52];
	Rva005DB100Mid *m_38;
};

Rva005DB100::~Rva005DB100()
{
	if (m_38)
		ReleaseTreeHintRef00217D4C(&m_38->m_hint);
}

// Native5DB145..5DB1E8,163B: inherited input update with local128B bitset.
// Input pointer range4C/50 and each nonnull entry id38 are native accesses;
// writes are committed to holder38+10 and countFC>1 sets byte20.
// Native repeats the range loads across each bit write. Nonemitting barriers
// retain that access order, and the unsigned index guard retains the SAR.
// Original owner and input identities remain address-derived.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// Evidence: chain from landed 0x39B2E6; input array +0x4c/+0x50 of elems with
// id at +0x38 accumulates bits into 128B local via rowed BfmeFixedStorage128
// copy 0x4548B then rep movsd writeback to holder at +0x38+0x10; +0xfc>1 sets
// flag at +0x20; tail calls rowed 0x39B2E6 on input; second arg unread.
struct Rva0039B2E6Input;

class Rva0039B2E6
{
public:
	void rva0039B2E6(const struct Rva0039B2E6Input &input);
};

struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);
	unsigned int m_w[32];
};

struct Db145Holder
{
	char m_pad00[0x10];
	BfmeFixedStorage128 m_stor10;
};

struct Db145Elem
{
	char m_pad00[0x38];
	unsigned int m_val38;
};

struct Db145Input
{
	char m_pad00[0x10];
	unsigned char m_str10[4];
	char m_pad14[0x1C - 0x14];
	int m_1C;
	int m_20;
	char m_pad24[0x4C - 0x24];
	Db145Elem **m_begin4C;
	Db145Elem **m_end50;
	char m_pad54[0xFC - 0x54];
	int m_cntFC;
};

class Rva005DB145
{
public:
	void rva005DB145(const struct Rva0039B2E6Input &input, int);
private:
	char m_pad00[8];
	unsigned char m_str08[4];
	int m_key0C;
	char m_pad10[0x20 - 0x10];
	bool m_flag20;
	char m_pad21[0x38 - 0x21];
	Db145Holder *m_holder38;
};

void Rva005DB145::rva005DB145(const struct Rva0039B2E6Input &input, int)
{
	const Db145Input *in = (const Db145Input *)&input;
	if (in->m_begin4C != in->m_end50) {
		BfmeFixedStorage128 bits(m_holder38->m_stor10);
		unsigned int i = 0;
		if (i < (unsigned)(in->m_end50 - in->m_begin4C)) {
			_ReadWriteBarrier();
			Db145Elem **pp = (Db145Elem **)in->m_begin4C;
			do {
				Db145Elem *e = *pp;
				if (e != 0) {
					unsigned int v = e->m_val38;
					bits.m_w[v >> 5] |= (1u << (v & 31));
				}
				_ReadWriteBarrier();
				++i;
				++pp;
			} while (i < (unsigned)(in->m_end50 - in->m_begin4C));
		}
		m_holder38->m_stor10 = bits;
	}
	if (in->m_cntFC > 1)
		m_flag20 = true;
	((Rva0039B2E6 *)this)->rva0039B2E6(input);
}
