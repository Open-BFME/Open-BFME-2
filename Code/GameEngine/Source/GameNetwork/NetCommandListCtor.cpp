// ??0NetCommandList@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc
//
// NetCommandList constructor, retail 0x0058B06A, 19 bytes: installs vtable
// RVA 0x00870A08 (DIR32 auto-patch; slot 0 is the now-matched ??_G row, so no
// dtor definition is needed here), zeroes the three list words, returns this.
//
// Shares NetCommandListView.h with the list operations so tu_skeleton can
// merge it into NetCommandList.cpp; the vtable store is the class's own.
#include "NetCommandListView.h"

// ??0NetCommandList@@QAE@XZ
NetCommandList::NetCommandList()
{
	m_first = 0;
	m_last = 0;
	m_lastMessageInserted = 0;
}

// Clean BF1 9cbfb551fe20dae985f91f2319d8997287b6a705 NetCommandList.cpp
// supplies length's source expression and spelling. Complete target
// 58B0CA..58B0D7 follows removeMessage's RET4 and precedes findMessage.
// Existing rowed list operations independently establish head+4 and next+4;
// the function counts nodes without touching message payloads.
Int NetCommandList::length()
{
	Int count = 0;
	NetCommandRef *node = m_first;
	while (node != 0) {
		++count;
		node = node->getNext();
	}
	return count;
}
