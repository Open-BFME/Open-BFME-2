// cl: /DNDEBUG /MD

// 0x000387C0, 12 bytes: returns the byte at +0x9F57 of the Debug singleton
// that the pointer at 0x00DE0880 names.  It sits among the Debug library's
// bodies and BFME_DX8_Thread_Lock at 0x0011F520 calls it to decide whether
// to report its twenty-second timeout.  Its own unit, because a definition in
// the lock's unit is inlined into the lock, where retail keeps the call.  The
// Debug model is reduced to its vtable pointer and the flag; the name is
// address-derived since the member's identity is not recovered.

class Debug
{
public:
	virtual void _M_slot_00();

	char m_bfme0004[0x9F53];
	bool m_bfme9F57;
};

extern Debug *theDebug;

bool bfmeRva000387C0()
{
	return theDebug->m_bfme9F57;
}
