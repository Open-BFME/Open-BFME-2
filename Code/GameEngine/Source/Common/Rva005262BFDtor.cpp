// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva005262BF@@QAE@XZ retail 0x005262BF 76B
// Pointee dtor of the owning-pointer reset 0x00526F2C. Members torn down in
// reverse order: STLport int list bases at +0x14 and +0x10 (rowed
// 0x004EC395), then the inline CRT buffer member at +0 frees its block.
namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
	private:
		void *m_node;
	};
}

extern "C" void __cdecl free(void *);

struct Rva005262BFBuffer
{
	void *m_block;
	~Rva005262BFBuffer()
	{
		if (m_block)
			free(m_block);
	}
};

class Rva005262BF
{
public:
	~Rva005262BF();
private:
	Rva005262BFBuffer m_buffer; // +0x00
	char m_pad04[0x10 - 0x04];
	_STL::_List_base<int, _STL::allocator<int> > m_list10; // +0x10
	_STL::_List_base<int, _STL::allocator<int> > m_list14; // +0x14
};

Rva005262BF::~Rva005262BF()
{
}
