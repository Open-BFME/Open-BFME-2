// cl: /O1 /DNDEBUG /MD /EHsc /Oi-
// ?rva00050FE3@Rva00050FE3@@QAEXXZ, retail 0x00050FE3, 26 bytes. Miles audio stop switch.
// If byte at +2 nonzero stops 3D sample with handle at +4 else stops sample with handle at +8.
// Evidence: cmp [ecx+2] 0 je else; call [IAT] mss32 AIL_stop_3D_sample@4 vs AIL_stop_sample@4. Honest Rva name.
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *sample);

class Rva00050FE3
{
public:
	void rva00050FE3();
	char m_lead[2];
	unsigned char m_cond;
	char m_pad3;
	void *m_handle3D;
	void *m_handle;
};

void Rva00050FE3::rva00050FE3()
{
	if (m_cond)
		AIL_stop_3D_sample(m_handle3D);
	else
		AIL_stop_sample(m_handle);
}
