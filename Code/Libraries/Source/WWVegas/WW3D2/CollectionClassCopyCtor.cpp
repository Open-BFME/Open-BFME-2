// cl: /O2 /G7 /MD
//
// CollectionClass copy constructor, retail 0x00130C00, 307 bytes.
// Dedicated TU so collect.cpp keeps its matched bodies.
// Retail calls RenderObjClass default ctor then memberwise-copies from +0xC4.

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int NumRefs;
};

class PersistClass
{
public:
	virtual ~PersistClass();
};

class RenderObjClass : public RefCountClass, public PersistClass
{
public:
	RenderObjClass();
	virtual ~RenderObjClass();
	unsigned char Pad[0xC4 - 12];
};

class CollectionClass : public RenderObjClass
{
public:
	CollectionClass(const CollectionClass &src);

	int A0;
	int A1;
	char C;
	char PadC[3];
	int B0, B1, B2, B3, B4, B5, B6, B7, B8, B9;
	int B10, B11, B12, B13, B14, B15, B16, B17, B18, B19;
};

CollectionClass::CollectionClass(const CollectionClass &src)
	: RenderObjClass()
{
	A0 = src.A0;
	A1 = src.A1;
	C = src.C;
	B0 = src.B0;
	B1 = src.B1;
	B2 = src.B2;
	B3 = src.B3;
	B4 = src.B4;
	B5 = src.B5;
	B6 = src.B6;
	B7 = src.B7;
	B8 = src.B8;
	B9 = src.B9;
	B10 = src.B10;
	B11 = src.B11;
	B12 = src.B12;
	B13 = src.B13;
	B14 = src.B14;
	B15 = src.B15;
	B16 = src.B16;
	B17 = src.B17;
	B18 = src.B18;
	B19 = src.B19;
}
