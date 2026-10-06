// cl: /O1 /DNDEBUG /MD
// ?rva00346C53@Rva00346C53@@QAEXW4ObjectStatusTypes@@_N@Z @0x00346C53 35B.
// Void status-mask applier (thiscall, enum plus bool): builds a 16B
// ObjectStatusMask on the frame through the rowed 3-arg 0x23DA79 builder
// and hands the resulting mask to the 0x293D3B hook on this. Both callees
// ride address-derived pins.
enum ObjectStatusTypes
{
	OBJECT_STATUS_00 = 0
};

struct ObjectStatusMask
{
public:
	ObjectStatusMask *Rva0023DA79(int a, ObjectStatusTypes b, bool c);

private:
	char m_data[16];
};

class Rva00346C53
{
public:
	void rva00346C53(ObjectStatusTypes a, bool b);
	void rva00293D3B(ObjectStatusMask *m);
};

void Rva00346C53::rva00346C53(ObjectStatusTypes a, bool b)
{
	ObjectStatusMask mask;
	rva00293D3B(mask.Rva0023DA79(0, a, b));
}
