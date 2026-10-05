// cl: /O1
// Single-element vector erase @0x002606AF, 55B; 8-byte element.
// Masked twin of Rva0040DC1F erase.

struct Rva002606AFElem { char m_pad[8]; };
class Rva002606AFDtor { public: ~Rva002606AFDtor(); };

namespace _STL {
struct __false_type {};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}

class Rva002606AF {
public:
	Rva002606AFElem *erase(Rva002606AFElem *position);
	const Rva002606AFElem *end() { return m_finish; }
private:
	Rva002606AFElem *m_start;
	const Rva002606AFElem *m_finish;
	Rva002606AFElem *m_endOfStorage;
};

Rva002606AFElem *Rva002606AF::erase(Rva002606AFElem *position)
{
	_STL::__false_type tag;
	if (position + 1 != end())
		_STL::__copy_ptrs(static_cast<const Rva002606AFElem *>(position + 1), m_finish, position, tag);
	--m_finish;
	((Rva002606AFDtor *)m_finish)->~Rva002606AFDtor();
	return position;
}
