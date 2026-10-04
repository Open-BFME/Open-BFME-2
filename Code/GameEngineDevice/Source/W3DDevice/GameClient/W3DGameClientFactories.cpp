// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// Nine more factory slots of vtable 0x00BC4738 (class Rva004C743, the game
// client whose slots 48 and 49 Rva0004C662Factory.cpp holds), each Zero
// Hour's W3DGameClient `return NEW X;` shape: operator new of the product's
// size, then its constructor, under an EH frame that frees the block if the
// constructor throws. Same flags as Rva0004C662Factory.cpp.
//
// Products are named after the ledger's name for the vtable their
// constructor stores, else after the constructor. One is identified: slot 45
// (0x0004C709) is Zero Hour's createMouse, which also stores the new mouse in
// TheWin32Mouse (0x00DE1B18) "for the WndProc"; its 0x60A8-byte product is
// named W3DMouse after that (inferred).
//
//   factory     new     ctor        vtable      product
//   0x0004C45D  0x2B0  0x00049DEA  0x00BC3C80  Rva00049DEAProduct
//   0x0004C492  0xAC0  0x0008EF3F  0x00BC7A88  Rva0008EF3FProduct
//   0x0004C4C7  0x40  0x0008FC51  0x00BC7C90  Rva008FCA3
//   0x0004C553  0x40  0x00090360  0x00BC7E20  Rva00090360
//   0x0004C5C6  0x24  0x00091A80  0x00BC80A0  Rva00091A80Product
//   0x0004C62D  0x108  0x0009525E  0x00BC8208  Rva0009525EProduct
//   0x0004C694  0x68  0x00098667  0x00BC8358  Rva00098667Product
//   0x0004C709  0x60A8  0x00098E69  0x00BC86D8  W3DMouse
//   0x0004C8DD  0x1D4  0x0009D55B  0x00BC89C8  Rva0009D55BProduct

class Rva00049DEAProduct
{
public:
	Rva00049DEAProduct();
private:
	char m_unmodelled[0x2B0];
};

class Rva0008B7CFProduct
{
public:
	Rva0008B7CFProduct();
private:
	char m_unmodelled[0x2508];
};

// Slot 118 of this product's vtable 0x00BC7A88 (0x0008EFD8) is itself a
// factory of the same shape: new 0x2508 bytes and the constructor 0x0008B7CF
// (pinned).
class Rva0008EF3FProduct
{
public:
	Rva0008EF3FProduct();
	void *rva0008EFD8();
private:
	char m_unmodelled[0xAC0];
};

void *Rva0008EF3FProduct::rva0008EFD8()
{
	return new Rva0008B7CFProduct;
}

class Rva008FCA3
{
public:
	Rva008FCA3();
private:
	char m_unmodelled[0x40];
};

class Rva00090360
{
public:
	Rva00090360();
private:
	char m_unmodelled[0x40];
};

class Rva00091A80Product
{
public:
	Rva00091A80Product();
private:
	char m_unmodelled[0x24];
};

class Rva0009525EProduct
{
public:
	Rva0009525EProduct();
private:
	char m_unmodelled[0x108];
};

class Rva00098667Product
{
public:
	Rva00098667Product();
private:
	char m_unmodelled[0x68];
};

class Win32Mouse
{
private:
	char m_unmodelled[0x60A8];
};

class W3DMouse : public Win32Mouse
{
public:
	W3DMouse();
};

extern Win32Mouse *TheWin32Mouse;

class Rva0009D55BProduct
{
public:
	Rva0009D55BProduct();
private:
	char m_unmodelled[0x1D4];
};

class Rva004C743
{
public:
	void *rva0004C45D();
	void *rva0004C492();
	void *rva0004C4C7();
	void *rva0004C553();
	void *rva0004C5C6();
	void *rva0004C62D();
	void *rva0004C694();
	Win32Mouse *rva0004C709();
	void *rva0004C8DD();
};

void *Rva004C743::rva0004C45D()
{
	return new Rva00049DEAProduct;
}

void *Rva004C743::rva0004C492()
{
	return new Rva0008EF3FProduct;
}

void *Rva004C743::rva0004C4C7()
{
	return new Rva008FCA3;
}

void *Rva004C743::rva0004C553()
{
	return new Rva00090360;
}

void *Rva004C743::rva0004C5C6()
{
	return new Rva00091A80Product;
}

void *Rva004C743::rva0004C62D()
{
	return new Rva0009525EProduct;
}

void *Rva004C743::rva0004C694()
{
	return new Rva00098667Product;
}

// Zero Hour's createMouse.
Win32Mouse *Rva004C743::rva0004C709()
{
	Win32Mouse *mouse = new W3DMouse;
	TheWin32Mouse = mouse;	///< global cheat for the WndProc()
	return mouse;
}

void *Rva004C743::rva0004C8DD()
{
	return new Rva0009D55BProduct;
}
