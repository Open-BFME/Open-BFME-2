// cl: /O1
//
// Single-element vector erase @0x000C4657, 55B.
// Masked twin of Rva002A75DA erase @0x002A75DA; 12-byte string-like element.
// Callees: copy 0x0007A401, dtor 0x00142D70 (basic_string).

#pragma comment(linker, "/alternatename:??$__copy_ptrs@PBVRva000C4657Elem@@PAV1@@_STL@@YAPAVRva000C4657Elem@@PBV1@0PAV1@ABU__false_type@0@@Z=??$copy@PBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@PAV12@@_STL@@YAPAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@0@PBV10@0PAV10@@Z")

struct Rva000C4657Elem
{
	char m_pad[12];
};

class Rva00142D70
{
public:
	~Rva00142D70();
};

namespace _STL
{
struct __false_type
{
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag);
}

class Rva000C4657
{
public:
	Rva000C4657Elem *erase(Rva000C4657Elem *position);
	const Rva000C4657Elem *end() { return m_finish; }

private:
	Rva000C4657Elem *m_start;
	const Rva000C4657Elem *m_finish;
	Rva000C4657Elem *m_endOfStorage;
};

Rva000C4657Elem *Rva000C4657::erase(Rva000C4657Elem *position)
{
	_STL::__false_type tag;
	if (position + 1 != end())
		_STL::__copy_ptrs(static_cast<const Rva000C4657Elem *>(position + 1), m_finish, position, tag);
	--m_finish;
	((Rva00142D70 *)m_finish)->~Rva00142D70();
	return position;
}
