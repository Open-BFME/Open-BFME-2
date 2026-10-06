// cl: /DNDEBUG /MD /EHsc
//
// ?rva002728C5@Drawable@@QAEXMM@Z, retail 0x002728C5, 71 bytes.
// Drawable float forwarder plus average-half store: if the +0x14C list head
// is present forward (a,b) to its slot 0x54 target, then store (a+b)*0.5
// (half at 0x00BC26F0) to +0xAC. Evidence: unlock lane; same +0x14C head
// pattern as Drawable_rva00272835; slot 0x54 callee pops 8B (no add esp);
// callers at 0x00485773; neighbours Drawable share flags.
extern const float g_00BC26F0;

class Rva002728C5Elem
{
public:
	virtual void s00() = 0; virtual void s01() = 0;
	virtual void s02() = 0; virtual void s03() = 0;
	virtual void s04() = 0; virtual void s05() = 0;
	virtual void s06() = 0; virtual void s07() = 0;
	virtual void s08() = 0; virtual void s09() = 0;
	virtual void s10() = 0; virtual void s11() = 0;
	virtual void s12() = 0; virtual void s13() = 0;
	virtual void s14() = 0; virtual void s15() = 0;
	virtual void s16() = 0; virtual void s17() = 0;
	virtual void s18() = 0; virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void slot54(float a, float b) = 0;
};

class Drawable
{
public:
	void rva002728C5(float a, float b);
private:
	char m_padAC[0xAC];
	float m_unkAC;
	char m_pad14C[0x14C - 0xAC - 4];
	Rva002728C5Elem **m_list;
};

void Drawable::rva002728C5(float a, float b)
{
	Rva002728C5Elem **head = m_list;
	if (*head != 0)
		(*head)->slot54(a, b);
	m_unkAC = (a + b) * g_00BC26F0;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00BC26F0@@3MB=?g_Va007C26F0@@3MA")
