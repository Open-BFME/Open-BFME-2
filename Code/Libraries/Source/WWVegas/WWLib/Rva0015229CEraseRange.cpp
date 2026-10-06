// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?EraseRange@Rva0015229CVector@@QAEPAURva0007BB16Record@@PAU2@0@Z, retail 0x0015229C, 51 bytes.
// Range erase over 36-byte two-string records: copy [last finish) down to first
// via rowed __copy_ptrs for BfmeAssignRecord36 at 0x00151FCA then destroy the
// vacated tail via rowed _Destroy for Rva0007BB16Record at 0x0007C2D7 then store
// the new finish and return first. Same 51B shape as rowed BfmeAssignRecord32
// erase at 0x00173FB6. Manual EraseRange spelling (Rva002983DA precedent) because
// retail mixes the BfmeAssignRecord36 copy spelling with the Rva0007BB16Record
// destroy spelling for the same 0x24 stride.
struct BfmeAssignRecord36 {
	~BfmeAssignRecord36();
	unsigned char m_pad[36];
};

struct Rva0007BB16Record {
	~Rva0007BB16Record();
	unsigned char m_pad[36];
};

namespace _STL {

struct __false_type {
};

struct random_access_iterator_tag {
};

template <class Type>
class allocator {
};

template <class Type, class Allocator>
class vector {
public:
	typedef Type *iterator;
	iterator erase(iterator first, iterator last);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *extra);

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag)
{
	__false_type local;
	return __copy(first, last, result, reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);

}

class Rva0015229CVector {
public:
	Rva0007BB16Record *EraseRange(Rva0007BB16Record *first, Rva0007BB16Record *last);
private:
	void *m_start;
	Rva0007BB16Record *m_finish;
	void *m_end;
};

Rva0007BB16Record *Rva0015229CVector::EraseRange(Rva0007BB16Record *first, Rva0007BB16Record *last)
{
	BfmeAssignRecord36 *result = _STL::__copy_ptrs((BfmeAssignRecord36 *)last, (BfmeAssignRecord36 *)m_finish, (BfmeAssignRecord36 *)first, _STL::__false_type());
	_STL::_Destroy((Rva0007BB16Record *)result, m_finish);
	m_finish = (Rva0007BB16Record *)result;
	return first;
}
