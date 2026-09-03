// ?Resize@?$VectorClass@H@@UAE_NHPBH@Z
// partial score=0.99 date=2026-09-03
// ?Resize@?$VectorClass@H@@UAE_NHPBH@Z
// partial score=0.99 date=2026-09-03
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Westwood WWLib VectorClass<T>::Resize at 0x00002226, 141 bytes, for a
// four-byte T. Identity comes from the vftable at 0x007BB5AC whose six slots
// are the VectorClass shape - scalar deleting destructor at 0x0000232B,
// operator== at 0x000022B3, this body in slot 2, Clear at 0x004F0CD4 which
// slot 2 tail-calls through [eax+0x0C] when newsize is zero, and the two ID
// overloads at 0x000022E9 and 0x00002314.
//
// Three differences were banked here before. Two are now closed:
//
//   * the conditional move. cl 13.10 emits one only under /arch:SSE - no /G
//     or /O flag does it. The operand order decides the condition: written as
//     `newsize < VectorMax ? newsize : VectorMax` it is cmovge against
//     cmp ebx, eax, which is retail. The other three spellings give cmovg,
//     cmovle or the wrong compare direction.
//   * the allocator. `new T[n]` on a POD T reaches operator new at 0x0002FDA0
//     unless operator new[] is DECLARED in the translation unit, at which
//     point the front end binds the array form and calls 0x0002FDE0, which is
//     retail. The same declaration for operator delete[] fixes the matching
//     call in the release branch. Neither declaration needs a definition.
//
// ONE byte is left, at 0x6A. Retail materialises the null in a register -
//   33 c0             xor eax, eax
//   39 44 24 14       cmp [esp+0x14], eax
// where cl compares against the immediate in five bytes:
//   83 7c 24 14 00    cmp dword ptr [esp+0x14], 0
// The sete that follows only writes al and the byte store only reads al, so
// retail's xor is dead - it is a peephole, not a semantic difference.
// Refuted for it: naming the bool, the ?: form, an int cast, /Os (identical),
// and /Ot or /O2, which rewrite the whole body back to 137 differences.
//
// STILL OPEN: T itself. The element is a four-byte scalar copied with a plain
// dword move and allocated with shl eax, 2 and no array cookie, which fixes
// its size but not its name. The mangled name above is a placeholder.
void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *);

struct Element { int value; };

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass();
	virtual bool operator==(const VectorClass<T> &that) const;
	virtual bool Resize(int newsize, const T *array = 0);
	virtual void Clear();
	virtual int ID(const T *ptr);
	virtual int ID(const T &object);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};

template <class T>
bool VectorClass<T>::Resize(int newsize, const T *array)
{
	if (newsize != 0)
	{
		T *newptr;

		IsValid = false;
		if (array == 0)
		{
			newptr = new T[newsize];
		}
		else
		{
			newptr = (T *)array;
		}
		IsValid = true;
		if (newptr == 0)
		{
			return false;
		}

		if (Vector != 0)
		{
			const int copycount = newsize < VectorMax ? newsize : VectorMax;
			for (int index = 0; index < copycount; index++)
			{
				newptr[index] = Vector[index];
			}
			if (IsAllocated)
			{
				delete[] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (int)(array == 0) != 0;
	}
	else
	{
		Clear();
	}

	return true;
}

template class VectorClass<Element>;
