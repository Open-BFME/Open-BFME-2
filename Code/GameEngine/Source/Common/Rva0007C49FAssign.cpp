// cl: /O1 /EHs /MD
//
// ??4Rva0007C49F@@QAEAAV0@ABV0@@Z @0x0007C49F 37B: memberwise assignment of a
// CameraClass-derived class (vtables 0x00BC6C58/0x00BC6C54 in its copy ctor
// 0x0007C404 and dtor 0x0007C454, class not recovered) whose only own member is
// a vector<BfmeFloat4Record00469C61> at +0x3FC: CameraClass::operator= (rowed
// 0x00135010) then the rowed vector assignment 0x0007C316. Assignment does not
// touch the vptrs, so the vtables are not needed here. Name is address-derived.

class CameraClass
{
public:
	CameraClass &operator=(const CameraClass &other);

private:
	char m_pad000[0x3FC];
};

struct BfmeFloat4Record00469C61;

namespace _STL
{
template <class T>
class allocator;

template <class T, class Alloc = allocator<T> >
class vector
{
public:
	vector<T, Alloc> &operator=(const vector<T, Alloc> &other);

private:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};
}

class Rva0007C49F : public CameraClass
{
public:
	Rva0007C49F &operator=(const Rva0007C49F &other);

private:
	_STL::vector<BfmeFloat4Record00469C61> m_records;
};

Rva0007C49F &Rva0007C49F::operator=(const Rva0007C49F &other)
{
	CameraClass::operator=(other);
	m_records = other.m_records;
	return *this;
}
