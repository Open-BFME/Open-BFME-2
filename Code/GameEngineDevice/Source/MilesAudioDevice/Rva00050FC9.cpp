// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oi-
// ?rva00050FC9@Rva00050FC9@@QAEXXZ, retail 0x00050FC9, 26 bytes. Miles audio start switch.
// If byte at +2 is nonzero starts 3D sample with handle at +4 else starts sample with handle at +8.
// Evidence: direct IAT calls to mss32 AIL_start_3D_sample@4 and AIL_start_sample@4; honest Rva name.
extern "C" __declspec(dllimport) void __stdcall AIL_start_3D_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_start_sample(void *sample);

class Rva00050FC9
{
public:
	void rva00050FC9();
	char m_lead[2];
	unsigned char m_cond;
	char m_pad3;
	void *m_handle3D;
	void *m_handle;
};

void Rva00050FC9::rva00050FC9()
{
	if (m_cond)
		AIL_start_3D_sample(m_handle3D);
	else
		AIL_start_sample(m_handle);
}
