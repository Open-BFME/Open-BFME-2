// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs-c- -Ireference/open-bfme-1/game/GameEngine/Source/Common

// ?movePair@BfmeB996@@QAEDPAH0PAII@Z
// retail 0x00106812, 98 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva007E3080MovePair.cpp
// (reference/open-bfme-1), recompiled /Os: byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text). Only
// the placed body is defined here; the donor's other definitions are omitted.
//
// The three-argument guard is the already-matched 108-byte
// ?checkRange@BfmeB996Range@@QAEDHPAIPAD@Z at 0x00106715
// (Code/GameEngine/Source/Common/BfmeConv996RangeCheck.cpp), reached under
// the same complete-object pointer; it writes the `stop` byte through its third
// argument, which is why this body tests it after the call.

class BfmeDev996
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual int classify( int value, int width );
};

// Call-only view of the already verified guard owner. Native call 0x10682B
// passes the unadjusted this pointer; both views locate the device at +4.
class BfmeB996Range
{
public:
	char checkRange(int first, unsigned int *second, char *stop);
};

class BfmeB996
{
public:
	char movePair( int *output, int *first, unsigned int *second,
		unsigned int limit );

private:
	char m_pad[ 4 ];
	BfmeDev996 *m_dev;
};

char BfmeB996::movePair( int *output, int *first,
	unsigned int *second, unsigned int limit )
{
	char stop = 0;
	if ( !reinterpret_cast<BfmeB996Range *>(this)->checkRange( (int)first, second, &stop ) ||
		stop || *second > limit ) {
		return 0;
	}
	int firstValue = *first;
	int *destination = output;
	destination[ 0 ] = firstValue;
	destination[ 1 ] = *second;
	BfmeDev996 *dev = m_dev;
	return dev->classify( (int)( destination + 2 ), *second - 8 ) ==
		*second - 8;
}
