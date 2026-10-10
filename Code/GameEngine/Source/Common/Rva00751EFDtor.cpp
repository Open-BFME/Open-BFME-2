// cl: /O1 /MD /EHsc
// ??1Rva00751EF@@UAE@XZ, retail 0x000751EF..0x00075279 (138 bytes, EH):
// the destructor the rowed scalar deleting destructor ??_GRva00751EF calls
// (call at 0x0007527C; table 0x00BC6620 slot 0). It hands the
// +0x28 display string back to TheDisplayStringManager (slot 15) when both
// exist, releases and clears the five reference-counted pointers at +0x11C,
// clears the static at 0x00DE1ED0, then the twenty 0x0C-byte records at
// +0x2C die through the eh vector destructor iterator with the shared
// first-pointer-free body 0x0007FAB3, and the vptr falls back to the base
// table 0x00BC65A8 (deleting destructor plus three pure slots). Owner
// identity and field roles are not established; names stay address-derived.
class Rva00074626
{
public:
	virtual ~Rva00074626() {}
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
};

struct Rva000751EFSlot
{
	~Rva000751EFSlot();
	unsigned char m_data[0x0C];
};

class Rva000751EFRef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

class DisplayStringManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void freeDisplayString(void *string);
};
extern DisplayStringManager *TheDisplayStringManager;

extern void *g_00DE1ED0;

class Rva00751EF : public Rva00074626
{
public:
	virtual ~Rva00751EF();
private:
	unsigned char m_pad04[0x28 - 4];
	void *m_string28;			// +0x28
	Rva000751EFSlot m_slots[20];		// +0x2C
	Rva000751EFRef *m_refs[5];		// +0x11C
};

Rva00751EF::~Rva00751EF()
{
	if (m_string28 && TheDisplayStringManager)
		TheDisplayStringManager->freeDisplayString(m_string28);
	for (int i = 0; i < 5; ++i)
	{
		if (m_refs[i])
		{
			m_refs[i]->Release_Ref();
			m_refs[i] = 0;
		}
	}
	g_00DE1ED0 = 0;
}
