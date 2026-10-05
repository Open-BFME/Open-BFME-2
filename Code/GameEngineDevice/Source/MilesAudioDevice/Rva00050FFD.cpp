// cl: /O1 /DNDEBUG /MD /EHsc /Oi-
// ?rva00050FFD@Rva00050FFD@@QAEXXZ, retail 0x00050FFD, 26 bytes. Miles audio offset switch.
// If byte at +2 nonzero reads 3D sample offset with handle at +4 else sample position with handle at +8.
// Evidence: cmp [ecx+2] 0 je else; call [IAT] mss32 AIL_3D_sample_offset@4 vs AIL_sample_position@4. Chain of 0x50FE3.
extern "C" __declspec(dllimport) void __stdcall AIL_3D_sample_offset(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_sample_position(void *sample);

class Rva00050FFD
{
public:
	void rva00050FFD();
	char m_lead[2];
	unsigned char m_cond;
	char m_pad3;
	void *m_handle3D;
	void *m_handle;
};

void Rva00050FFD::rva00050FFD()
{
	if (m_cond)
		AIL_3D_sample_offset(m_handle3D);
	else
		AIL_sample_position(m_handle);
}
