// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?Rva00180782@Gen_dtor_00972460@@UAEXXZ, retail 0x00180782, 18 bytes. Virtual
// slot 6 (offset 0x18) of vtable 0x007D5010 (class of ??1Gen_dtor_00972460@@UAE@XZ):
// deletes m_ptr at +0x14 and nulls it. Evidence: dtor at 0x00180734 deletes
// the same pointer plus Free_String; ctor at 0x00180847 sets m_ptr to 0;
// loader slot 2 at 0x001808B0 allocates 0x44 for BOX chunk 0x740 into m_ptr;
// Create slot 15 at 0x00180794 builds AABox/OBBox from it. No callers.
// Callee operator delete resolves through rowed 0x0002FD60.
//
// Donor layout: Gen_dtor_00972460.cpp (Rva009EB810TailBase plus m_ptr plus
// StringClass m_name); honest address name since slot-to-method mapping is
// unproven.

void __cdecl operator delete(void *);

class StringClass
{
	void Free_String();
	friend class Gen_dtor_00972460;
	char *m_buffer;
};

class Rva009EB810TailBase
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual ~Rva009EB810TailBase();

private:
	char m_pad[0x10];
};

class Gen_dtor_00972460 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00972460();
	virtual void Rva00180782();

private:
	void *m_ptr;
	StringClass m_name;
};

void Gen_dtor_00972460::Rva00180782()
{
	operator delete(m_ptr);
	m_ptr = 0;
}
