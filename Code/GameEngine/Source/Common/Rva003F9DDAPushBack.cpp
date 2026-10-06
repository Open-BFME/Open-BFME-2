// cl: /DNDEBUG /MD /EHsc
// ?rva003F9DDA@Rva003F9DDA@@QAEXABUBfmeE8@@@Z @ 0x003F9DDA 8B: inline vector push_back forwarder via plus0x3c to rowed push_back 0x00539A2E. Evidence: add ecx 0x3c plus jmp plus caller 0x00210ECF ret4.
struct BfmeE8 { unsigned int a; unsigned int b; };
namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector {
public:
	void push_back(const T &);
};
}
class Rva003F9DDA {
	char m_pad[0x3c];
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
public:
	void rva003F9DDA(const BfmeE8 &);
};
void Rva003F9DDA::rva003F9DDA(const BfmeE8 &e)
{
	m_vec.push_back(e);
}
