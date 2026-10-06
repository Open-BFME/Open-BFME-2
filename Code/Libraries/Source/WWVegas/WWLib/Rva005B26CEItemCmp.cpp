// cl: /GX-
// stlport
// The E16 STLport family calls this thiscall comparator on 16-byte records.
// Its rowed stdcall twin compares the four dwords as nullness-ordered cells;
// the caller's record facade is four unsigned words.
struct Rva005B2FDCItem
{
	unsigned int w[4];
};

struct Rva005B26CEItemCmp
{
	bool operator()(const Rva005B2FDCItem &a, const Rva005B2FDCItem &b) const;
};

// ??RRva005B26CEItemCmp@@QBE_NABURva005B2FDCItem@@0@Z @0x005B26CE 53B
bool Rva005B26CEItemCmp::operator()(const Rva005B2FDCItem &a, const Rva005B2FDCItem &b) const
{
	for (int i = 0; i < 4; ++i) {
		unsigned int av = a.w[i];
		unsigned int bv = b.w[i];
		if (av != 0 && bv == 0)
			return true;
		if (av == 0 && bv != 0)
			return false;
	}
	return true;
}
