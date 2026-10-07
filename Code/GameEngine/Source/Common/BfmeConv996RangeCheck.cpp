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
	bool rva00106781( void **firstOut, int *first, unsigned int *second, char *stop, bool mode );
	bool rva0010694B( void **firstOut, int *first, unsigned int *second );
	int rva00106BC9( int target, int *maximum );
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

// 0x0010694B (37B): target checks this+8 against 6, then forwards the three
// arguments, a byte at the high end of the third argument's stack slot, and
// true to 0x00106781. The callee initializes that output byte before reading
// it. The boundary abuts rva0010690D; the callee body remains blocked and
// unrecovered. The new callee name stays address-derived.
// Retail's EBP prologue and EBP+0x13 stack-byte address require frame pointers.
#pragma optimize("y", off)
bool BfmeB996Range::rva0010694B( void **firstOut, int *first, unsigned int *second )
{
	if ( m_kind == 6 ) {
		return rva00106781( firstOut, first, second, ((char *)&second) + 3, true );
	}
	return false;
}
#pragma optimize("y", on)

class Rva007E3410Object
{
public:
	void invokeForMode();
};

// 0x00106BC9 176B: counted scan over range records. Donor Open-BFME-1
// Rva007E3770BfmeB996ScanCount.cpp Rva007E3770 (same +4 dev/+8 kind, +0x30
// available/cursor, (int)&first pattern, target/max/count/max2 shape).
// invokeForMode row 0x00106A06 shares layout and slot 0x14.
int BfmeB996Range::rva00106BC9( int target, int *maximum )
{
	if ( m_kind == 6 ) {
		int count = 0;
		int initial = m_dev->cursor();
		int first = 0;
		unsigned int second = 0;
		char stop = 0;
		( (Rva007E3410Object *)this )->invokeForMode();
		if ( rva001068D1( (int)&first, &second, &stop ) ) {
			do {
				if ( stop )
					goto fail;
				if ( target == 0 ) {
					++count;
				} else if ( first == target ) {
					if ( *maximum < second )
						*maximum = second;
					++count;
				}
				if ( *maximum < second )
					*maximum = second;
				rva0010690D();
			} while ( rva001068D1( (int)&first, &second, &stop ) );
		}
		if ( stop )
			goto fail;
		m_dev->v5( initial, 1 );
		return count;
fail:
		return 0;
	} else {
		return 0;
	}
}
