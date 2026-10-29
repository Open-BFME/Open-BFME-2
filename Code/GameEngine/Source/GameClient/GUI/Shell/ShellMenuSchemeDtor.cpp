// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1ShellMenuScheme@@QAE@XZ @0x002006B0 196B (was the placeholder Rva002006B0).
// Two-list cleanup dtor with StringBase release. Evidence: EH prolog scope
// 0x0076C38D; rowed list<int> erase 0x00438539 and list_base dtor 0x004EC395;
// rowed StringBase<D> releaseBuffer 0x00036410 and delete 0x0002FD60;
// offsets +4 +8 payload +0x14; callers 0x0020078E 0x00200818 0x0020091D.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();


class Payload002006B0 : public StringBase<char>
{
public:
	char m_pad[0x10];
	int m_image;
};

class ShellMenuScheme : public StringBase<char>
{
public:
	~ShellMenuScheme();
private:
	_STL::list<int> m_4;
	_STL::list<int> m_8;
};

ShellMenuScheme::~ShellMenuScheme()
{
	for (_STL::list<int>::iterator it = m_4.begin(); it._M_node != m_4.end()._M_node; )
	{
		Payload002006B0 *image = (Payload002006B0 *)(int)*it;
		it = m_4.erase(it);
		if (image != 0)
		{
			image->m_image = 0;
			delete image;
		}
	}
	for (_STL::list<int>::iterator it = m_8.begin(); it._M_node != m_8.end()._M_node; )
	{
		void *image = (void *)(int)*it;
		it = m_8.erase(it);
		if (image != 0)
			delete image;
	}
}

class Rva002007D5
{
public:
	Rva002007D5();
	~Rva002007D5();
private:
	_STL::list<int> m_0;
	int m_4;
};

Rva002007D5::Rva002007D5()
	: m_0()
	, m_4(0)
{
}

Rva002007D5::~Rva002007D5()
{
	m_4 = 0;
	for (_STL::list<int>::iterator it = m_0.begin(); it._M_node != m_0.end()._M_node; )
	{
		ShellMenuScheme *shellMenuScheme = (ShellMenuScheme *)(int)*it;
		it = m_0.erase(it);
		if (shellMenuScheme != 0)
			delete shellMenuScheme;
	}
}

// ?forceShellMenuSchemeDelete@@YAXPAVShellMenuScheme@@@Z absent-from-retail
void forceShellMenuSchemeDelete(ShellMenuScheme *shellMenuScheme) { delete shellMenuScheme; }

// ?forceRva002007D5Delete@@YAXPAVRva002007D5@@@Z absent-from-retail
void forceRva002007D5Delete(Rva002007D5 *m_schemeManager) { delete m_schemeManager; }
