// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva0026E1A6@@QAE@XZ retail 0x0026E1A6 56B
// TU-local member dtor for the +0x3AC field of the 0x0033DDA1 teardown. The
// body runs the rowed LocomotorSetType tree clear 0x0026DEE4 on this, then
// the inline CRT buffer member at +0 (the tree header) frees its block.
enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1
};
class LocomotorTemplate;

namespace _STL
{
	template <class T> class allocator
	{
	};
	template <class T, class A> class vector
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
		void clear();
	};
}

typedef _STL::vector<const LocomotorTemplate *, _STL::allocator<const LocomotorTemplate *> > Rva0026E1A6Templates;
typedef _STL::pair<const LocomotorSetType, Rva0026E1A6Templates> Rva0026E1A6Value;
typedef _STL::_Rb_tree<LocomotorSetType, Rva0026E1A6Value, _STL::_Select1st<Rva0026E1A6Value>, _STL::less<LocomotorSetType>, _STL::allocator<Rva0026E1A6Value> > Rva0026E1A6Tree;

extern "C" void __cdecl free(void *);

struct Rva0026E1A6Header
{
	void *m_block;
	~Rva0026E1A6Header()
	{
		if (m_block)
			free(m_block);
	}
};

class Rva0026E1A6
{
public:
	~Rva0026E1A6();
private:
	Rva0026E1A6Header m_header; // +0x00
	int m_count; // +0x04
	int m_compare; // +0x08
};

Rva0026E1A6::~Rva0026E1A6()
{
	reinterpret_cast<Rva0026E1A6Tree *>(this)->clear();
}
