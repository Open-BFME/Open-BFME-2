// cl: /O1 /EHsc /arch:SSE2

// Rva003AEAA3 (58B) clone via new 0xAC plus rowed outer copy Rva003AEADD.
// Same EH new-plus-copy shape as the rowed Concrete clone at 0x3AE9DB;
// size 0xAC comes from the padded Rva class (outer TU uses 0xA0 since its
// copy never touches the tail). Both callees already resolve (new via pin
// ??2@YAPAXI@Z, copy via rowed Rva003AEADD).

class Rva003AEADD
{
public:
	Rva003AEADD(const Rva003AEADD &other);
	Rva003AEADD *clone() const;

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
	char m_pad20[128]; // +0x20..0x9F
	char m_tail[12]; // +0xA0..0xAB: makes sizeof 0xAC for new
};

// ?clone@Rva003AEADD@@QBEPAV1@XZ
Rva003AEADD *Rva003AEADD::clone() const
{
	return new Rva003AEADD(*this);
}
