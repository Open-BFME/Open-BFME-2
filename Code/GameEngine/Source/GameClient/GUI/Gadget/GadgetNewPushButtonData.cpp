// cl: /O1 /DNDEBUG /MD

// ?getNewPushButtonData@@YAPAU_PushButtonData@@XZ,
// retail 0x0032843E, 22 bytes. Dedicated TU.
//
// Null-checked frameless new of the 0x38-byte push-button record. The
// zeroing ctor lives out of line (pinned at 0x00327E22; this body is its
// sole raw caller image-wide) and operator new resolves via its row. /O1
// is what cleans the pushed size with pop ecx; the Helpers TU's /O2 emits
// add esp,4 for the same source (SlavedUpdate friend_new precedent).
struct _PushButtonData
{
	_PushButtonData() throw();

private:
	char m_pad[0x38];
};

// ?getNewPushButtonData@@YAPAU_PushButtonData@@XZ
_PushButtonData *getNewPushButtonData(void)
{
	return new _PushButtonData;
}
