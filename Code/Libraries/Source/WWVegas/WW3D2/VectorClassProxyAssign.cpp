// cl: /G7 /DNDEBUG /MD /EHsc
// ?operator=@?$VectorClass@VProxyClass@@@@QAEAAV0@ABV0@@Z
//
// VectorClass<ProxyClass>::assignment operator, retail 0x0016F610 (249B).
//
// What the retail bytes prove about the element type here:
//
// - The new[] buffer is sized Count*4+4 with the count stored at [buffer]
//   and elements at [buffer+4]: MSVC's new[] lowering for an element type
//   with a non-trivial destructor, so ProxyClass has a user-declared dtor
//   (and the array build goes through ??_L with SEH).
// - The fill loop copies 4 bytes per element, inlining the element
//   assignment as: AddRef the source handle (null-checked increment of the
//   WORD at handle+4), Release the destination handle through 0x0061ED10
//   (null-checked), then copy the handle.  No other member traffic means
//   ProxyClass itself is a 4-byte refcounted handle; the Name/Transform
//   interface the collection code programs against lives behind it.
// - The operator first calls the slot-3 virtual (Clear) and parks IsValid
//   false, restoring it (with IsAllocated) on each completed path.  That
//   IsValid juggling is not in the generic WWLib template, so this TU
//   carries the BFME2-era shape explicitly.
//
// C++ name mangling encodes only the identifier, so this TU-scoped replica
// mangles identically to the real instantiation while keeping the fat
// ProxyClass views other TUs use untouched.

extern void *__cdecl operator new[](unsigned int size);
extern void __cdecl operator delete[](void *block);

class TextureBaseClass
{
public:
	void Release_Ref();
};

class ProxyClass
{
public:
	ProxyClass();
	~ProxyClass();
	ProxyClass &operator=(ProxyClass const &src);

private:
	TextureBaseClass *m_Data;
};

// ?ProxyClass::ProxyClass present-unmatched
inline ProxyClass::ProxyClass() :
	m_Data(0)
{
}

// ?ProxyClass::~ProxyClass present-unmatched
inline ProxyClass::~ProxyClass()
{
	if (m_Data != 0) {
		m_Data->Release_Ref();
	}
}

inline ProxyClass &ProxyClass::operator=(ProxyClass const &src)
{
	if (src.m_Data != 0) {
		*(unsigned short *)((unsigned char *)src.m_Data + 4) =
			*(unsigned short *)((unsigned char *)src.m_Data + 4) + 1;
	}
	if (m_Data != 0) {
		m_Data->Release_Ref();
	}
	m_Data = src.m_Data;
	return *this;
}

template<class T>
class VectorClass
{
public:
	virtual ~VectorClass(void);
	virtual bool operator==(VectorClass<T> const &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

	VectorClass<T> &operator=(VectorClass<T> const &vec);
	int Length(void) const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }
	T const &operator[](int index) const { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClass<T> &VectorClass<T>::operator=(VectorClass<T> const &vec)
{
	int index;
	if (this != &vec) {
		Clear();
		IsValid = false;
		VectorMax = vec.Length();
		if (VectorMax != 0) {
			Vector = new T[VectorMax];
			if (Vector != 0) {
				index = 0;
				IsAllocated = true;
				IsValid = true;
				for (; index < VectorMax; index += 1) {
					Vector[index] = vec[index];
				}
			}
		}
		else {
			Vector = 0;
			IsAllocated = false;
			IsValid = true;
		}
	}
	return *this;
}

template<class T>
VectorClass<T>::~VectorClass(void)
{
}

template<class T>
bool VectorClass<T>::operator==(VectorClass<T> const &) const
{
	return false;
}

template<class T>
bool VectorClass<T>::Resize(int, T const *)
{
	return false;
}

template<class T>
void VectorClass<T>::Clear(void)
{
}

template<class T>
int VectorClass<T>::ID(T const *)
{
	return 0;
}

template<class T>
int VectorClass<T>::ID(T const &)
{
	return 0;
}

template class VectorClass<ProxyClass>;
