// cl: /MD /EHsc
// ??1Rva005DAC85@@UAE@XZ @0x005DAC85 59B evidence: vtable VA 0x008765F8 at +0; StringBase char releaseBuffer at +0x3C via 0x00036410; base Rva0055B0CC dtor pin at 0x0055B0CC; unblocks deleting dtor 0x005DADD1

template <typename T>
class StringBase
{
	friend class Rva005DAC85;
private:
	void releaseBuffer();
	void *m_data;
};

class Rva0055B0CC
{
	friend class Rva005DAC85;
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(void *xfer, void *arg2);
	virtual ~Rva0055B0CC();
private:
	float m_04;
	int m_08;
	void *m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	int m_24;
	bool m_28;
};

class Rva005DAC85 : public Rva0055B0CC
{
public:
	virtual ~Rva005DAC85();
private:
	char m_pad2C[0x10];
	StringBase<char> m_3C;
};

Rva005DAC85::~Rva005DAC85()
{
	m_3C.releaseBuffer();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?slot0@Rva0055B0CC@@UAEXXZ=??_GRva005DAC85@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?slot4@Rva0055B0CC@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot7@Rva0055B0CC@@UAEXXZ=?friend_setNext@Upgrade@@QAEXPAV1@@Z")
#pragma comment(linker, "/alternatename:?slot11@Rva0055B0CC@@UAEXXZ=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?Rva0055AED6@Rva0055B0CC@@UAEXPAX0@Z=?Rva0055AED6@Rva0055B0CC@@UAEXPAVXfer@@PAX@Z")
