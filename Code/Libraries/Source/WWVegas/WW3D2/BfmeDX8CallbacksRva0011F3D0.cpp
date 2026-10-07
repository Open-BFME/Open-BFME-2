// cl: /DNDEBUG /MD /O2 /arch:SSE /G7
// ?Rva0011F3D0Convert@@YAXPBDPAX@Z at 0x0011F3D0 (128B). Address-derived name; retail loops over a narrow string into a 256-word buffer and calls packet-identified bfmeData00DEDBE4.
typedef void (__stdcall *BfmeWideTextHookD0)(void *context, const unsigned short *text);

extern void *bfmeData00DEDBE4;

void Rva0011F3D0Convert(const char *text, void *context)
{
	BfmeWideTextHookD0 hook = (BfmeWideTextHookD0)bfmeData00DEDBE4;
	if (hook)
	{
		unsigned short buffer[256];
		for (unsigned i = 0; i < 256; ++i)
		{
			buffer[i] = (short)text[i];
			if (buffer[i] == 0)
				break;
		}
		hook(context, buffer);
	}
}
