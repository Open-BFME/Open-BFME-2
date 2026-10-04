// cl: /O1 /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 GameNetwork/GameSpy/Thread/GetNickForMessage.cpp
// at 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24, the whole one-body donor.
// Its nickname callback role is supported by native messageCallback 00551139:
// operand 00551157 passes this address to rowed gpGetInfo 0072C390.
// Native 00550639/24 begins after the complete 5-byte thunk at 00550634 and
// ends at its own RET immediately before 00550651. It copies from argument 2
// plus 8 to argument 3 plus 10 using the actual msvcr71 _mbscpy thunk 629176.
// The donor's strcpy spelling is adapted to that proven native import.
// Names follow the donor and existing caller declaration; buffer capacities
// and complete application record layouts are deliberately not asserted.

class GPConnection;
struct GPGetInfoResponseArg;
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *, const unsigned char *);

void getNickForMessage(GPConnection *, GPGetInfoResponseArg *arg, void *param)
{
    _mbscpy((unsigned char *)param + 0x10, (const unsigned char *)arg + 8);
}
