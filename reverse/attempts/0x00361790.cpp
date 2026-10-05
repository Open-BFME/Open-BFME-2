// ?Rva00361790@@YAHPAVRva00360F55@@@Z
// partial score=0.9528 date=2026-10-05
// ?Rva00361790@@YAHPAVRva00360F55@@@Z
// partial score=0.96 date=2026-10-05
// ?Rva00361790@@YAHPAVRva00360F55@@@Z
// partial score=0.96 date=2026-10-05 seat-14-r16 (trials F+G banked)
// cl: /O1 /DNDEBUG /MD
//
// ?Rva00361790@@YAHPAVRva00360F55@@@Z at 0x00361790 (135 bytes).
// Pool intern for the 0x94-byte ObjectFilter science-cluster record.
// LINEAGE: ShapeE (r15, guard+do-while, 0.96, 6B count/offset swap) base.
// Trial F (r16): ShapeE + unsigned int offset view (non-declaration lever).
//   Result: byte-identical to ShapeE outcome, same 6B swap (mov ebp,eax vs
//   ebx,eax; test ebp vs ebx; xor ebx vs ebp; lea [eax+ebx] vs [eax+ebp];
//   add ebx,edi vs ebp,edi; cmp esi,ebp vs esi,ebx; first diff +0x1B).
//   Unsigned view does NOT move the VC6 allocator.
// Trial G (r16, this file): ShapeE + distinct count-expression (byteCount
//   temp hoist, offset back to int to isolate count lever).
//   Result: same 6B swap, same first diff, 135B. Count-expression hoist
//   does NOT flip count/offset allocation either.
// RESIDUAL (6B): count/offset swapped ebp/ebx vs retail ebx/ebp. All pushes,
// stride=edi, index=esi, single jle, late offset-zero, calls (0x360E64,
// 0x361756), branches, immediates, sizes exact.
// NEXT (not decl-order: banned after r14; unsigned/count-expr now exhausted):
// try loop-induction rewrite (pointer-chase vs index/offset dual) or
// tail count-reuse elimination, each as single-lever trial.

struct BfmePod148
{
	int m_words[37];
};

namespace _STL
{
	template <class _Tp> class allocator
	{
	};
	template <class _Tp, class _Alloc> class vector
	{
	public:
		void push_back(const _Tp &value);
	};
}

class Rva00360F55
{
public:
	bool rva00360E64(const Rva00360F55 &other);

	char m_pad00[0x8C];
	int m_useCount;
	char m_pad90[0x94 - 0x90];
};

extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;

// ?Rva00361790@@YAHPAVRva00360F55@@@Z
int Rva00361790(Rva00360F55 *record)
{
	int byteCount = g_validityEnd - g_validityBegin;
	int count = byteCount / (int)sizeof(Rva00360F55);
	int index = 0;
	if (count > 0)
	{
		int offset = 0;
		do
		{
			Rva00360F55 *entry = (Rva00360F55 *)(g_validityBegin + offset);
			if (entry->rva00360E64(*record))
			{
				((Rva00360F55 *)(g_validityBegin + index * (int)sizeof(Rva00360F55)))->m_useCount++;
				return index;
			}
			++index;
			offset += (int)sizeof(Rva00360F55);
		} while (index < count);
	}
	record->m_useCount = 1;
	((_STL::vector<BfmePod148, _STL::allocator<BfmePod148> > *)&g_validityBegin)->push_back((const BfmePod148 &)*record);
	count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55);
	return count - 1;
}
