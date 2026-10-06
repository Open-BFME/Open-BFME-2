// ?rva003FC291@Rva003FC291@@QAEXM@Z
// partial score=0.6221 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva003FC291@Rva003FC291@@QAEXM@Z @0x003FC291 339B
// Sibling of 0x003FC149: this+8 delegate with matrix at +0x18 and scale at +0x48,
// this+0x14 second delegate, float at +0x7c; slot20 then Matrix3D copy, scale by f/scale, slot93+slot21.
// Evidence: same slots 0x50/0x54 as 0x003FC149; callers 0x00213718/0x005C4E8A; neighbours use /O1 /DNDEBUG /MD.
class Matrix3D
{
public:
	float m[12];
};
class Rva003FC291Target
{
public:
	virtual void _p00(); virtual void _p01(); virtual void _p02(); virtual void _p03();
	virtual void _p04(); virtual void _p05(); virtual void _p06(); virtual void _p07();
	virtual void _p08(); virtual void _p09(); virtual void _p10(); virtual void _p11();
	virtual void _p12(); virtual void _p13(); virtual void _p14(); virtual void _p15();
	virtual void _p16(); virtual void _p17(); virtual void _p18(); virtual void _p19();
	virtual void slot20();
	virtual void slot21(Matrix3D *m);
	virtual void _p22(); virtual void _p23(); virtual void _p24(); virtual void _p25();
	virtual void _p26(); virtual void _p27(); virtual void _p28(); virtual void _p29();
	virtual void _p30(); virtual void _p31(); virtual void _p32(); virtual void _p33();
	virtual void _p34(); virtual void _p35(); virtual void _p36(); virtual void _p37();
	virtual void _p38(); virtual void _p39(); virtual void _p40(); virtual void _p41();
	virtual void _p42(); virtual void _p43(); virtual void _p44(); virtual void _p45();
	virtual void _p46(); virtual void _p47(); virtual void _p48(); virtual void _p49();
	virtual void _p50(); virtual void _p51(); virtual void _p52(); virtual void _p53();
	virtual void _p54(); virtual void _p55(); virtual void _p56(); virtual void _p57();
	virtual void _p58(); virtual void _p59(); virtual void _p60(); virtual void _p61();
	virtual void _p62(); virtual void _p63(); virtual void _p64(); virtual void _p65();
	virtual void _p66(); virtual void _p67(); virtual void _p68(); virtual void _p69();
	virtual void _p70(); virtual void _p71(); virtual void _p72(); virtual void _p73();
	virtual void _p74(); virtual void _p75(); virtual void _p76(); virtual void _p77();
	virtual void _p78(); virtual void _p79(); virtual void _p80(); virtual void _p81();
	virtual void _p82(); virtual void _p83(); virtual void _p84(); virtual void _p85();
	virtual void _p86(); virtual void _p87(); virtual void _p88(); virtual void _p89();
	virtual void _p90(); virtual void _p91(); virtual void _p92();
	virtual void slot93(float f);
public:
	char m_pad04[20];
	Matrix3D m_mat;
	float m_scale;
};
class Rva003FC291
{
public:
	void rva003FC291(float f);
private:
	char m_pad00[8];
	Rva003FC291Target *m_08;
	char m_pad0C[8];
	Rva003FC291Target *m_14;
	char m_pad18[100];
	float m_7c;
};
// ?rva003FC291@Rva003FC291@@QAEXM@Z present-unmatched
void Rva003FC291::rva003FC291(float f)
{
	Rva003FC291Target *p = m_08;
	if (!p)
		return;
	m_7c = f;
	p->slot20();
	Matrix3D tm;
	tm.m[0] = p->m_mat.m[0];
	tm.m[1] = p->m_mat.m[1];
	tm.m[2] = p->m_mat.m[2];
	tm.m[3] = p->m_mat.m[3];
	tm.m[4] = p->m_mat.m[4];
	tm.m[5] = p->m_mat.m[5];
	tm.m[6] = p->m_mat.m[6];
	tm.m[7] = p->m_mat.m[7];
	tm.m[8] = p->m_mat.m[8];
	tm.m[9] = p->m_mat.m[9];
	tm.m[10] = p->m_mat.m[10];
	tm.m[11] = p->m_mat.m[11];
	float extra = f / m_08->m_scale;
	tm.m[0] *= extra;
	tm.m[1] *= extra;
	tm.m[2] *= extra;
	tm.m[4] *= extra;
	tm.m[5] *= extra;
	tm.m[6] *= extra;
	tm.m[8] *= extra;
	tm.m[9] *= extra;
	tm.m[10] *= extra;
	m_08->slot93(f);
	m_08->slot21(&tm);
	if (m_14) {
		m_14->slot93(f);
		m_14->slot21(&tm);
	}
}
