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
// Row spellings of the callees: 0x003F318C is vector<Rva003F318CRecord>::
// operator= (the +0x1A8 vector assigned from the +0x60 one), and 0x003F20B0,
// 0x003F1AFF and 0x003EFDF5 are rowed on their own address-named views.
struct Rva003F318CRecord;
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	vector &operator=(const vector &other);
};
}
typedef _STL::vector<Rva003F318CRecord, _STL::allocator<Rva003F318CRecord> > Rva003F318CVector;
class Rva003F3F27Sub1A8
{
};
class Rva003F20B0 { public: void rva003F20B0(); };
#include "../../Include/Common/Rva003F1AFF.h"
#include "../../../Libraries/Source/WWVegas/WWLib/Rva003EFDF5Host.h"

// 0x003F2106 is rowed as Rva003F2106::rva003F2106 (Rva002B7B71DeleteAll.cpp).
#include "../../Include/Common/Rva003F2106.h"

class Rva003F3F27
{
public:
	void rva003F3F27();
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
	((Rva003F20B0 *)this)->rva003F20B0();
	((Rva003F1AFF *)this)->rva003F1AFF(-1);
	((Rva003EFDF5Host *)this)->rva003EFDF5((void *)1);
	((Rva003F2106 *)this)->rva003F2106();
	m_17c = 0;
	m_1a3 = 0;
	*(Rva003F318CVector *)&m_1a8 = *(const Rva003F318CVector *)&m_60marker;
	rva003F3B4F();
	m_134 = 0;
	m_138 = 0;
}
