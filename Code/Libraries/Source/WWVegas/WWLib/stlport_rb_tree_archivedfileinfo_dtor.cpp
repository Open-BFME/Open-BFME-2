// cl: /DNDEBUG /MD /EHs
// ??1?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VArchivedFileInfo@@@_STL@@...@_STL@@QAE@XZ
// retail 0x00223FF1 57B. The archived-file map tree dtor: the rowed node
// clear 0x0022380B (rowed under the address-derived
// ?rva0022380B@Rva00223591@@QAEXXZ) runs on this, then the header block at
// +4 is freed through the CRT when non-null.
class AsciiString;
class ArchivedFileInfo;

class Rva00223591
{
public:
	void rva0022380B();
};

extern "C" void __cdecl free(void *);

struct Rva00223FF1Header
{
	void *m_block;
	~Rva00223FF1Header()
	{
		if (m_block)
			free(m_block);
	}
};

namespace _STL
{
	template <class T> class allocator
	{
	};
	template <class T1, class T2> struct pair
	{
	};
	template <class T> struct _Select1st
	{
	};
	template <class T> struct less
	{
	};
	template <class K, class V, class KoV, class C, class A> class _Rb_tree
	{
	public:
		~_Rb_tree();
	private:
		int m_compare;
		Rva00223FF1Header m_header;
		int m_count;
	};
}

typedef _STL::pair<const AsciiString, ArchivedFileInfo> Rva00223FF1Value;
typedef _STL::_Rb_tree<AsciiString, Rva00223FF1Value, _STL::_Select1st<Rva00223FF1Value>, _STL::less<AsciiString>, _STL::allocator<Rva00223FF1Value> > Rva00223FF1Tree;

template <> Rva00223FF1Tree::~_Rb_tree()
{
	reinterpret_cast<Rva00223591 *>(this)->rva0022380B();
}
