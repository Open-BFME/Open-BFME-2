/* A small CALENDAR DATE class sitting just below the DirtySock text helpers.
 * It is a separate translation unit from those because it is built with
 * OPTIMISATION ON: no /GZ local fill, no frame pointer, a switch lowered to an
 * index byte table plus a jump table, and a modulo folded into `and eax,
 * 0x80000003` with a sign fixup.  The socket and text units are /Od /GZ, so
 * this cannot share a file with them.
 *
 * THE OBJECT LAYOUT COMES FROM THE THREE BODIES AGREEING.  The constructor
 * writes +0x00 and +0x08 and passes 1 to the day setter; the setter validates
 * against a per-month length and writes +0x04; and the leap-year test is
 * handed +0x08.  So +0x00 is the month, +0x04 the day, +0x08 the year, and
 * nothing here is inferred from field order alone.
 */

/* Not a member: the setter loads the YEAR VALUE into ecx before calling, where
 * a member call would have loaded the object pointer.  One integer argument in
 * ecx and nothing on the stack is __fastcall. */
bool __fastcall Rva007FF3F0IsLeapYear( int year );

struct Rva007FF700Date
{
	int m_month;    /* +0x00 */
	int m_day;      /* +0x04 */
	int m_year;     /* +0x08 */

	Rva007FF700Date();
	int setDay( int day );
	int setMonth( int month );
	int setYear( int year );
	int setDate( int month, int day, int year );
};

/* The ordinary rule, and the bytes show all three tests: divisible by four,
 * except centuries, except every fourth century.  The first test compiles to
 * `and eax, 0x80000003` with a decrement/or/increment fixup rather than a
 * divide -- that fixup is what makes it correct for NEGATIVE years, which a
 * plain mask would get wrong. */
// Rva007FF3F0IsLeapYear: defined in Y4DirtySockDate.cpp (its row's unit).
bool __fastcall Rva007FF3F0IsLeapYear( int year );

/* Default state is 1 January 1900.  The day goes in through the setter rather
 * than by direct assignment, so it is range-checked like any other day. */
// Rva007FF700Date::Rva007FF700Date: defined in Y4DirtySockDate.cpp (its row's unit).

/* Returns 0 on success, -2 for a day outside the month, and -1 for a month
 * that is not 1..12 -- so the two failures are DISTINGUISHABLE, which matters
 * because an out-of-range day leaves a valid object while a bad month means
 * the object was already inconsistent.
 *
 * February's length is 28 plus the leap flag, computed as an arithmetic
 * conversion of the bool rather than a branch.
 */
// Rva007FF700Date::setDay: defined in Y4DirtySockDate.cpp (its row's unit).

int Rva007FF700Date::setMonth( int month )
{
	if ( month > 0 && month < 13 )
	{
		m_month = month;
		return 0;
	}
	return -1;
}

int Rva007FF700Date::setYear( int year )
{
	if ( year >= 1900 )
	{
		m_year = year;
		return 0;
	}
	return -3;
}

// Complete retail body at 0x0066B9C0 (BFME 1 0x007FF4F0): the month/year
// validation helpers inline before the call to setDay. Keeping their result
// tests preserves retail's separate month (-1) and year (-3) failure tails.
// The unit builds at plain /O2 for this: under /Ob1 the two helpers, which
// must also stay out of line for their own rows, are called instead.
int Rva007FF700Date::setDate( int month, int day, int year )
{
	int result;
	if ( (result = setMonth( month )) != 0 )
		return result;
	if ( (result = setYear( year )) != 0 )
		return result;
	return setDay( day );
}
