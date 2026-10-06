// cl: /DNDEBUG /MD /EHsc /Ob2
//
// ??1ModuleTagString@@QAE@XZ, retail 0x006CE7F0, 97 bytes. Dedicated TU: the
// ModuleInfoNuggetDestructor unit declares this dtor for its member call, so
// the real body lives here. Conditionally releases member +0x08 through the
// cdecl helper at 0x006CE3D0, then destroys the two-element array at +0x0C
// through ehvec_dtor (0x00629110, pinned) with the thunked element dtor at
// 0x004A9DF3. Both callees resolve via pins; no other TU is disturbed.

struct Rva004A9DF3Element
{
	~Rva004A9DF3Element();
	int m_value;
};

void Rva006CE3D0Cleanup(void *ptr, int first, int second);

class ModuleTagString
{
public:
	~ModuleTagString();

private:
	unsigned char m_pad[8];
	void *m_ptr;
	Rva004A9DF3Element m_elems[2];
};

// ??1ModuleTagString@@QAE@XZ
ModuleTagString::~ModuleTagString()
{
	if (m_ptr != (void *)m_elems)
		Rva006CE3D0Cleanup(m_ptr, 0, 0);
}
