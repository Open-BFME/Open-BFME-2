// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeConv996RangeCheck.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// BfmeB996Range::checkRange 0x00106715 (108B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

class BfmeDev996Range
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual int classify( int value, int width );
	virtual void v4(); virtual void v5( int a, int b ); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual int cursor();
};

class BfmeB996Range
{
public:
 	char checkRange( int first, unsigned int *second, char *stop );
 	bool rva001068D1( int first, unsigned int *second, char *third );
 	void rva0010690D();
 	char rva00106A5C();
private:
	char m_pad[ 4 ];
	BfmeDev996Range *m_dev;
	int m_kind;
	int m_limit;
};

// BfmeB996Range::checkRange is defined with its retail-matched body in Code/GameEngine/Source/Common/BfmeConv996RangeCheck.cpp (0x00106715).

// BfmeB996Range::rva001068D1 is defined with its retail-matched body in Code/GameEngine/Source/Common/BfmeConv996RangeCheck.cpp (0x001068D1).

class Rva007E3410Object
{
public:
	void invokeForMode();
};

// 0x00106A5C 109B: loop over rva001068D1 with advance rva0010690D and mode invokes.
// Donor Open-BFME-1 Rva007E34C0BfmeB996RangeLoop.cpp rva007e34c0 (same layout,
// (int)&probe pattern, success+flag tail). invokeForMode row 0x00106A06 shares
// +4 target/+8 mode layout and slot 0x14. Caller at 0x00106B56.
char BfmeB996Range::rva00106A5C()
{
	char flag = 0;
	char done = 0;
	( (Rva007E3410Object *)this )->invokeForMode();
	int probe;
	unsigned int arg;
	while ( rva001068D1( (int)&probe, &arg, &flag ) ) {
		if ( flag != 0 )
			break;
		rva0010690D();
		done = 1;
	}
	if ( done == 0 || flag != 0 )
		return 0;
	( (Rva007E3410Object *)this )->invokeForMode();
	return 1;
}
