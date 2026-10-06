// cl: /Ob1 /DNDEBUG /MD
// BFME retail 0x001B3A20: virtual-base constructor shape.

class BfmeCtorFirstBase001B3A20
{
public:
	virtual void slot() = 0;
};

class BfmeCtorVirtualBase001B3A20
{
public:
	virtual void slot() = 0;
};

class BfmeCtor001B3A20 : public BfmeCtorFirstBase001B3A20,
	public virtual BfmeCtorVirtualBase001B3A20
{
public:
	BfmeCtor001B3A20();
};

BfmeCtor001B3A20::BfmeCtor001B3A20()
{
}

// ??0Rva003058F9@@QAE@XZ, retail 0x003058F9, 46 bytes: the same constructor for
// another class over the same two bases. Only the derived vftable it stores
// (VA 0xc4ef80) differs; the virtual-base table (VA 0xc74ed4) and the virtual
// base's vftable (VA 0xc078dc) are the template's, folded in retail since
// their contents are identical. Identity is not recovered.
class Rva003058F9 : public BfmeCtorFirstBase001B3A20,
	public virtual BfmeCtorVirtualBase001B3A20
{
public:
	Rva003058F9();
};

Rva003058F9::Rva003058F9()
{
}
