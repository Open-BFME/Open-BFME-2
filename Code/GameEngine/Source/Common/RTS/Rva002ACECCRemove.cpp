// cl: /MD /GX-
// ?rva002ACECC@Rva002ACECC@@QAEXH@Z @0x002ACECC 19B unlock via 0x002ABFC3
// Evidence: this+0x754 list<BfmePod12>::remove rowed; == in stlport_pod_list_bodies reads only a[0] so int key passed as Pod12 ref is safe; callers at 0x00489DC1 0x00489E52.
struct BfmePod12 { int a[3]; };
namespace _STL {
template <class T> class allocator;
template <class T, class A> class list {
public:
	void remove(const T &) throw();
};
}
class Rva002ACECC {
	char m_pad[0x754];
	_STL::list<BfmePod12, _STL::allocator<BfmePod12> > m_list;
public:
	void rva002ACECC(int key);
};
void Rva002ACECC::rva002ACECC(int key)
{
	m_list.remove(*(const BfmePod12 *)&key);
}
