// cl: /DNDEBUG /MD
//
// ?rva003FC3E4@Rva003FC3E4@@QAEXXZ @0x003FC3E4 (68B):
// Mesh texture reset walk: if +0x8 collection set take count via slot28;
// for each index take element via slot30 and unless null take material via
// slot85 and unless null call rowed Reset_Texture_Mappers.
// Evidence: rowed Reset_Texture_Mappers 0x00184010; caller 0x005392DE;
// unblocks 0x005392C2; neighbours use /O1 /DNDEBUG /MD.
class MaterialInfoClass
{
public:
	void Reset_Texture_Mappers();
};
class Rva003FC3E4ObjB
{
public:
	virtual void _p00(); virtual void _p01(); virtual void _p02(); virtual void _p03();
	virtual void _p04(); virtual void _p05(); virtual void _p06(); virtual void _p07();
	virtual void _p08(); virtual void _p09(); virtual void _p10(); virtual void _p11();
	virtual void _p12(); virtual void _p13(); virtual void _p14(); virtual void _p15();
	virtual void _p16(); virtual void _p17(); virtual void _p18(); virtual void _p19();
	virtual void _p20(); virtual void _p21(); virtual void _p22(); virtual void _p23();
	virtual void _p24(); virtual void _p25(); virtual void _p26(); virtual void _p27();
	virtual void _p28(); virtual void _p29(); virtual void _p30(); virtual void _p31();
	virtual void _p32(); virtual void _p33(); virtual void _p34(); virtual void _p35();
	virtual void _p36(); virtual void _p37(); virtual void _p38(); virtual void _p39();
	virtual void _p40(); virtual void _p41(); virtual void _p42(); virtual void _p43();
	virtual void _p44(); virtual void _p45(); virtual void _p46(); virtual void _p47();
	virtual void _p48(); virtual void _p49(); virtual void _p50(); virtual void _p51();
	virtual void _p52(); virtual void _p53(); virtual void _p54(); virtual void _p55();
	virtual void _p56(); virtual void _p57(); virtual void _p58(); virtual void _p59();
	virtual void _p60(); virtual void _p61(); virtual void _p62(); virtual void _p63();
	virtual void _p64(); virtual void _p65(); virtual void _p66(); virtual void _p67();
	virtual void _p68(); virtual void _p69(); virtual void _p70(); virtual void _p71();
	virtual void _p72(); virtual void _p73(); virtual void _p74(); virtual void _p75();
	virtual void _p76(); virtual void _p77(); virtual void _p78(); virtual void _p79();
	virtual void _p80(); virtual void _p81(); virtual void _p82(); virtual void _p83();
	virtual void _p84();
	virtual MaterialInfoClass *v85();
};
class Rva003FC3E4ObjA
{
public:
	virtual void _q00(); virtual void _q01(); virtual void _q02(); virtual void _q03();
	virtual void _q04(); virtual void _q05(); virtual void _q06(); virtual void _q07();
	virtual void _q08(); virtual void _q09(); virtual void _q10(); virtual void _q11();
	virtual void _q12(); virtual void _q13(); virtual void _q14(); virtual void _q15();
	virtual void _q16(); virtual void _q17(); virtual void _q18(); virtual void _q19();
	virtual void _q20(); virtual void _q21(); virtual void _q22(); virtual void _q23();
	virtual void _q24(); virtual void _q25(); virtual void _q26(); virtual void _q27();
	virtual int v28();
	virtual void _q29();
	virtual Rva003FC3E4ObjB *v30(int index);
};
class Rva003FC3E4
{
public:
	void rva003FC3E4();
private:
	char m_pad00[8];
	Rva003FC3E4ObjA *m_08;
};
void Rva003FC3E4::rva003FC3E4()
{
	Rva003FC3E4ObjA *a = m_08;
	if (a == 0)
		return;
	int n = a->v28();
	for (int i = 0; i < n; ++i) {
		Rva003FC3E4ObjB *o = m_08->v30(i);
		if (o == 0)
			continue;
		MaterialInfoClass *m = o->v85();
		if (m == 0)
			continue;
		m->Reset_Texture_Mappers();
	}
}
