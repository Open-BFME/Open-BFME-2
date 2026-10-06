// cl: /DNDEBUG /MD /EHsc
//
// One unclaimed call-free leaf carried from Open-BFME-1's
// game/GameEngine/Source/Common/UnclaimedSmallLeaves02.cpp (BFME 1 RVA
// 0x00808F50), whose bytes reappear unchanged in game.dat at 0x00674E70.
// Only this body is carried; the donor's other leaves do not place here.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the BFME 1 address.

// now minus +0x1C below 3000
class Rva00808F50
{
public:
	int isRecent( unsigned int now ) const;

	char m_lead[ 0x1C ];
	unsigned int m_1c;
};

int Rva00808F50::isRecent( unsigned int now ) const
{
	return now - m_1c < 3000;
}
