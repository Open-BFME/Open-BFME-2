// cl: /O1 /arch:SSE /G7 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// ??0Rva00502A02@@QAE@AAHABURva00502909Sub@@@Z, retail 0x00502A02 29B.
// Owner-like ctor: int at +0 from *a1, Sub at +4 copy-constructed from *a2
// via rowed 0x005026EE. Evidence: same int-plus-Sub layout as
// Rva00502909Owner read family in RvaReadThroughFamily.cpp and rowed Sub copy
// ctor callee; frameless 29B ret-8 shape matches that family.
struct Rva00501656
{
	Rva00501656(const Rva00501656 &o);
};

class Rva00502A02
{
public:
	Rva00502A02(int &a, const Rva00501656 &b);

private:
	int m_00;
	Rva00501656 m_04;
};

Rva00502A02::Rva00502A02(int &a, const Rva00501656 &b)
	: m_00(a)
	, m_04(b)
{
}
