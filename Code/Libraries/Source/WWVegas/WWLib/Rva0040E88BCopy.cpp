// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?GetEntries@ArmySummary@@QAEXAAV?$vector@URva0040DC56Element@@V?$allocator@URva0040DC56Element@@@_STL@@@_STL@@@Z @0x0040E88B 70B
// Copies 8-byte source range [+0x40,+0x44) second fields into dest vector:
// dest.erase(begin,end), dest.reserve(count), push_back each [esi+4].
// Evidence: unlock lane; callees rowed erase 0x0040DC56 reserve 0x0040DC89 push_back 0x003F7B22; callers at 0x002BBF61 0x004FA26F.
#include <vector>

struct Rva0040DC56Element
{
	int a[1];
};

struct Rva003F7B22Element
{
	int a[1];
};

struct Rva0040E88BSrc
{
	int m_first;
	Rva003F7B22Element m_second;
};

class ArmySummary
{
public:
	void GetEntries(_STL::vector<Rva0040DC56Element> &dst);
private:
	char m_pad[0x40];
	Rva0040E88BSrc *m_begin;
	Rva0040E88BSrc *m_end;
};

void ArmySummary::GetEntries(_STL::vector<Rva0040DC56Element> &dst)
{
	dst.erase(dst.begin(), dst.end());
	dst.reserve(unsigned int(m_end - m_begin));
	_STL::vector<Rva003F7B22Element> &dst2 = (_STL::vector<Rva003F7B22Element> &)dst;
	Rva0040E88BSrc *first = m_begin;
	Rva0040E88BSrc *last = m_end;
	for (Rva0040E88BSrc *p = first; p != last; ++p)
		dst2.push_back(p->m_second);
}
