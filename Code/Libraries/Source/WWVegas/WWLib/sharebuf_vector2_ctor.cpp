// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// ??0?$ShareBufferClass@VVector2@@@@QAE@HPBDH@Z, retail 0x000D1D33 (149 bytes).
//
// BFME's 3-arg aligned-buffer ShareBufferClass constructor for Vector2.
// Modelled on sharebuf_vector2_copy_ctor.cpp (same Vector2/RefCountClass
// layout, same flags): RawBuffer/Array/Count/Alignment around Zero Hour's
// Array and Count, installed vtable, refcount of 1. The default Vector2
// constructor stays declared-only so the array construction reaches the
// out-of-line trivial ctor at 0x0047A6A9 through vector_constructor_iterator
// (retail pushes VA 0x87A6A9); the allocation reaches operator new[] at
// 0x002FDE0. Sole known caller: Install_UV_Array at 0x0015B960.

void *operator new[](unsigned int size) throw();
void operator delete[](void *place) throw();
inline void *operator new(unsigned int, void *place) { return place; }

class Vector2
{
public:
	Vector2();

private:
	float X;
	float Y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int NumRefs;
};

// upstream layout: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/sharebuf.h,
// with BFME's RawBuffer/Alignment pair around Zero Hour's Array and Count.
template <class Type>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment = 0);
	~ShareBufferClass();

protected:
	Type *RawBuffer;
	Type *Array;
	int Count;
	int Alignment;
};

template <class Type>
ShareBufferClass<Type>::ShareBufferClass(int count, const char *msg, int alignment) :
	Count(count),
	Alignment(alignment)
{
	if (Alignment == 0) {
		RawBuffer = new Type[Count];
		Array = RawBuffer;
	} else {
		RawBuffer = (Type *)new char[Count * sizeof(Type) + Alignment];
		Array = (Type *)(((unsigned int)RawBuffer + Alignment - 1) &
			~(unsigned int)(Alignment - 1));
	}
}

template ShareBufferClass<Vector2>::ShareBufferClass(int, const char *, int);

// ??1?$ShareBufferClass@VVector2@@@@UAE@XZ, retail 0x000D1DC8 (26 bytes).
template <class Type>
ShareBufferClass<Type>::~ShareBufferClass()
{
	delete[] RawBuffer;
}

template ShareBufferClass<Vector2>::~ShareBufferClass();
