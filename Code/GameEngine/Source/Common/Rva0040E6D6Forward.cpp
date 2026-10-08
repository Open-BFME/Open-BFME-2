// cl: /MD
//
// Null-guarded member forward at retail 0x0040E6D6 (32B). Reads the
// argument's +0x1C word into the argument slot, then forwards the slot's
// address to the +0x14 subobject's method (pinned retail 0x002E01C6).
// __fastcall member: the middle int parameter rides in EDX and is not
// consulted on this path; the callee pops the one stack arg. Names are
// address-derived.
// The callee is the rowed STLport vector<ScienceType>::push_back.
enum ScienceType { SCIENCE_INVALID_0040E6D6 = -1 };
namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}
class Rva0040E6D6Sub
{
};

struct Rva0040E6D6Arg
{
	char m_00[0x1C];
	int m_1C;
};

class Rva0040E6D6Host
{
public:
	void __fastcall forwardFrom(int unused, Rva0040E6D6Arg *arg); // retail 0x0040E6D6

private:
	char m_00[0x14];
	Rva0040E6D6Sub m_14; // +0x14
};

void __fastcall Rva0040E6D6Host::forwardFrom(int unused, Rva0040E6D6Arg *arg)
{
	if (arg == 0) {
		return;
	}
	ScienceType slot = (ScienceType)arg->m_1C;
	((_STL::vector<ScienceType> *)&m_14)->push_back(slot);
}
