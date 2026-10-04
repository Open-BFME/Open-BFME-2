// ?Rva0033F9FECheck@@YA_NPAVObject@@PBUCoord3D@@PAX@Z
// partial score=0.94 date=2026-10-04
// cl: /O1 /EHsc /MD
// ?Rva0033F9FECheck@@YA_NPAVObject@@PBUCoord3D@@PAX@Z RVA 0x0033F9FE 102B
// Evidence: chain from 0x0026163A; free function with EH_prolog; guards via Rva002C9400ByteField::get
//   and Xfer::IsStoring on [esi+4]; stack filter (vtable 0x00C07150 Rva002619C1Filter : Rva000421C8,
//   m_next=0 + m_obj) calling Rva0026163A::rva0026163A.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Xfer
{
public:
	virtual bool IsStoring() const;
};

class Rva0026163A
{
public:
	bool rva0026163A(const Coord3D *target);
};

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	Rva000421C8 *m_next;
};

class Rva002619C1Filter : public Rva000421C8
{
public:
	Rva002619C1Filter(Object *o) : m_obj(o) {}
	Object *m_obj;
};

struct Rva0033F9FEHolder
{
	char _00[4];
	void *m_4;
};

// ?Rva0033F9FECheck@@YA_NPAVObject@@PBUCoord3D@@PAX@Z present-unmatched
bool Rva0033F9FECheck(Object *arg1, const Coord3D *arg2, void *arg3)
{
	Rva0033F9FEHolder *holder = (Rva0033F9FEHolder *)arg3;
	if (holder == 0 || arg2 == 0
		|| ((Rva002C9400ByteField *)holder->m_4)->get() != 0
		|| ((Xfer *)holder->m_4)->Xfer::IsStoring())
		return true;
	Rva002619C1Filter tmp(arg1);
	if (((Rva0026163A *)&tmp)->rva0026163A(arg2) == false)
		return false;
	return true;
}
