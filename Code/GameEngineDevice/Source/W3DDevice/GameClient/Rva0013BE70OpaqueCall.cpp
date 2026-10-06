// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?opaqueCall@Rva0013BE70Host@@QAEXPBD@Z, retail 0x0013BE70, 54 bytes.
// Copies the render-object name into the +0x9C inline buffer via sprintf
// using the input as its own format, after null and len<0x20 guards.
// Evidence: sole matched caller Create_Render_Obj 0x136175 passes its
// PBD name here; IAT sprintf; strlen-style len check; buffer at +0x9C.

class Rva0013BE70Host
{
public:
	void opaqueCall(const char *name);
private:
	unsigned char m_pad[0x9C];
	char m_name[0x20];
};

extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" int __declspec(dllimport) __cdecl sprintf(char *dst, const char *fmt, ...);

void Rva0013BE70Host::opaqueCall(const char *name)
{
	if (!name)
		return;
	if (strlen(name) >= 0x20)
		return;
	sprintf(m_name, name);
}
