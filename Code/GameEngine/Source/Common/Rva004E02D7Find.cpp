// cl: /MD
// ?rva004E02D7@Rva004E02D7Owner@@QAEXPAVCreateAHeroData@@@Z @0x004E02D7 52B: thiscall, one
// reference argument, ret 4. Finds the argument in the pointer vector at +4 (start +4, finish +8)
// with the rowed find 0x0020E873; when found, erases that element through the rowed vector erase
// 0x001FF51F and then calls the owner's follow-up member at 0x004E00D9 (address-named pin).
// Names are address-derived views; no field meaning is claimed beyond the bytes.
class CreateAHeroData;

namespace _STL
{
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
	T *_M_start;
	T *_M_finish;
	T *erase(T *pos);
};
template <class I, class T> I find(I first, I last, const T &value);
}

class Rva004E02D7Owner
{
public:
	void rva004E02D7(CreateAHeroData *value);
	void rva004E00D9();
private:
	int m_pad00;
	_STL::vector<void *, _STL::allocator<void *> > m_heroes;
};

void Rva004E02D7Owner::rva004E02D7(CreateAHeroData *value)
{
	CreateAHeroData **end = (CreateAHeroData **)m_heroes._M_finish;
	CreateAHeroData **found = _STL::find((CreateAHeroData **)m_heroes._M_start, end, value);
	if (found != end) {
		m_heroes.erase((void **)found);
		rva004E00D9();
	}
}
