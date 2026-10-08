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
	int length();
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

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 NetCommandList.cpp
// supplies length's source expression and spelling. Complete target
// 58B0CA..58B0D7 follows removeMessage's RET4 and precedes findMessage.
// Existing rowed list operations independently establish head+4 and next+4;
// the function counts nodes without touching message payloads. The local
// link view represents only those accessed words, not a complete node type.
int NetCommandList::length()
{
	struct Link { void *command; Link *next; };
	int count = 0;
	Link *node = (Link *)m_first;
	while (node != 0) {
		++count;
		node = node->next;
	}
	return count;
}
