// ??0NetCommandList@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc
//
// NetCommandList constructor, retail 0x0058B06A, 19 bytes: installs vtable
// RVA 0x00870A08 (DIR32 auto-patch; slot 0 is the now-matched ??_G row, so no
// dtor definition is needed here), zeroes the three list words, returns this.
//
// Dedicated TU (callee-visibility: defining it in the init TU would inline it
// into the matched FrameData::init; defining it in the Deleter TU would see
// the defined dtor there instead of the row). Explicit vtable so this TU
// emits no vtable/??_G copy; the Deleter TU owns those.
extern "C" const void *const vtbl_00C70A08[];  // ??_7NetCommandList@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C70A08=??_7NetCommandList@@6B@")
class NetCommandList
{
public:
	NetCommandList();
private:
	const void *m_vtable; // +0, retail 0x00C70A08 (explicit so no vtable emitted)
	void *m_first;
	void *m_last;
	void *m_lastMessageInserted;
};
// ??0NetCommandList@@QAE@XZ
NetCommandList::NetCommandList()
	: m_vtable(vtbl_00C70A08)
{
	m_first = 0;
	m_last = 0;
	m_lastMessageInserted = 0;
}
