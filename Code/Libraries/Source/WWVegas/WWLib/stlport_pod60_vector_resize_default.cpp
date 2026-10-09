// cl: /EHsc /MD /D_CRTIMP= /DNDEBUG /O1 /G7 /arch:SSE
// STLport 4.5.3 vector<BfmePod60>::resize(size_type) at 0x00588A72 (35B, RET 4): the one-argument
// resize builds a default element (rowed ctor ??0BfmePod60 0x00587500 on a stack temporary) and
// forwards to the rowed two-argument resize 0x0058814C, which takes the element by value
// (stlport_pod60_vector_resize_value.cpp). BfmePod60 names the proven 60-byte stride only. The
// declared copy ctor and destructor make MSVC build the default temporary in place at the
// argument slot with the saved-ESP frame slot; they are never called here (retail has no cleanup).
struct BfmePod60
{
	BfmePod60();
	BfmePod60(const BfmePod60 &);
	~BfmePod60();
	int a[15];
};
namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector {
public:
    typedef unsigned int size_type;
    void resize(size_type newSize, T value);
    void resize(size_type newSize);
};
template <class T, class A>
void vector<T,A>::resize(size_type newSize) {
    resize(newSize, T());
}
template void vector<BfmePod60,allocator<BfmePod60> >::resize(unsigned int);
}
