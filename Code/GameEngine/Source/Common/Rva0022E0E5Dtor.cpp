// cl: /DNDEBUG /MD /EHsc
// ??1Rva0022E0E5@@UAE@XZ retail 0x001B4D16 77B
// Own vptr 0x00BD7678 (slot-0 ??_G at 0x001B4D63). The body clears the
// STLport list member at +0x0C through the rowed _List_base clear 0x001B4C7A,
// then the member teardown runs the rowed 0x001B4CD8 (clear plus node free,
// rowed under the address-derived ?rva001B4CD8@Rva001B4CD8@@QAEXXZ), then the
// rowed base dtor ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74.
struct BfmeVectorRecord001B4A39;

class Rva001B4CD8
{
public:
	void rva001B4CD8();
};

namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class A> class _List_base
	{
	public:
		__forceinline ~_List_base()
		{
			reinterpret_cast<Rva001B4CD8 *>(this)->rva001B4CD8();
		}
		void clear();
	private:
		void *m_node;
	};
}

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

class Rva0022E0E5 : public SubsystemInterface
{
public:
	virtual ~Rva0022E0E5();

private:
	_STL::_List_base<BfmeVectorRecord001B4A39, _STL::allocator<BfmeVectorRecord001B4A39> > m_list0C; // +0x0C
};

Rva0022E0E5::~Rva0022E0E5()
{
	m_list0C.clear();
}
