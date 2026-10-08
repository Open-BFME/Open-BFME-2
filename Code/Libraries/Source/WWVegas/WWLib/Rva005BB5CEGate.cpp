// cl: /MD /EHsc
// ?rva005BB5CE@Rva005BB5CEOwner@@QAE_NXZ @0x005BB5CE 40B: thiscall, no args, bool.
// Runs three gate predicates in order (rowed 0x005BA626, 0x005BA6EE and the address-named
// 0x005BB3A1); when all pass, sets the owner's byte flag at +0x78 to 1. Predicate
// meanings are address-derived views only.
class Rva005BA626 { public: bool rva005BA626(); };
class Rva005BA6EE { public: bool rva005BA6EE(); };
class Rva005BB3A1 { public: bool rva005BB3A1(); };

class Rva005BB5CEOwner
{
public:
	bool rva005BB5CE();
private:
	char pad00[0x78];
	unsigned char m_78;
};

bool Rva005BB5CEOwner::rva005BB5CE()
{
	bool r = ((Rva005BA626 *)this)->rva005BA626();
	if (r)
		r = ((Rva005BA6EE *)this)->rva005BA6EE();
	if (r)
		r = ((Rva005BB3A1 *)this)->rva005BB3A1();
	if (r)
		m_78 = 1;
	return r;
}
