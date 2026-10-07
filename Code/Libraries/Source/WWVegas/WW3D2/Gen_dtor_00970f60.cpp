// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	~StringClass() { Free_String(); }
	char *m_buffer;
private:
	void Free_String();
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

class Gen_dtor_00970f60Held
{
public:
	virtual void destroy();
	int m_refs;
};

class Gen_dtor_00970f60 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00970f60();

private:
	Gen_dtor_00970f60Held *m_ptr;
	StringClass m_name;
};

Gen_dtor_00970f60::~Gen_dtor_00970f60()
{
	Gen_dtor_00970f60Held *ptr = m_ptr;
	if (ptr && --ptr->m_refs == 0)
		ptr->destroy();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot00@Rva009EB810TailBase@@UAEXXZ=?get@Rva002A79A1DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?slot04@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot0C@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot14@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot1C@Rva009EB810TailBase@@UAEXXZ=??1Coord2D@@QAE@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot10@Rva009EB810TailBase@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
