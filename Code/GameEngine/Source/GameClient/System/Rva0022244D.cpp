// cl: /O1 /DNDEBUG /EHsc /MD
// ?rva0022244D@Rva0022244D@@QAEXXZ @0x0022244D 36B
// Target evidence: byte flag at this+0x328 gates vtable slot +0x28; on the
// set path it clears the flag then calls rowed 0x00411523, the matched
// 0x006CC880 body through its retail thunk, and rowed 0x0041154F. The owner's
// identity and the slot's semantic name remain unresolved.

// The target retains its incoming ECX across the preceding virtual call: the
// rowed 0x00411523 walk is static and does not read ECX.
class Rva00411523
{
public:
	static void rva00411523();
};

// Retail calls the rowed 5-byte Apt tail jump 0x006CC940, which jumps to 0x006CC880.
void rva006cc940();
void Rva0041154FHide();
#if defined(BFME2_MODERN)
// W3DDisplay.cpp: whether this Apt draw follows a fixed update (consumes it).
bool modernAptFreshFrame();
#endif

class Rva0022244D
{
	char m_pad[0x324];
	unsigned char m_flag328;

public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void rva0022244DVslot10() = 0;

	void rva0022244D();
};

void Rva0022244D::rva0022244D()
{
	if (m_flag328)
	{
		rva0022244DVslot10();
		m_flag328 = 0;
	}
#if defined(BFME2_MODERN)
	// Extra presentations between fixed updates must not hide component
	// windows (progress overlays, 3D portraits) that only an update re-marks.
	if (!modernAptFreshFrame())
	{
		rva006cc940();
		return;
	}
#endif
	Rva00411523::rva00411523();
	rva006cc940();
	Rva0041154FHide();
}
