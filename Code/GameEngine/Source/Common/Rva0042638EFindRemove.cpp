// cl: /Oy- /MD
//
// ?rva0042638E@Rva0042638E@@QAE_NPBUSearchArg0042638E@@@Z, retail 0x0042638E, 60 bytes.
// Removes a CreateAHeroData entry from the +0x24/+0x28 range if present:
// finds [arg+0x74] via rowed _STL::find, swaps in the last element and
// shrinks finish by one, returning true; else false.
// Evidence: _STL::find call to rowed 0x0020E873; [edi-4] fill; add [mem],-4;
// callers at 0x002986D9 and 0x00299DA5; ret 4 single pointer arg.
class CreateAHeroData;

namespace _STL
{
template <typename I, typename T> T *__cdecl find(I first, I last, const T &val) throw();
}

struct SearchArg0042638E
{
	char m_pad[0x74];
	CreateAHeroData *m_entry;
};

class Rva0042638E
{
public:
	bool rva0042638E(const SearchArg0042638E *arg);
private:
	char m_pad[0x24];
	CreateAHeroData **m_start;
	CreateAHeroData **m_finish;
};

bool Rva0042638E::rva0042638E(const SearchArg0042638E *arg)
{
	CreateAHeroData *v = arg->m_entry;
	CreateAHeroData **finish = m_finish;
	CreateAHeroData **found = _STL::find(m_start, finish, v);
	if (found != finish)
	{
		*found = *(finish - 1);
		--m_finish;
		return true;
	}
	return false;
}
