// cl: /Od /MD /EHsc

// VC7's <new> declares std::bad_alloc's destructor inline, so including it
// cannot emit the retail out-of-line body.  This TU keeps the ABI-bearing
// declaration local: the retail Ghidra boundary names std::bad_alloc, its
// vptr is the standard derived exception vptr, and the base destructor is the
// imported VC7 std::exception destructor.
namespace std {
class exception
{
public:
	virtual __declspec(dllimport) ~exception();
};

class bad_alloc : public exception
{
public:
	virtual ~bad_alloc();
};

bad_alloc::~bad_alloc()
{
}
}
