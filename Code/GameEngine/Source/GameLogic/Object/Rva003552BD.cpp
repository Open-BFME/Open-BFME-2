// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva003552BDJump@@YAXXZ @0x003552BD 5B
// Evidence: 5B jmp to rowed dup_00355257; callers are Unwind funclets
void __cdecl dup_00355257();
void __cdecl Rva003552BDJump()
{
	dup_00355257();
}
