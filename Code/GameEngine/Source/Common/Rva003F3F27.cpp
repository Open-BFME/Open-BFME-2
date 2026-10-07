// cl: /O1 /MD
//
// ?rva003F3F27@Rva003F3F27@@QAEXXZ @0x003F3F27 85B.
// Multi-clear tail on the same TU object as 0x003F3F03: run the rowed
// ScienceType-vector clear at 0x003F20B0, three unclaimed no-arg/one-arg
// members, zero the +0x17c word, run the +0x1A8 subobject method with the
// +0x60 block address while clearing the +0x1A3 byte, run the range-19
// 0x003F3B4F member, then zero the +0x134/+0x138 words.
// Evidence: retail push esi / mov esi,ecx / call 0x003F20B0 / push -1 /
// call 0x003F1AFF / push 1 / call 0x003EFDF5 / call 0x003F2106 /
// and [esi+0x17c],0 / lea eax,[esi+0x60] / push eax /
// lea ecx,[esi+0x1a8] / mov byte [esi+0x1a3],0 / call 0x003F318C /
// call 0x003F3B4F / and [esi+0x134],0 / and [esi+0x138],0 / pop esi / ret.
class Rva003F3F27Sub1A8
{
public:
	void rva003F318C(void *block);
};

class Rva003F3F27
{
public:
	void rva003F3F27();
	void rva003F20B0();
	void rva003F1AFF(int n);
	void rva003FEFDF5(int n);
	void rva003F2106();
	void rva003F3B4F();
private:
	char m_pad00[0x60];
	int m_60marker;
	char m_pad64[0xD0];
	int m_134;
	int m_138;
	char m_pad13C[0x40];
	int m_17c;
	char m_pad180[0x23];
	char m_1a3;
	char m_pad1A4[4];
	Rva003F3F27Sub1A8 m_1a8;
};

void Rva003F3F27::rva003F3F27()
{
	rva003F20B0();
	rva003F1AFF(-1);
	rva003FEFDF5(1);
	rva003F2106();
	m_17c = 0;
	m_1a3 = 0;
	m_1a8.rva003F318C(&m_60marker);
	rva003F3B4F();
	m_134 = 0;
	m_138 = 0;
}
