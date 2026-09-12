// cl: /O1 /MD

// Evidence: retail 0x001EE5BE (24 bytes) is the REL32 call target named
// ?_bfme_setEngineVisibility@Mouse@@QAEX_N@Z at several already-matched call
// sites (e.g. Code/GameEngine/Source/Common/GameEngineClientSubsystems.cpp).
// The already byte-matched BFME1 conversion of the same method
// (reference/open-bfme-1/Code/GameEngine/Source/Common/
// promoted__bfme_setEngineVisibility_Mouse_QAEX_N_Z_005A4B50.cpp) documents:
//   void Mouse::_bfme_setEngineVisibility(bool visible)
//   {
//       if (m_cursorDirty) { m_cursor = m_pendingCursor; m_cursorState = m_pendingCursorState; m_cursorDirty = 0; }
//       applyCursor(visible, &m_cursor);
//   }
// BFME2 moved the five cursor-state bytes from Mouse+0x4DA1.. to +0x4F9D..
// and factored the commit-if-dirty block into its own private helper
// (retail 0x1EDDFF, verified against this exact byte layout), called
// unconditionally before applyCursor -- which itself moved from vtable
// slot 0x5C to 0x70 (five more virtuals ahead of it in BFME2's Mouse).

class Mouse
{
public:
	virtual void _M_slot_00(); virtual void _M_slot_04(); virtual void _M_slot_08();
	virtual void _M_slot_0c(); virtual void _M_slot_10(); virtual void _M_slot_14();
	virtual void _M_slot_18(); virtual void _M_slot_1c(); virtual void _M_slot_20();
	virtual void _M_slot_24(); virtual void _M_slot_28(); virtual void _M_slot_2c();
	virtual void _M_slot_30(); virtual void _M_slot_34(); virtual void _M_slot_38();
	virtual void _M_slot_3c(); virtual void _M_slot_40(); virtual void _M_slot_44();
	virtual void _M_slot_48(); virtual void _M_slot_4c(); virtual void _M_slot_50();
	virtual void _M_slot_54(); virtual void _M_slot_58(); virtual void _M_slot_5c();
	virtual void _M_slot_60(); virtual void _M_slot_64(); virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void applyCursor( bool visible, const unsigned char *cursor );

	void _bfme_setEngineVisibility( bool visible );

private:
	// Retail's commit-if-dirty helper, factored out of this method (see
	// evidence above); it directly touches the five bytes below.
	void commitPendingCursor( void );

	unsigned char m_unreconstructed_04[0x4F9D - 4];
	unsigned char m_cursor;               // +0x4F9D
	unsigned char m_cursorState;          // +0x4F9E
	unsigned char m_pendingCursor;        // +0x4F9F
	unsigned char m_pendingCursorState;   // +0x4FA0
	unsigned char m_cursorDirty;          // +0x4FA1
};

__declspec(noinline) void Mouse::commitPendingCursor( void )
{
	if ( m_cursorDirty )
	{
		m_cursor = m_pendingCursor;
		m_cursorState = m_pendingCursorState;
		m_cursorDirty = 0;
	}
}

void Mouse::_bfme_setEngineVisibility( bool visible )
{
	commitPendingCursor();
	applyCursor( visible, &m_cursor );
}
