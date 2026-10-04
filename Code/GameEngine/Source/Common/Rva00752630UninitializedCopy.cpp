// cl: /O1 /DNDEBUG /MD
//
// ?Rva000791EDCopy@@YAPAVRva00752630@@PAV1@00@Z @0x000791ED 50B
// __uninitialized_copy for Rva00752630 (24B stride 0x18, rowed copy ctor
// ??0Rva00752630@@QAE@ABV0@@Z). Count via (last-first)/0x18 idiv, counted loop
// with copy ctor, returns final result. Evidence: push 0x18 cdq pop ecx idiv
// plus add 0x18 on both cursors plus copy ctor call; Rva00752630 size 24 from
// its matched copy TU; caller 0x0007942F; prev VslotMemberForwarders flags.
//

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);
private:
	void *m_item;
};

class Rva00752630
{
	BfmeSubA m_00;
	char m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
public:
	Rva00752630(const Rva00752630 &other);
};

inline void *__cdecl operator new(unsigned, void *p) throw()
{
	return p;
}

Rva00752630 *Rva000791EDCopy(Rva00752630 *first, Rva00752630 *last, Rva00752630 *result)
{
	int n = last - first;
	if (n > 0) {
		int count = n;
		do {
			__assume(result != 0);
			new (result) Rva00752630(*first);
			++first;
			++result;
			--count;
		} while (count != 0);
	}
	return result;
}
