// cl: /G7 /DNDEBUG /MD

// Two small hooks just below BFME_DX8_Thread_Lock, each driving a function
// pointer the engine can install:
//   0x0011F340  widens a narrow string into a 256-character buffer and hands
//               it, with the caller's argument, to the __stdcall hook at
//               0x00DEDBDC
//   0x0011F3C0  calls the argument-less hook at 0x00DEDBE0 when one is set
// Zero Hour has neither, so every name here is address-derived.

typedef void (__stdcall *BfmeWideTextHook)(void *context, const unsigned short *text);
typedef void (*BfmeVoidHook)(void);

extern BfmeWideTextHook bfmeData00DEDBDC;		// 0x00DEDBDC
extern BfmeVoidHook bfmeData00DEDBE0;			// 0x00DEDBE0

// Each character is sign-extended into the buffer before the terminator test,
// so the terminator is copied too.
// The index is zeroed before the hook test, as retail's xor comes first.
void bfmeRva0011F340(const char *text, void *context)
{
	unsigned i = 0;
	BfmeWideTextHook hook = bfmeData00DEDBDC;
	if (hook) {
		unsigned short buffer[256];
		for ( ; i < 256; ++i) {
			buffer[i] = (short)text[i];
			if (buffer[i] == 0)
				break;
		}
		hook(context, buffer);
	}
}

// ?bfmeRva0011F3C0@@YAXXZ present-unmatched
void bfmeRva0011F3C0(void)
{
	BfmeVoidHook hook = bfmeData00DEDBE0;
	if (hook != 0)
		hook();
}
