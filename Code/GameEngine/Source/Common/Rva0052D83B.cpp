// cl: /DNDEBUG /MD
// ?rva0052D83B@Rva0052D83B@@QAEXABURva0052D801Record@@@Z @0x0052D83B 8B
// Evidence: unlock lane unblocks 0x00566D83; add ecx,0xC tail-jmp to rowed vector push_back 0x0052D801; neighbours share /O1 /G7.
typedef int Int;

struct Rva0052D801Record;

namespace _STL {
template <typename T> class allocator;
template <typename T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &v);
};
}

class Rva0052D83B
{
	char m_pad[0xC];
	_STL::vector<Rva0052D801Record> m_vec;
public:
	void rva0052D83B(const Rva0052D801Record &v);
};

void Rva0052D83B::rva0052D83B(const Rva0052D801Record &v)
{
	return m_vec.push_back(v);
}
