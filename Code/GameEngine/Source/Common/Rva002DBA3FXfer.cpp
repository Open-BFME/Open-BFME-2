// cl: /MD
//
// ?rva002DBA3F@Rva002DBA3F@@QAEXPAVXfer@@@Z, retail 0x002DBA3F, 43 bytes.
// __thiscall xfer-style method taking Xfer*: Version1 via rowed 0x000053EE
// then LivingWorldRegionID into +4 via rowed Rva003EFE82Get 0x003EFE82 then
// int at +8 via Xfer slot 0x3C (operator==(int)). Minimal Xfer pads place
// the int overload at slot 15; full donor Xfer lays overloaded == in
// reverse so it lands at 0x7C. Chain lane: calls the just-landed 0x003EFE82.
// Caller 0x002DE072. Prev 0x002DBA19 lea getter / next SaveDate::isNewerThan.
// Honest address name; owner class unproven.
class Xfer
{
public:
	void Version1();
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual class Xfer &operator==(int &value);
};

struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(struct Rva003EFE82Obj *obj, void *out);

struct Rva002DBA3F
{
	char m_pad[4];
	int m_regionID;
	int m_val;
	void rva002DBA3F(class Xfer *xfer);
};

void Rva002DBA3F::rva002DBA3F(class Xfer *xfer)
{
	xfer->Version1();
	Rva003EFE82Get((struct Rva003EFE82Obj *)xfer, &m_regionID);
	*xfer == m_val;
}
