// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004F9E59@Rva004F9E59@@QAEXXZ @0x004F9E59 29B.
// Dual-range sort: call the canonical thiscall sorter0x004F9635 through
// the native receiver. Rva004F9E59 remains an opaque existing receiver view.
// over the 12-byte records at +0x0C and +0x18. The push-2/pop-ebx counter
// idiom is what the retail loop uses.
struct Rva004F9635Rec;

class LivingWorldAutoResolveBattle {public: void rva004F9635(Rva004F9635Rec *);};

class Rva004F9E59
{
public:
	void rva004F9E59();
};

void Rva004F9E59::rva004F9E59()
{
	Rva004F9635Rec *r = (Rva004F9635Rec *)((char *)this + 0x0C);
	int n = 2;
	do {
		reinterpret_cast<LivingWorldAutoResolveBattle *>(this)->rva004F9635(r);
		r = (Rva004F9635Rec *)((char *)r + 0x0C);
		--n;
	} while (n != 0);
}
