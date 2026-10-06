// cl: /DNDEBUG /MD /Ob2 /EHsc
//
// ShareBufferClass<unsigned>::ShareBufferClass, retail 0x00D1DE2 (110 bytes).
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
// with the ebp-frame __EH_prolog sequence.

void * __cdecl operator new[](unsigned int size);

class RefCountClass
{
public:
	RefCountClass() : m_refs(1) {}
	RefCountClass(const RefCountClass &) : m_refs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int m_refs;
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment);

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

template ShareBufferClass<unsigned>::ShareBufferClass(int, const char *, int);
