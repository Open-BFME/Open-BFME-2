// cl: /O1 /DNDEBUG /MD /EHsc /Oy- /G7
// ?rva00272C1E@Drawable@@QAE_NXZ retail 0x00272C1E 36 bytes.
// OR-accumulate slotDC over null-terminated Elem array at +0x14C. Evidence: same +0x14C walk as neighbours Drawable_rva00272BE7 0x00272BE7 and Drawable_rva0027267D 0x0027267D; prev 0x00272BE7 same flags.
class Elem
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
	virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
	virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
	virtual bool s55();
};
class Drawable
{
public:
	bool rva00272C1E();
private:
	unsigned char m_pad[0x14C];
	Elem **m_arr;
};

bool Drawable::rva00272C1E()
{
	Elem **pp = m_arr;
	bool acc = false;
	while (*pp != 0) {
		acc |= (*pp)->s55();
		++pp;
	}
	return acc;
}
