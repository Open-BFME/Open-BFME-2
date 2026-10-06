// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// stlport
// ??1Rva00200667@@QAE@XZ, retail 0x00200667, 5 bytes. Thunk jmp to List_base dtor 0x004EC395.
// Evidence: retail 5B jmp to 0x004EC395; vector-dtor at 0x00320058 pushes 0x00200667 as array element dtor; Rva00283002Clear calls it; deleting-dtor wrapper at 0x002821B3.
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class _List_base
	{
	public:
		~_List_base();
	private:
		void *m_header;
	};
}

class Rva00200667 : public _STL::_List_base<int, _STL::allocator<int> >
{
public:
	~Rva00200667();
};

Rva00200667::~Rva00200667()
{
}
