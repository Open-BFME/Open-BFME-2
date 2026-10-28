// cl: /DNDEBUG /MD /Ob2 /EHsc
//
// ShareBufferClass<unsigned>::ShareBufferClass, retail 0x00D1DE2 (110 bytes),
// and its sibling destructor group in the same object: the scalar deleting
// destructor at 0x00D1E6C (28 bytes) and the destructor at 0x00D1E88
// (26 bytes, the vtable store 0xBCE330 identifies the instantiation).
// Out-of-line dependency of MeshMatDescClass::Get_Color_Array (retail calls
// it with the fresh 0x18-byte block, VertexCount and the
// "MeshMatDescClass::ColorArray" message). BFME1 sweep sharebuf.h 3-arg
// shape (Count/Alignment init-list, RawBuffer in-arm, Array sunk to the
// join); msg is dead in retail, kept only for the signature. Both arms
// allocate through an explicit operator new[] call (retail routes them to
// vector-new 0x2FDE0): a plain array-new of a trivial element type would
// emit scalar operator new instead. RawBuffer/Array/Count/Alignment sit at
// +0x08/+0x0C/+0x10/+0x14 behind the vtable (retail installs 0xBCE330).
// RefCountClass resets NumRefs to 1 on copy. This unit builds at /O1: at
// /O2 the compiler picks the frameless SEH prologue, while retail opens
// with the ebp-frame __EH_prolog sequence; the /O1 cleanup form (pop ecx,
// not add esp,4) is what retail's kept deleting destructor shows.

#include <new>

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int NumRefs; // +0x04
};

// The canonical class view declares the destructor out of line. This unit
// emits the instantiation retail keeps: the CPU's vptr stores around the
// buffer free, no EH frame (the free cannot throw) and no null test.
template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment);
	virtual ~ShareBufferClass();

protected:
	T *m_rawBuffer; // +0x08
	T *m_array; // +0x0C
	int m_count; // +0x10
	int m_alignment; // +0x14
};

template <class T>
ShareBufferClass<T>::ShareBufferClass(int count, const char *msg, int alignment) :
	m_count(count),
	m_alignment(alignment)
{
	(void)msg;
	if (m_alignment == 0)
	{
		m_rawBuffer = (T *)operator new[](m_count * sizeof(T));
		m_array = m_rawBuffer;
	}
	else
	{
		m_rawBuffer = (T *)operator new[](m_count * sizeof(T) + m_alignment);
		m_array = (T *)(((unsigned int)m_rawBuffer + m_alignment - 1) &
			~(m_alignment - 1));
	}
}

template <> inline
ShareBufferClass<unsigned>::~ShareBufferClass()
{
	::operator delete[](m_rawBuffer);
}

template ShareBufferClass<unsigned>::ShareBufferClass(int, const char *, int);
