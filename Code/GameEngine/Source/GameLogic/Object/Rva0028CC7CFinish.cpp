// ?rva0028CC7C@Object@@QAE_NH@Z
// cl: /MD
// ?rva0028CC7C@Object@@QAE_NH@Z @0x0028CC7C 61B
// Object containedBy-gated inner check: cont = m_contained274; inner = cont provider slot31 or 0; if null return true else inner slot84(this param).
// Evidence: +0x274 containedBy plus +0x250 provider both per Object_isAbleToAttack; slots 0x7C and 0x150; ret 4 bool via al;
// caller 0x00295BD5; neighbours Rva004DF7C2Derived and ObjectRva0028D481 give /O1 /MD flags.
class Object;

class Rva0028CC7CInner
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual bool slot84(Object *outer, int key);
};

class Rva0028CC7CProvider
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30();
	virtual Rva0028CC7CInner *slot31();
};

class Object
{
public:
	bool rva0028CC7C(int key);

private:
	char m_pad00[0x250];
	Rva0028CC7CProvider *m_provider250; // +0x250
	char m_pad254[0x274 - 0x254];
	Object *m_contained274; // +0x274 containedBy per Object_isAbleToAttack
};

bool Object::rva0028CC7C(int key)
{
	if (m_contained274 != 0) {
		Rva0028CC7CProvider *prov = m_contained274->m_provider250;
		Rva0028CC7CInner *inner = prov != 0 ? prov->slot31() : 0;
		if (inner != 0) {
			if (!inner->slot84(this, key))
				return false;
		}
	}
	return true;
}
