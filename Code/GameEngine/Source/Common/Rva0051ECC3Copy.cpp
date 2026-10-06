// cl: /MD
// ??0Rva0051ECC3@@QAE@ABV0@@Z @0x0051ECC3 71B vector copy ctor via rowed Vector_base SaveMapPreview get_allocator AsciiString uninit-copy Rva0039BA22
// Evidence: caller 0x0051F87B member at +0x14; stride 0x14; callees 0x0021983A row AsciiString 0x004FF36C pin SaveMapPreview 0x0039BA22 row Rva0039B893; precedent Rva005386F5Copy.cpp
class SaveMapPreview
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
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
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
class Rva0051ECC3 : public _STL::_Vector_base<SaveMapPreview, _STL::allocator<SaveMapPreview> >
{
public:
	Rva0051ECC3(const Rva0051ECC3 &x);
};
Rva0051ECC3::Rva0051ECC3(const Rva0051ECC3 &x)
	: _STL::_Vector_base<SaveMapPreview, _STL::allocator<SaveMapPreview> >((x.m_finish - x.m_start), *(const _STL::allocator<SaveMapPreview> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (SaveMapPreview *)Rva0039BA22UninitCopy((Rva0039B893 *)x.m_start, (Rva0039B893 *)x.m_finish, (Rva0039B893 *)m_start, _STL::__false_type());
}
