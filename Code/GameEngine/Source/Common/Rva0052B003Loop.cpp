// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
// ?rva0052B003@Holder0052B003@@QAEXH@Z @0x0052B003 33B
// Pointer-range loop: for each Obj* from +0x2C to +0x30 call pinned
// 0x005C4180 with the int arg.
// The ledger row at 0x005C4180 is Rva005C41C9::rva005C4180(unsigned char).
class Rva005C41C9
{
public:
	virtual ~Rva005C41C9();
	void rva005C4180(unsigned char value);
};

struct Obj0052B003
{
};

struct Holder0052B003
{
	char m_pad[0x2C];
	Obj0052B003 **m_2C; // +0x2C
	Obj0052B003 **m_30; // +0x30
	void rva0052B003(int value);
};

void Holder0052B003::rva0052B003(int value)
{
	Obj0052B003 **begin = m_2C;
	Obj0052B003 **end = m_30;
	for (Obj0052B003 **p = begin; p != end; ++p)
		((Rva005C41C9 *)*p)->rva005C4180((unsigned char)value);
}

// Same building-icon pointer range at +0x2C/+0x30. Target52B23D..52B278
// proves virtual destruction with global delete, followed by vector erase.
// WorldBuilder1073A60 supplies the same complete loop. Element application
// identity remains opaque; the vector stores erased pointers to these objects.
class Rva0052B23D
{
	char m_pad[0x2C];
	_STL::vector<void *> m_items;
public:
	void rva0052B23D();
};

void Rva0052B23D::rva0052B23D()
{
	_STL::vector<void *>::iterator end = m_items.end();
	_STL::vector<void *> &items = m_items;
	for (_STL::vector<void *>::iterator it = items.begin(); it != end; ++it)
		::delete (Rva005C41C9 *)*it;
	items.erase(items.begin(), items.end());
}
