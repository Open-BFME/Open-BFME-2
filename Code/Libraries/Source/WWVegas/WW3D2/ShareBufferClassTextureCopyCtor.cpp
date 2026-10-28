// cl: /DNDEBUG /MD /Ob2 /EHsc
//
// ShareBufferClass<TextureClass*>::ShareBufferClass, retail 0x0015AE10
// (284 bytes). BFME1 port with a BFME2 drift: the reference copy skeleton
// (reference/open-bfme-1/.../WWLib/sharebuf.h, Array = new T[Count] then
// RawBuffer = Array, plus the alignment branch from the 3-arg ctor) copies
// raw pointers, but BFME2's texture elements are ref-counted, so each slot
// goes through vector-new over a 4-byte RefCountPtr<TextureClass> (retail calls
// the eh-vector constructor at 0x629512) and the copy loop AddRefs the
// incoming pointer (word at +4, inline) while releasing the outgoing one
// out of line (TextureBaseClass::Release_Ref at 0x61ED10) before the store
// -- the same AddRef discipline as BFME1's TexBufferClass copy in
// reference/open-bfme-1/.../WW3D2/meshmatdesc.cpp, moved into the base.
// RawBuffer/Array/Count/Alignment sit at +0x08/+0x0C/+0x10/+0x14 behind the
// vtable (retail installs 0xBD3C94); the allocation itself comes from the
// operator new[] at 0x2FDE0. RefCountClass resets NumRefs to 1 on copy.

class TextureBaseClass
{
public:
	void Release_Ref();

	unsigned char m_pad[4];
	unsigned short m_refCount;
};

class TextureClass : public TextureBaseClass
{
};

// The vector-new callback pair is the existing RefCountPtr<TextureClass>
// constructor at 0x00326BE6 and destructor at 0x0017098D. Use that provider
// identity, as fxshadernamespacesas.cpp does for its texture handles.
template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	~RefCountPtr() { if (m_ptr != 0) m_ptr->Release_Ref(); }

	T *m_ptr;
};

#pragma optimize("s", on)
class RefCountClass
{
public:
	__declspec(dllimport) __forceinline RefCountClass() : m_refs(1) {}
	RefCountClass(const RefCountClass &) : m_refs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int m_refs;
};
#pragma optimize("", on)

// The texture instantiation's destructor body is rowed as ~BfmeOwnVVE at
// 0x0015CC90: vtable 0xBD3C94 (installed by the copy ctor below) holds the
// deleting dtor 0x0015D020 that calls it.
class BfmeOwnVVE
{
public:
	~BfmeOwnVVE();
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(const ShareBufferClass &that);
	virtual ~ShareBufferClass() { ((BfmeOwnVVE *)this)->BfmeOwnVVE::~BfmeOwnVVE(); }

protected:
	T *m_rawBuffer; // +0x08
	T *m_array; // +0x0C
	int m_count; // +0x10
	int m_alignment; // +0x14
};

#include <new>

template <class T>
ShareBufferClass<T>::ShareBufferClass(const ShareBufferClass<T> &that) :
	m_count(that.m_count)
{
	m_alignment = that.m_alignment;
	if (m_alignment == 0)
	{
		m_rawBuffer = (T *)new RefCountPtr<TextureClass>[m_count];
		m_array = m_rawBuffer;
	}
	else
	{
		m_rawBuffer = (T *)new char[m_count * sizeof(T) + m_alignment];
		m_array = (T *)(((unsigned int)m_rawBuffer + m_alignment - 1) &
			~(m_alignment - 1));
	}
	for (int index = 0; index < m_count; ++index)
	{
		TextureClass **srcSlot = &that.m_array[index];
		TextureClass **dstSlot = &m_array[index];
		if (*srcSlot != 0)
			(*srcSlot)->m_refCount += 1;
		if (*dstSlot != 0)
			(*dstSlot)->Release_Ref();
		*dstSlot = *srcSlot;
	}
}

template ShareBufferClass<TextureClass *>::ShareBufferClass(
	const ShareBufferClass<TextureClass *> &);
