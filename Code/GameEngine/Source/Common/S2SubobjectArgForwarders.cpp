// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Two __cdecl two-argument functions that hand their second argument to a
// __thiscall member of a sub-object of their first:
//
//     mov eax,[esp+8] / mov ecx,[esp+4] / push eax / add ecx,<OFFSET>
//     call <REL32> / ret
//
// WHAT THE BYTES SHOW.  The receiver is formed by loading the owner into ecx
// and ADDING the offset, not by `lea ecx,[reg+OFFSET]` off a separate copy:
// that is the encoding you get when the source names the owner ONCE, so the
// expression is not independent and there is nothing for the compiler to fold.
// The callee is reached with one dword on the stack and the caller pops
// nothing, so it is __thiscall with a single argument.  Nothing is popped after
// the call and nothing is done with eax, so this function returns void.
//
// ONE CALLEE, TWO OFFSETS: 0x0C and 0x04, both through the thunk at 0x0001581B
// (body 0x00065090), so one sub-object class covers both rows.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived and the forwarded
// argument is typed as an opaque pointer because it is only ever a dword.

class GenForwardedArg
{
public:
	int m_x;
};

// The sub-object member is the already-matched 21-byte wrapper at retail
// 0x005045C6, rowed as ?rva005045C6@Rva005045C6@@QAEXABVRva00064640Record@@@Z
// and chaining into the rowed set insert 0x005045A3.  It is __thiscall with
// one argument, so one declaration of it serves both offsets; the forwarded
// argument is only ever a dword, so it is typed as an opaque pointer here and
// the class is named for the address it is pinned at.
class Rva00064640Record;
class Rva005045C6
{
public:
	void rva005045C6( const Rva00064640Record &a );
};

#define BFME_SUBOBJECT_ARG_FORWARDER( NAME, OFFSET )                      \
	class NAME##Owner                                                     \
	{                                                                     \
	public:                                                               \
		char m_lead[ OFFSET ];                                            \
		Rva005045C6 m_sub;                                                \
	};                                                                    \
	void NAME( NAME##Owner *owner, GenForwardedArg *a )                   \
	{                                                                     \
		owner->m_sub.rva005045C6( *(const Rva00064640Record *)a );       \
	}

// @?Rva003B7140@@YAXPAVRva003B7140Owner@@PAVGenForwardedArg@@@Z 0x003B7140
BFME_SUBOBJECT_ARG_FORWARDER( Rva003B7140, 0x04 )
// @?Rva003B70F0@@YAXPAVRva003B70F0Owner@@PAVGenForwardedArg@@@Z 0x003B70F0
BFME_SUBOBJECT_ARG_FORWARDER( Rva003B70F0, 0x0C )
