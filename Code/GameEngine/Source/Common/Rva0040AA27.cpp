// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
//
// ?rva0040AA27@Rva0040AA27@@QAEHH@Z @0x0040AA27 76B.
// All-quantifier over the +0x1c/+0x20 array (0x10 stride): run the 0x40A99A
// predicate (unclaimed, address pinned) on each element with our int arg,
// stop at the first false, then require a non-empty full count.
// Evidence: retail push ebx/ebp/esi/edi / esi=this / edi=[esi+0x1c] /
// ebp=0 / bl=0 / loop cmp edi,[esi+0x20] / push [esp+0x14] / ecx=edi /
// call 0x40A99A / test al / je→bl=1 else ebp++ / edi+=0x10 / test bl /
// je loop / test ebp / jbe false / eax=([esi+0x20]-[esi+0x1c])>>4 /
// cmp ebp,eax / jne false / eax=1 / false: eax=0 / pop regs / ret 4.
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0, FORCE_NAMEKEYTYPE_LONG=0x7fffffff };
class NameKeyGenerator { public: const AsciiString &keyToName(NameKeyType); };
extern NameKeyGenerator *TheNameKeyGenerator;
class CreateAHeroData { public: bool rva004080DD(const AsciiString&, unsigned int*); };
class Rva0040A7D5 { public: int rva0040A7D5(int) const; };

class Rva0040A99AElem
{
public:
	bool rva0040A99A(int x);
private:
	int *m_begin, *m_end, *m_capacity;
	int m_required;
};

class Rva0040AA27
{
public:
	int rva0040AA27(int x);
private:
	char m_pad00[0x1c];
	Rva0040A99AElem *m_begin1c;
	Rva0040A99AElem *m_end20;
};

int Rva0040AA27::rva0040AA27(int x)
{
	Rva0040A99AElem *p = m_begin1c;
	unsigned count = 0;
	bool stop = false;
loop:
	if (p == m_end20)
		goto done;
	if (p->rva0040A99A(x))
		count++;
	else
		stop = true;
	p++;
	if (!stop)
		goto loop;
done:
	if (count > 0 && count == (unsigned)(m_end20 - m_begin1c))
		return 1;
	return 0;
}

// Retail 0040A99A..0040AA27: sum unlocked amounts keyed by the array
// entries and compare with the signed threshold at +0x0C. The neighboring
// array predicate passes the context as an opaque word; its receiver at
// 004080DD identifies CreateAHeroData independently. No donor class name
// or original element name is asserted. Four-byte entries are interned keys.
bool Rva0040A99AElem::rva0040A99A(int context)
{
	int total = 0;
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i) {
		unsigned int amount = 0;
		AsciiString name = TheNameKeyGenerator->keyToName(
			(NameKeyType)((const Rva0040A7D5 *)this)->rva0040A7D5(i));
		if (((CreateAHeroData *)context)->rva004080DD(name, &amount))
			total += amount;
	}
	return total >= m_required;
}
