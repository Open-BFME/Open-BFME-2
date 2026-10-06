// cl: /MD
//
// ?rva001DBCC0@Rva001DBC77@@QAEPAXI@Z retail 0x001DBCC0 28B. Deleting helper
// for the rowed dtor 0x001DBC77: destroys via that dtor then frees with rowed
// operator delete when flags bit0 is set. Evidence: chain caller of landed
// 0x001DBC77 plus rowed delete 0x0002FD60. Honest address name on proven owner.
void __cdecl operator delete(void *p);

class Rva001DBC77
{
public:
	~Rva001DBC77();
	void *rva001DBCC0(unsigned int flags);
};

void *Rva001DBC77::rva001DBCC0(unsigned int flags)
{
	this->~Rva001DBC77();
	if (flags & 1)
		::operator delete(this);
	return this;
}
