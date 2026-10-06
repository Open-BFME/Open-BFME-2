// cl: /DNDEBUG /MD /EHsc
// ?rva002726C3@Drawable@@QAE_NHHHH@Z retail 0x002726C3 70 bytes.
// Scan null-terminated Elem array at +0x14C: e = elem->slotA8; if e then if e->slotAC(a,b,c,d) return true else next. Evidence: same +0x14C walk and slot 0xA8 as neighbour Drawable_rva0027267D 0x0027267D but second slot 0xAC; bool 4-arg shape as Drawable_rva00272835; prev 0x0027267D same flags.
class Sub
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
	virtual void s40(); virtual void s41(); virtual void s42();
	virtual bool s43(int a, int b, int c, int d);
};
class Elem
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03(); virtual void t04();
	virtual void t05(); virtual void t06(); virtual void t07(); virtual void t08(); virtual void t09();
	virtual void t10(); virtual void t11(); virtual void t12(); virtual void t13(); virtual void t14();
	virtual void t15(); virtual void t16(); virtual void t17(); virtual void t18(); virtual void t19();
	virtual void t20(); virtual void t21(); virtual void t22(); virtual void t23(); virtual void t24();
	virtual void t25(); virtual void t26(); virtual void t27(); virtual void t28(); virtual void t29();
	virtual void t30(); virtual void t31(); virtual void t32(); virtual void t33(); virtual void t34();
	virtual void t35(); virtual void t36(); virtual void t37(); virtual void t38(); virtual void t39();
	virtual void t40(); virtual void t41();
	virtual Sub *t42();
};
class Drawable
{
public:
	bool rva002726C3(int a, int b, int c, int d);
private:
	unsigned char m_pad[0x14C];
	Elem **m_arr;
};

bool Drawable::rva002726C3(int a, int b, int c, int d)
{
	Elem **pp = m_arr;
	while (*pp != 0) {
		Sub *e = (*pp)->t42();
		if (e != 0) {
			if (e->s43(a, b, c, d))
				return true;
		}
		++pp;
	}
	return false;
}
