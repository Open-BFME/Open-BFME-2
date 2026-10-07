// cl: /O1 /DNDEBUG /EHsc /MD
// ?rva0022244D@Rva0022244D@@QAEXXZ @0x0022244D 36B
// Target evidence: byte flag at this+0x328 gates vtable slot +0x28; on the
// set path it clears the flag then calls rowed 0x00411523, the matched
// 0x006CC880 body through its retail thunk, and rowed 0x0041154F. The owner's
// identity and the slot's semantic name remain unresolved.

// The target retains its incoming ECX across the preceding virtual call. This
// address-derived call view emits a direct cdecl call without restoring ECX;
// the matched callee does not read ECX.
void Rva00411523CallAsFree();

void rva006cc880();
void Rva0041154FHide();

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
	Rva00411523CallAsFree();
	rva006cc880();
	Rva0041154FHide();
}
