// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva00414BDBElement@@QAE@XZ retail 0x001DDEC3 60B
// Element dtor reached from the 0x00414BDB vector insert overflow. Members in
// reverse order: the inline CRT buffer member at +0x20 frees its block, then
// the BfmeRecord001DD3BC set at +0x14 runs the rowed tree dtor 0x001DDB8E.
struct BfmeRecord001DD3BC;

namespace _STL
{
	template <class T> class allocator
	{
	};
	template <class T> struct _Identity
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
		void *m_header;
		int m_count;
		int m_compare;
	};
}

extern "C" void __cdecl free(void *);

struct Rva00414BDBElementBuffer
{
	void *m_block;
	~Rva00414BDBElementBuffer()
	{
		if (m_block)
			free(m_block);
	}
};

class Rva00414BDBElement
{
public:
	~Rva00414BDBElement();
private:
	char m_pad00[0x14];
	_STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > m_set; // +0x14
	Rva00414BDBElementBuffer m_buffer; // +0x20
};

Rva00414BDBElement::~Rva00414BDBElement()
{
}
