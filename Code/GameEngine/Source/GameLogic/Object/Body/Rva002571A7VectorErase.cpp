// cl: /MD /DNDEBUG /EHsc
//
// ?erase@Rva002571A7Vector@@QAEPAURva002571A7Elem@@PAU2@0@Z, retail 0x002571A7, 54 bytes.
// Inline 8-byte POD range-erase (count via sar 3, two-dword copy loop, no
// _Destroy call): shifts [last, finish) down to first, stores the new
// finish and returns first. Called to clear the +0xC8 vector by the
// ActivateModuleSpecialPowerModuleData dtor at 0x0025714A. Element is an
// honest 8-byte POD (stride is all retail observes); the Rva name claims
// only the address plus the 8-byte stride.
struct Rva002571A7Elem
{
	int m_a;
	int m_b;
};

class Rva002571A7Vector
{
public:
	Rva002571A7Elem *erase(Rva002571A7Elem *first, Rva002571A7Elem *last);

private:
	Rva002571A7Elem *m_begin;
	Rva002571A7Elem *m_finish;
	Rva002571A7Elem *m_end;
};

Rva002571A7Elem *Rva002571A7Vector::erase(Rva002571A7Elem *first, Rva002571A7Elem *last)
{
	Rva002571A7Elem *source = last;
	Rva002571A7Elem *dest = first;
	int count = m_finish - last;
	if (count > 0)
	{
		do
		{
			dest->m_a = source->m_a;
			dest->m_b = source->m_b;
			++source;
			++dest;
			--count;
		} while (count != 0);
	}
	m_finish = dest;
	return first;
}
