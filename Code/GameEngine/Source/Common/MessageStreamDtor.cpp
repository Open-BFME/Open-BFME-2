// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1MessageStream@@UAE@XZ, retail 0x00310FA1 (84 bytes).
// MessageStream dtor shard (regular virtual, not novtable, so the compiler
// emits the vtable store plus EH prolog in retail order). ZH MessageStream.cpp
// donor proves the semantics: walk the translator list deleting each entry
// then tear down the GameMessageList base. TranslatorData dtor plus operator
// delete resolve via the rowed bodies; the GameMessageList base dtor resolves
// via its row 0x0030F57C. The class comes from the canonical MessageStream.h,
// so the table this unit emits is retail's 20-slot 0x00C09890 shape
// (SubsystemInterface's 14 slots, GameMessageList's four, MessageStream's two).

#include "../../Include/Common/MessageStream.h"

#include <new>

void deleteMessageStream(MessageStream *messageStream)
{
	delete messageStream;
}

// ??1MessageStream@@UAE@XZ @0x00310FA1
MessageStream::~MessageStream()
{
	TranslatorData *trans, *nextTrans;
	for (trans = m_firstTranslator; trans; trans = nextTrans)
	{
		nextTrans = trans->m_next;
		delete trans;
	}
}
