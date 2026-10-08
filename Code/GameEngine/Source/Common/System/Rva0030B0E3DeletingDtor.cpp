// cl: /MD
// ?rva0030B119@Rva0030B0E3@@QAEPAXI@Z, retail 0x0030B119, 28 bytes.
// Calls rowed 0x0007461F plus rowed operator delete 0x0002FD60; shape matches deleting dtor slot 0 of vtable 0x00808830.
// Evidence: adjacent to ??0Rva0030B0E3 ctor storing vtable 0x00808830; vtable slot 0 points here.
// 0x0007461F is the rowed empty dtor ??1Rva00074626@@UAE@XZ.
class Rva00074626
{
public:
	virtual ~Rva00074626();
};

void __cdecl operator delete(void *);

class Rva0030B0E3
{
public:
	void *rva0030B119(unsigned int flags);
};

void *Rva0030B0E3::rva0030B119(unsigned int flags)
{
	((Rva00074626 *)this)->Rva00074626::~Rva00074626();
	if (flags & 1)
		::operator delete(this);
	return this;
}
