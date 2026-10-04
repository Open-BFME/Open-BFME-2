// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
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

char BfmeB996Range::checkRange( int first, unsigned int *second, char *stop )
{
	int firstClass = m_dev->classify( first, 4 );
	*stop = 0;
	if ( firstClass != 4 ) {
		if ( firstClass != 0 ) {
			*stop = 1;
		}
		return 0;
	}

	int secondClass = m_dev->classify( (int)second, 4 );
	unsigned int remaining = m_limit - m_dev->cursor();
	if ( secondClass == 4 && *second >= 8 && *second - 8 <= remaining ) {
		return 1;
	}
	*stop = 1;
	return 0;
}

bool BfmeB996Range::rva001068D1( int first, unsigned int *second, char *third )
{
	if ( m_kind == 6 ) {
		if ( checkRange( first, second, third ) != 0 ) {
			if ( *third == 0 ) {
				m_dev->v5( -8, 1 );
				return true;
			}
		}
	}
	return false;
}

// 0x0010690D 62B: void advance step; calls rva001068D1 with stack probe/arg/flag
// then v5(arg,1). Donor Open-BFME-1 Rva007E34C0BfmeB996RangeLoop.cpp bfmeAdvance996
// (same layout +4 dev/+8 kind, (int)&probe pattern); callers at 0x000911B2 etc.
void BfmeB996Range::rva0010690D()
{
	if ( m_kind == 6 ) {
		int probe;
		unsigned int arg;
		char flag = 0;
		if ( rva001068D1( (int)&probe, &arg, &flag ) && flag == 0 ) {
			m_dev->v5( arg, 1 );
		}
	}
}

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
