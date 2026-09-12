// ?_heap_abort@@YAXXZ
// partial score=0.8 date=2026-09-12
// cl: /MD /Oy-
//
// _heap_abort, the CRT new-handler / heap-corruption abort routine.
//
// Evidence: retail 0x000398A0 (80 bytes) references the string literal
// "Fatal heap error." -- ZH's debug_debug.cpp (already ported verbatim to
// Code/Libraries/Source/debug/debug_debug.cpp, line ~1637) has:
//   void __cdecl _heap_abort(void) { DCRASH_RELEASE("Fatal heap error."); }
// but ZH's DCRASH_RELEASE macro expands to 4 calls while retail makes 5: it
// first captures its own caller address (read at [ebp+4], i.e.
// _ReturnAddress()) and threads it through an extra CaptureCallSite call.
// This is a documented, already-analyzed BFME macro difference -- see
// reference/open-bfme-1/reverse/re_attempts.log's entry for
// ?_heap_abort@@YAXXZ (BFME1 RVA 0x0088A5F0), which independently derived
// the same five-call chain and the same two vtable shapes (DebugInterface's
// CaptureCallSite/FlushCapture/BeginCrash and CrashStream's Write/Done) by
// the same evidence (this exact string, plus the DCRASH_RELEASE expansion).
// This BFME2 retail body's BeginCrash call pushes three zero args (not
// BFME1's guessed two), so that slot is modeled with three here.
//
// Editing the shared DCRASH_RELEASE macro (debug_macro.h) to capture the
// caller everywhere would touch every DCRASH/DLOG call site in the tree, so
// this body is written out by hand instead, matching retail's five calls
// directly rather than through the macro.

extern "C" void *_ReturnAddress( void );
extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic(_ReturnAddress)
#pragma intrinsic(_ReadWriteBarrier)

// Slot offsets 0x38 (Write) and 0x4C (Done) are proven by this call site
// (this project's Debug singleton, VA 0xDE0880, already returns objects of
// this same shape at those exact offsets from a different call site -- see
// Code/Libraries/Source/profile/profile_cmd_run_result_functions.cpp).
class CrashStream
{
public:
	virtual void _M_slot_00(); virtual void _M_slot_04(); virtual void _M_slot_08();
	virtual void _M_slot_0c(); virtual void _M_slot_10(); virtual void _M_slot_14();
	virtual void _M_slot_18(); virtual void _M_slot_1c(); virtual void _M_slot_20();
	virtual void _M_slot_24(); virtual void _M_slot_28(); virtual void _M_slot_2c();
	virtual void _M_slot_30(); virtual void _M_slot_34();
	virtual CrashStream &Write( const char *text );
	virtual void _M_slot_3c(); virtual void _M_slot_40(); virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void Done( bool die );
};

// Same singleton class as profile_cmd_run_result_functions.cpp's "Debug"
// (VA 0xDE0880), extended here with the three slots this call site proves:
// CaptureCallSite at 0x5C, FlushCapture at 0x60, BeginCrash at 0x6C.
class Debug
{
public:
	virtual void _M_slot_00(); virtual void _M_slot_04(); virtual void _M_slot_08();
	virtual void _M_slot_0c(); virtual void _M_slot_10(); virtual void _M_slot_14();
	virtual void _M_slot_18(); virtual void _M_slot_1c(); virtual void _M_slot_20();
	virtual void _M_slot_24(); virtual void _M_slot_28(); virtual void _M_slot_2c();
	virtual void _M_slot_30(); virtual void _M_slot_34(); virtual void _M_slot_38();
	virtual void _M_slot_3c(); virtual void _M_slot_40(); virtual void _M_slot_44();
	virtual void _M_slot_48(); virtual void _M_slot_4c(); virtual void _M_slot_50();
	virtual void _M_slot_54(); virtual void _M_slot_58();
	virtual void CaptureCallSite( unsigned address, int enabled );
	virtual void FlushCapture( void );
	virtual void _M_slot_64(); virtual void _M_slot_68();
	virtual CrashStream *BeginCrash( int channel, int level, int extra );
};

extern Debug *theDebug;

void __cdecl _heap_abort( void )
{
	unsigned volatile caller = (unsigned)_ReturnAddress();
	theDebug->CaptureCallSite( caller, 1 );
	theDebug->FlushCapture();
	theDebug->BeginCrash( 0, 0, 0 )->Write( "Fatal heap error." ).Done( true );
}
