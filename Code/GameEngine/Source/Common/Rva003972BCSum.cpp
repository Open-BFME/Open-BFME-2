// cl: /DNDEBUG /MD
//
// ?rva003972BC@Rva003972BC@@QAEHXZ, retail 0x003972BC, 23 bytes.
// Sums the sibling ObjectID-range counts at 0x00397238 (+0x50/+0x54) and
// 0x0039727A (+0x74/+0x78) on the same object.
// Evidence: calls rowed ?rva00397238@Rva00397238@@QAEHXZ and
// ?rva0039727A@Rva0039727A@@QAEHXZ; prev/next share /O1 /DNDEBUG /MD.

class Rva00397238
{
public:
	int rva00397238();
};

class Rva0039727A
{
public:
	int rva0039727A();
};

class Rva003972BC
{
public:
	int rva003972BC();
};

int Rva003972BC::rva003972BC()
{
	int first = static_cast<Rva00397238 *>((void *)this)->rva00397238();
	int second = static_cast<Rva0039727A *>((void *)this)->rva0039727A();
	return first + second;
}
