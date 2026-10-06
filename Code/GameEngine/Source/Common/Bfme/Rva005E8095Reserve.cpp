// cl: /MD
// ?rva005E8095@Rva005E8095@@QAEXI@Z @0x005E8095 104B
// Vector reserve for Rva005E71C6Ref: if capacity - start >= n return; else if
// start!=0 allocate_and_copy via rowed 0x005E7229 plus clear via rowed 0x005E8077
// else allocate n via rowed STL allocator; then finish=start+size and
// storage=start+n. Chain via just-landed 0x005E7229 plus prev/next same /O1 flags.
struct Rva005E71C6Ref
{
	void *m_object;
};
struct BfmeE12
{
	float x;
	float y;
	float z;
};
namespace _STL {
template <typename T> class allocator
{
public:
	T *allocate(unsigned n, const void *hint) const;
};
}
class Rva005E7229
{
public:
	Rva005E71C6Ref *rva005E7229(unsigned n, Rva005E71C6Ref *first, Rva005E71C6Ref *last);
private:
	char m_pad[8];
	_STL::allocator<BfmeE12 *> m_alloc;
};
class Rva005E8077
{
public:
	void rva005E8077();
};
class Rva005E8095
{
public:
	void rva005E8095(unsigned n);
private:
	Rva005E71C6Ref *m_start;
	Rva005E71C6Ref *m_finish;
	union {
		Rva005E71C6Ref *m_end;
		_STL::allocator<BfmeE12 *> m_alloc;
	};
};
void Rva005E8095::rva005E8095(unsigned n)
{
	if ((unsigned)(m_end - m_start) >= n)
		return;
	unsigned old_size = (unsigned)(m_finish - m_start);
	Rva005E71C6Ref *new_start;
	if (m_start != 0) {
		new_start = ((Rva005E7229 *)this)->rva005E7229(n, m_start, m_finish);
		((Rva005E8077 *)this)->rva005E8077();
	} else {
		new_start = (Rva005E71C6Ref *)m_alloc.allocate(n, 0);
	}
	m_finish = new_start + old_size;
	m_start = new_start;
	m_end = new_start + n;
}
