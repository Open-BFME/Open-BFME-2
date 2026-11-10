// cl: /MD
//
// ?rva0056AA32@Rva0056AA32@@QAEHPBVRva004E0625@@@Z @0x0056AA32 34B.
// Guarded equality: 0 when the +0x10 count is zero, else whether the rowed
// const 0x004E0625 query equals it (nested if shares one false target).
#include "../../Include/Common/Rva004E0625.h"

class Rva0056AA32
{
public:
	int rva0056AA32(const Rva004E0625 *arg);
private:
	char m_pad[0x10];
	int m_10;	// +0x10
};

int Rva0056AA32::rva0056AA32(const Rva004E0625 *arg)
{
	if (m_10 != 0) {
		if (arg->rva004E0625() == m_10)
			return 1;
	}
	return 0;
}

// Native56AAF4/21 and WB14462E0 compare the opaque resolver bits to
// receiver1C. Native56AABF/53 and WB1446280 choose the two owned
// manager268 callbacks by the same comparison against receiver08.
// Names and prefix views preserve original object and field uncertainty.
class Rva00318FA1MainOwner {public:int rva00318FA1();};
class Rva0056AAF4 {public:int rva0056AAF4();private:char unknown00[0x18];Rva00318FA1MainOwner *owner18;int bits1C;};
int Rva0056AAF4::rva0056AAF4(){return owner18->rva00318FA1()==bits1C;}
class Rva003EE966 {public:void rva003EE966(int);};
class Rva003EE91A {public:void rva003EE91A(int);};
class LivingWorldManager;extern LivingWorldManager *TheLivingWorldManager;
struct Manager268View {char unknown00[0x268];void *word268;};
class Rva0056AABF {public:void rva0056AABF(Rva00318FA1MainOwner *);private:char unknown00[8];int bits08;};
void Rva0056AABF::rva0056AABF(Rva00318FA1MainOwner *arg){
 void *target=((Manager268View*)TheLivingWorldManager)->word268;
 if(target){int bits=bits08;if(arg->rva00318FA1()==bits) ((Rva003EE966*)target)->rva003EE966(bits);else ((Rva003EE91A*)target)->rva003EE91A(bits);}
}

struct Rva0056A9F4Arg
{
	char m_pad[0x2C];
	int m_2C;
};

class Rva0056A9F4
{
public:
	void rva0056A9F4(int a, const Rva0056A9F4Arg *b);
private:
	int m_00;
	int m_04;
	int m_08;
	unsigned char m_0C;
};

// ?rva0056A9F4@Rva0056A9F4@@QAEXHPBURva0056A9F4Arg@@@Z @0x0056A9F4 (28B)
void Rva0056A9F4::rva0056A9F4(int a, const Rva0056A9F4Arg *b)
{
	if (m_04 == a && m_08 == b->m_2C)
		m_0C = 1;
}

class Rva0056AA22
{
public:
	void rva0056AA22(int a, int b);
private:
	int m_00;
	int m_04;
	int m_08;
	unsigned char m_0C;
};

// ?rva0056AA22@Rva0056AA22@@QAEXHH@Z @0x0056AA22 (16B)
void Rva0056AA22::rva0056AA22(int a, int)
{
	if (m_04 == a)
		m_0C = 1;
}

class Rva0056AAA6
{
public:
	void rva0056AAA6(int a, int b);
private:
	int m_00;
	int m_04;
	int m_08;
	unsigned char m_0C;
};

// ?rva0056AAA6@Rva0056AAA6@@QAEXHH@Z @0x0056AAA6 (25B)
void Rva0056AAA6::rva0056AAA6(int a, int b)
{
	if (m_04 == b && m_08 == a)
		m_0C = 1;
}
