// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// Westwood WWLib VectorClass<T>::Resize at 0x00002226, 141 bytes, for a
// four-byte T. Identity comes from the vftable at 0x007BB5AC whose six slots
// are the VectorClass shape - scalar deleting destructor at 0x0000232B,
// operator== at 0x000022B3, this body in slot 2, Clear at 0x004F0CD4 which
// slot 2 tail-calls through [eax+0x0C] when newsize is zero, and the two ID
// overloads at 0x000022E9 and 0x00002314.
//
// The body is Vector.H verbatim, placement-new branch included. Three
// things about it are not obvious:
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
//   * the last statement, which is what the earlier banks were stuck on.
//     Retail materialises the null into a register before the test -
//       33 c0             xor eax, eax
//       39 44 24 14       cmp [esp+0x14], eax
//     where every spelling of `array == 0` gives the shorter immediate form
//       83 7c 24 14 00    cmp dword ptr [esp+0x14], 0
//     and no flag moves it - /G7, /arch:SSE2, /Og, /Gy, /Oi and /Os are all
//     identical here, /Ot and /O2 rewrite the whole body. It is not a
//     peephole. Vector.H does not test `array == 0`, it tests
//     `Vector && !array`, and although cl folds the left operand away (Vector
//     is newptr, which the early return already proved non-null) the zeroed
//     register the conjunction set up survives into the compare. Restoring
//     the real conjunction closes the body exactly.
//
// T itself is a four-byte scalar copied with a plain dword move and allocated
// with shl eax, 2 and no array cookie, which fixes its size but not its name;
// int is the representative instantiation and any four-byte POD emits these
// same bytes.

void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *);
inline void *__cdecl operator new[](unsigned int, void *p) { return p; }

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass();
	virtual bool operator==(const VectorClass<T> &that) const;
	virtual bool Resize(int newsize, T const *array = 0);
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
VectorClass<T>::~VectorClass()
{
	Clear();
}

template <class T>
void VectorClass<T>::Clear()
{
	if (Vector != 0 && IsAllocated) {
		delete [] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template <class T>
bool VectorClass<T>::Resize(int newsize, T const *array)
{
	if (newsize) {

		T *newptr;

		IsValid = false;
		if (!array) {
			newptr = new T[newsize];
		} else {
			newptr = new((void *)array) T[newsize];
		}
		IsValid = true;
		if (!newptr) {
			return(false);
		}

		if (Vector != 0) {

			int copycount = (newsize < VectorMax) ? newsize : VectorMax;
			for (int index = 0; index < copycount; index++) {
				newptr[index] = Vector[index];
			}

			if (IsAllocated) {
				delete[] Vector;
				Vector = 0;
			}
		}

		Vector = newptr;
		VectorMax = newsize;
		IsAllocated = (Vector && !array);

	} else {

		Clear();
	}
	return(true);
}

template <class T>
int VectorClass<T>::ID(T const &object)
{
	if (!IsValid) return 0;
	for (int index = 0; index < VectorMax; ++index) {
		if (Vector[index] == object) return index;
	}
	return -1;
}

template <class T>
int VectorClass<T>::ID(T const *ptr)
{
	if (!IsValid) return 0;
	return (reinterpret_cast<unsigned long>(ptr) -
		reinterpret_cast<unsigned long>(Vector)) / sizeof(T);
}

template <class T>
bool VectorClass<T>::operator==(VectorClass<T> const &that) const
{
	if (VectorMax == that.VectorMax) {
		for (int index = 0; index < VectorMax; ++index) {
			if (Vector[index] != that.Vector[index]) return false;
		}
		return true;
	}
	return false;
}

template class VectorClass<int>;
