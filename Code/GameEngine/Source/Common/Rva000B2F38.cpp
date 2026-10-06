// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva000B2F38@Rva000B2F38@@QAE_NM@Z 0x000B2F38 131B evidence: iface at +0x50 slot3 int vs 0x19 slot47 ptr then int slot5 float slot6 with fild fmul fdivr plus BfmeZeroRange comiss divss store +0x9c bool return; callers at 0x000B3770/0x000B7104 unblocks 0x000B7074; neighbours 0x000B2D4D/0x000B304B same flags

class Rva000B2F38B;
class Rva000B2F38A
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual int s03();
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
	virtual void s44(); virtual void s45(); virtual void s46();
	virtual Rva000B2F38B *s47();
};

class Rva000B2F38B
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04();
	virtual int t05();
	virtual float t06();
};

class Rva000B2F38
{
	char _pad[0x50];
	Rva000B2F38A *m_a;
	char _fill[0x9c - 0x50 - 4];
	float m_f;
public:
	bool rva000B2F38(float v);
};

bool Rva000B2F38::rva000B2F38(float v)
{
	if (!m_a || m_a->s03() != 0x19)
		return false;
	Rva000B2F38B *b = m_a->s47();
	if (!b)
		return false;
	int n = b->t05();
	float f = (float)n * 1e+03f;
	float m = b->t06();
	float g = f / m;
	if (g > 0.0f && v > 0.0f)
	{
		m_f = g / v;
		return true;
	}
	return false;
}
