// cl: /O1 /DNDEBUG /MD
//
// ?equalTag_Rva003B31C7@@YA_NPBX0H@Z,
// retail 0x003B31C7, 24 bytes. Dedicated TU.
//
// Head-tag predicate for the script player-mask writer (0x3B372D calls it
// with the record, a global tag and a spare): memcmp of the first dword,
// nonzero-test folded to a booleanize. The third parameter is dead in
// retail (constant size 4 is pushed first); it is kept so the arity matches
// the caller. No #pragma intrinsic here: retail emits a real E8 to the
// memcmp import thunk (rowed ji_0062929e plus the _memcmp pin), and an
// intrinsic would inline to rep cmpsb instead.

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

// ?equalTag_Rva003B31C7@@YA_NPBX0H@Z
Bool equalTag_Rva003B31C7(const void *record, const void *tag, Int /*unused*/)
{
	return memcmp(record, tag, 4) == 0;
}
