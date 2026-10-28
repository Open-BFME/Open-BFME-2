// cl: /MD
// ??0Rva0039C151@@QAE@ABV0@@Z @0x0051ECC3 71B vector copy ctor via rowed Vector_base Rva0054103E get_allocator AsciiString uninit-copy Rva0039BA22
// Evidence: caller 0x0051F87B member at +0x14; stride 0x14; callees 0x0021983A row AsciiString 0x004FF36C pin Rva0054103E 0x0039BA22 row Rva0039B893; precedent Rva005386F5Copy.cpp
class Rva0054103E
{
public:
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
};
class Rva0039B893
{
public:
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();
	int m_field04; // +0x04
	int m_field08; // +0x08
	short m_field0C; // +0x0C
	short m_field0E; // +0x0E
	short m_field10; // +0x10
	char m_pad12[0x2];
};
class AsciiString;
namespace _STL {
template <class T> class allocator
{
public:
	allocator();
	allocator(const allocator &other);
	template <class U> allocator(const allocator<U> &) {}
	T *allocate(unsigned int n, const void *hint) const;
};
struct __false_type { __false_type() {} };
template <class T, class Alloc> class vector
{
public:
	allocator<T> get_allocator() const;
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
template <class T, class Alloc> class _Vector_base
{
protected:
	T *m_start;
	T *m_finish;
	T *m_end;
public:
	_Vector_base(unsigned int n, const allocator<T> &a);
};
}
class Rva0039B893;
Rva0039B893 *Rva0039BA22UninitCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const _STL::__false_type &tag);
class Rva0039C151 : public _STL::_Vector_base<Rva0054103E, _STL::allocator<Rva0054103E> >
{
public:
	Rva0039C151(const Rva0039C151 &x);
};
Rva0039C151::Rva0039C151(const Rva0039C151 &x)
	: _STL::_Vector_base<Rva0054103E, _STL::allocator<Rva0054103E> >((x.m_finish - x.m_start), *(const _STL::allocator<Rva0054103E> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (Rva0054103E *)Rva0039BA22UninitCopy((Rva0039B893 *)x.m_start, (Rva0039B893 *)x.m_finish, (Rva0039B893 *)m_start, _STL::__false_type());
}
