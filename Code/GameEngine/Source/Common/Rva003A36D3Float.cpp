// cl: /MD
// ?rva003A36D3@Rva003A36D3@@UAEMH@Z, retail 0x003A36D3, 36 bytes.
// Slot 8 (offset 0x20) of several vtables (e.g. 0x0086E270 class of ??1Rva00573B23). Returns first slot-9 float/int call divided by second slot-10 float/int call via x87 fdivr.
// Layout: base with 8 dummy virtuals to place this at slot 8 and callees at 0x24/0x28. Evidence: leaf packet EBP frame plus fstp/fdivr plus ret 4; virtual calls need no rows.
// Precedent float-division shape with neighbouring virtual slots.
class Rva003A36D3Base
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
};

class Rva003A36D3 : public Rva003A36D3Base
{
public:
	virtual float rva003A36D3(int arg);
	virtual float v9(int arg);
	virtual float v10(int arg);
};

float Rva003A36D3::rva003A36D3(int arg)
{
	float a = v9(arg);
	float b = v10(arg);
	return a / b;
}
