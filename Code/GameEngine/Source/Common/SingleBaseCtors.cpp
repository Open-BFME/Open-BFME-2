// cl: /DNDEBUG /MD /EHsc
//
// Wave-3 F24 shape family: single-base constructors forwarding one int (or
// the constant 1) to a pinned base constructor, then stamping the derived
// vtable and returning `this`. Identities beyond these shapes are not
// recovered.
//

class Rva003FAE68Base
{
public:
	Rva003FAE68Base(int a);
	virtual void f0() = 0;
};

class Rva00210EF1 : public Rva003FAE68Base
{
public:
	Rva00210EF1(int a);
};

Rva00210EF1::Rva00210EF1(int a) : Rva003FAE68Base(a)
{
}

class Rva003B0454Base
{
public:
	Rva003B0454Base(int a);
	virtual void f0() = 0;
};

class Rva003B0835 : public Rva003B0454Base
{
public:
	Rva003B0835(int a);
};


class Rva005D5095Base
{
public:
	Rva005D5095Base(int a);
	virtual void f0() = 0;
};

class Rva005D50C4 : public Rva005D5095Base
{
public:
	Rva005D50C4();
};

Rva005D50C4::Rva005D50C4() : Rva005D5095Base(1)
{
}

// ??0Rva005D50E3@@QAE@XZ retail 0x005D50E3 20B
// Evidence: leaf lane; base Rva005D5095Base(0) pin plus vtable 0x00875AFC; caller 0x005AE368; sibling Rva005D50C4 same TU same flags.
class Rva005D50E3 : public Rva005D5095Base
{
public:
	Rva005D50E3();
};

Rva005D50E3::Rva005D50E3() : Rva005D5095Base(0)
{
}
