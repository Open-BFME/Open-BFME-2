// ?Resize@?$VectorClass@H@@UAE_NHPBH@Z
// partial score=0.98 date=2026-09-02
// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// Westwood WWLib VectorClass<T>::Resize at 0x00002226, 141 bytes, for a
// four-byte T.  Identity comes from the vftable at 0x007BB5AC, whose six slots
// are exactly the VectorClass shape - scalar deleting destructor at
// 0x0000232B, operator== at 0x000022B3, this body in slot 2, Clear at
// 0x004F0CD4 (which slot 2 tail-calls through [eax+0x0C] when newsize is
// zero), and the two ID overloads at 0x000022E9 and 0x00002314.
//
// Three differences remain, all one byte each and two of them cancelling:
//
//   * retail calls operator new[] at 0x0002FDE0; every spelling of `new
//     T[newsize]` here reaches operator new at 0x0002FDA0 instead.  Giving T a
//     user-declared constructor does flip the call to ??_U but drags a
//     construction loop in with it.
//   * retail computes the copy count with `cmovge`; both the ?: and the
//     if-form give `jle`/`mov` at /O1, and /Ot (or /O2) rewrites the whole
//     body.  /G5, /G6, /G7 and /GB make no difference to it.
//   * retail's `IsAllocated = (array == 0)` materialises zero in eax and
//     compares against the register; ours compares against an immediate.
//
// STILL OPEN: T itself.  The element is a four-byte scalar copied with a plain
// dword move and allocated with `shl eax,2` (no array cookie), which fixes its
// size but not its name, and nothing reaches the vftable except unclaimed
// bodies - 0x00154C0D, 0x0015540B, 0x00158B49, 0x00158E3D store it and
// 0x0015546F calls this.  The mangled name below is a placeholder: land the
// vftable's other five slots first, or convert one of those five callers, and
// the instantiation should fall out.

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
			int copycount = newsize;
			if (copycount > VectorMax)
			{
				copycount = VectorMax;
			}
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
		IsAllocated = (array == 0);
	}
	else
	{
		Clear();
	}

	return true;
}

template class VectorClass<Element>;
