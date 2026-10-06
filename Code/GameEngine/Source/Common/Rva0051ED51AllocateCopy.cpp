// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0051ED51@Rva0051ED51Holder@@QAEPAVRva0039B893@@IPAV2@0@Z @0x0051ED51 45B allocate-and-copy
// via rowed 20-byte allocator 0x00395960 and rowed null-guarded uninit copy 0x0039BA22.
// Evidence: chain from just-landed 0x0039BA22; callers 0x0039C062 0x0051F71E push three args.

class Rva0039B893;
struct BfmeStringRecord002CF4C6;

namespace _STL
{
template <class T>
class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};

struct __false_type { __false_type() {} };
}

Rva0039B893 *__cdecl Rva0039BA22UninitCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const _STL::__false_type &);

class Rva0051ED51Holder
{
public:
	Rva0039B893 *rva0051ED51(unsigned int n, Rva0039B893 *first, Rva0039B893 *last);

private:
	char m_pad00[8];
	_STL::allocator<BfmeStringRecord002CF4C6> m_alloc08;
};

Rva0039B893 *Rva0051ED51Holder::rva0051ED51(unsigned int n, Rva0039B893 *first, Rva0039B893 *last)
{
	Rva0039B893 *result = (Rva0039B893 *)m_alloc08.allocate(n, 0);
	Rva0039BA22UninitCopy(first, last, result, _STL::__false_type());
	return result;
}
