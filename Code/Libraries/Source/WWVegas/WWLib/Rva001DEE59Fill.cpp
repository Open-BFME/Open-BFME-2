// cl: /O1 /DNDEBUG /MD
// ?Rva001DEE59Fill@@YAPAURva001DF3F1Element@@PAU1@IABU1@@Z @0x001DEE59 27B: free wrapper over rowed __uninitialized_fill_n 0x001DEDFA; caller 0x001DF36C unblocks 0x001DF2D3.
struct Rva001DF3F1Element
{
	char _m[0x30];
	Rva001DF3F1Element(const Rva001DF3F1Element &that);
};
namespace _STL
{
struct __false_type {};
template <class F, class S, class T>
F __uninitialized_fill_n(F first, S n, const T &x, const __false_type &);
}
Rva001DF3F1Element *Rva001DEE59Fill(Rva001DF3F1Element *first, unsigned int n, const Rva001DF3F1Element &val)
{
	char dummy;
	return _STL::__uninitialized_fill_n(first, n, val, *(const _STL::__false_type *)&dummy);
}
