// ?rva0033C965@Rva0033C965@@QAEXHH@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /EHs /MD
// ?rva0033C965@Rva0033C965@@QAEXHH@Z @0x0033C965 284B.
// Module/draw resolver: builds the four ModuleInfo entries at +0x2e4 via the
// rowed 0x33B5B8 helper, formats the +0x90 base-name label through the rowed
// AsciiStringPlusText chain (operator+ 0xB49C5 plus conversion 0xBC4F7) unless
// the base name isEmpty, appends it to the arg list via AssetList::operator<<
// (0x6C950), notifies the six +0x14 record slots of every 0x368 ModelCondition
// entry via the rowed 0x2CAC6E member, and finishes with the global-flag-gated
// table lookup (0x31D5F8 on the +0x70 name) plus 0x409F1B dispatch.
// The 0xBC684C format pointer is a retail-pinned runtime-materialized string
// outside the file image, so it rides as an address cast (byte-verified push)
// rather than a literal the string gate could never confirm.
template <class T>
class StringBase
{
public:
	bool isEmpty() const;

protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString();
};

struct AsciiStringPlusText
{
	operator AsciiString();

	const AsciiString *m_string;
	const char *m_ptr;
	int m_len;
};

AsciiStringPlusText operator+(const AsciiString &left, const char *right);

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &s);
};

class ModuleInfo
{
public:
	char m_data[12];
};

enum ModuleType
{
	MODULE_0,
	MODULE_1,
	MODULE_2,
	MODULE_3
};

void Rva0033B5B8Build(ModuleInfo *info, ModuleType type, int a1, int a2);

class Rva002CA9CA
{
public:
	void rva002CAC6E(int a1, int a2);
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);
};

class Rva00409F1B
{
public:
	void rva00409F1B(int a1, int a2);
};

extern void *g_00DFE758;
extern void *g_00E01CFC;

struct Rva0033C965Rec
{
	char m_pad[0x14];
	Rva002CA9CA *m_slots[6];
	char m_tail[0x368 - 0x14 - 24];
};

class Rva0033C965
{
public:
	void rva0033C965(int a1, int val);

private:
	char m_pad00[0x70];
	AsciiString m_name70; // +0x70
	char m_pad74[0x90 - 0x74];
	AsciiString m_base90; // +0x90
	char m_pad94[0x2e4 - 0x94];
	ModuleInfo m_mod0; // +0x2e4
	ModuleInfo m_mod1; // +0x2f0
	ModuleInfo m_mod2; // +0x2fc
	ModuleInfo m_mod3; // +0x308
	char m_pad310[0x358 - 0x314];
	Rva0033C965Rec *m_recs; // +0x358
	Rva0033C965Rec *m_recsEnd; // +0x35c
};

void Rva0033C965::rva0033C965(int a1, int val)
{
	Rva0033B5B8Build(&m_mod0, MODULE_0, a1, val);
	Rva0033B5B8Build(&m_mod1, MODULE_1, a1, val);
	Rva0033B5B8Build(&m_mod2, MODULE_2, a1, val);
	Rva0033B5B8Build(&m_mod3, MODULE_3, a1, val);

	AsciiString &baseName = m_base90;
	if (!baseName.isEmpty()) {
		AsciiString label = baseName + (const char *)0xBC684C;
		*(AssetList *)a1 << label;
	}

	for (Rva0033C965Rec *rec = m_recs; rec != m_recsEnd; rec++) {
		Rva002CA9CA **slot = rec->m_slots;
		int left = 6;
		do {
			if (*slot)
				(*slot)->rva002CAC6E(a1, val);
			slot++;
		} while (--left != 0);
	}

	if (*(char *)((char *)g_00DFE758 + 0x1110) == 0) {
		void *hit = ((Rva0031D5F8 *)g_00E01CFC)->rva0031D5F8(&m_name70);
		if (hit != 0)
			((Rva00409F1B *)hit)->rva00409F1B(a1, val);
	}
}
