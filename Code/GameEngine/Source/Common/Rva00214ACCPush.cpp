// cl: /DNDEBUG /MD
// ?rva00214ACC@Rva00214ACC@@QAEXURva004DFCB0Element@@@Z @0x00214ACC 16B
// Vector push_back wrapper: lea eax,[esp+4] push eax add ecx,0xC call rowed
// push_back 0x004DFCB0 ret 4. Evidence: rowed push_back 0x004DFCB0; caller
// 0x00214CFF in unclaimed 0x00214C4E; abuts prev 0x00214AC7 and next 0x00214ADC;
// container offset 0xC. Honest address-derived holder.
struct Rva004DFCB0Element
{
	unsigned word0;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class Rva00214ACC
{
public:
	void rva00214ACC(Rva004DFCB0Element value);
private:
	char m_pad[0x0C];
	_STL::vector<Rva004DFCB0Element> m_vec;
};

void Rva00214ACC::rva00214ACC(Rva004DFCB0Element value)
{
	m_vec.push_back(value);
}
