// cl: /O1
// Single-element vector erase @0x002821CF, 55B; 8-byte element.
// Masked twin of Rva0040DC1F erase.

struct Rva002821CFElem { char m_pad[8]; };
class Rva002821CFDtor { public: ~Rva002821CFDtor(); };

namespace _STL {
struct __false_type {};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}

class Rva002821CF {
public:
	Rva002821CFElem *erase(Rva002821CFElem *position);
	const Rva002821CFElem *end() { return m_finish; }
private:
	Rva002821CFElem *m_start;
	const Rva002821CFElem *m_finish;
	Rva002821CFElem *m_endOfStorage;
};

Rva002821CFElem *Rva002821CF::erase(Rva002821CFElem *position)
{
	_STL::__false_type tag;
	if (position + 1 != end())
		_STL::__copy_ptrs(static_cast<const Rva002821CFElem *>(position + 1), m_finish, position, tag);
	--m_finish;
	((Rva002821CFDtor *)m_finish)->~Rva002821CFDtor();
	return position;
}
