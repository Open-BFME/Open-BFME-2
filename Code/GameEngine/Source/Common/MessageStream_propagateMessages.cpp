// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// MessageStream::propagateMessages, retail 0x00310FF5 (101 bytes).
//
// Direct port of the Zero Hour MessageStream::propagateMessages worker with
// two Battle for Middle-earth II deltas proven by the retail body:
// - a destroyed message goes through the global delete (flag 0 on slot 0
//   plus a separate scalar deallocation of the deleting-destructor return,
//   not plain `delete`, which would pass 1);
// - the surviving list is handed to CommandList::appendMessageList in a
//   single call instead of looping appendMessage per message.
// Layout from the retail body: firstMessage at +0x0C, lastMessage at +0x10,
// firstTranslator at +0x14, so the list base carries 8 bytes ahead of the
// Zero Hour head; translator links at +0x00 with the translator at +0x0C,
// and the message link at +0x04.

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

#include "../../Include/Common/MessageStream.h"
#include "../../Include/Common/CommandList.h"

class GameMessageTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *message) = 0;
	virtual ~GameMessageTranslator(void) {}
};

void MessageStream::propagateMessages(void)
{
	TranslatorData *translator;
	GameMessage *message;
	GameMessage *next;

	for (translator = m_firstTranslator; translator; translator = translator->m_next)
	{
		for (message = m_firstMessage; message; message = next)
		{
			if (translator->m_translator)
			{
				GameMessageDisposition disposition =
					translator->m_translator->translateGameMessage(message);
				next = message->next();
				if (disposition == DESTROY_MESSAGE)
					::delete message;
			}
			else
			{
				next = message->next();
			}
		}
	}

	TheCommandList->appendMessageList(m_firstMessage);
	m_firstMessage = 0;
	m_lastMessage = 0;
}
