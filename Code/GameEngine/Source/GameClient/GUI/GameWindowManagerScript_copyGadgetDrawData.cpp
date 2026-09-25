// cl: /O1 /DNDEBUG /MD

// Gadget draw-data copy, retail 0x003157BE (128B). BFME2-new code (no Zero
// Hour / BFME1 donor): copies the three 0x6C draw-data arrays
// (enabled/disabled/hilite, nine 0x0C WinDrawData entries each) at instance
// offsets +0x18/+0x84/+0xF0 from a source window's instance data, or from
// explicit template blocks when the source is null. Called ~10 times from
// createGadget (0x00316518) after wiring each gadget's sub-windows.
// The instance pointer is the rowed disp8 lea getter 0x00314046 (declared,
// never defined here); memcpy is a plain extern so the call stays an E8 to
// the import thunk like the getDataTemplate TU.

class GameWindow;

class Rva00314046LeaField
{
public:
	void *get() const;
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

void copyGadgetDrawData_Rva003157BE(GameWindow *dst, GameWindow *src, void *enabled, void *disabled, void *hilite)
{
	if (!dst)
		return;
	char *instA = (char *)((Rva00314046LeaField *)dst)->get();
	char *instB;
	if (src)
		instB = (char *)((Rva00314046LeaField *)src)->get();
	else
		instB = 0;
	memcpy(instA + 0x18, instB ? instB + 0x18 : (char *)enabled, 0x6C);
	memcpy(instA + 0x84, instB ? instB + 0x84 : (char *)disabled, 0x6C);
	memcpy(instA + 0xF0, instB ? instB + 0xF0 : (char *)hilite, 0x6C);
}
