// ?propagateMessages@MessageStream@@QAEXXZ
// partial score=0.99 date=2026-09-12
// cl: /O1 /MD

// Evidence: retail 0x00310FF5 (101 bytes) is the REL32 call target named
// ?propagateMessages@MessageStream@@QAEXXZ, referenced from
// Code/GameEngine/Source/Common/GameEngineClientSubsystems.cpp's call
// chain. ZH's MessageStream.cpp implements this verbatim:
//   void MessageStream::propagateMessages( void )
//   {
//       for( ss=m_firstTranslator; ss; ss=ss->m_next )
//           for( msg=m_firstMessage; msg; msg=next )
//           {
//               if (ss->m_translator)
//               {
//                   GameMessageDisposition disp = ss->m_translator->translateGameMessage(msg);
//                   next = msg->next();
//                   if (disp == DESTROY_MESSAGE) msg->deleteInstance();
//               }
//               else next = msg->next();
//           }
//       TheCommandList->appendMessageList( m_firstMessage );
//       m_firstMessage = NULL;
//       m_lastMessage = NULL;
//   }
// This build has no memory-pool objects (BFME_MODULE_NO_MPO), so
// deleteInstance() collapses to the same split teardown as the other
// candidates in this lane: a virtual dtor call forced to flag 0, then a
// separate call to the global scalar operator delete (0x2FD60). Member
// offsets (MessageStream+0xC/+0x10/+0x14, TranslatorData+0/+0xC,
// GameMessage+4) and TheCommandList's appendMessageList (non-virtual,
// pinned at 0x30F880) are read directly from the retail body.

class GameMessage
{
public:
	virtual ~GameMessage();
	GameMessage *next( void ) { return m_next; }
private:
	GameMessage *m_next; // +0x4
};

class GameMessageTranslator
{
public:
	virtual int translateGameMessage( const GameMessage *msg );
	virtual ~GameMessageTranslator();
};

struct TranslatorData
{
	TranslatorData *m_next;
	TranslatorData *m_prev;
	unsigned int m_id;
	GameMessageTranslator *m_translator;
	unsigned int m_priority;
};

class CommandList
{
public:
	void appendMessageList( GameMessage *list );
};

extern CommandList *TheCommandList; // VA 0xE00954

class MessageStream
{
public:
	void propagateMessages( void );

private:
	unsigned char m_unreconstructed_00[0xC];
	GameMessage *m_firstMessage;      // +0xC
	GameMessage *m_lastMessage;       // +0x10
	TranslatorData *m_firstTranslator; // +0x14
};

void MessageStream::propagateMessages( void )
{
	TranslatorData *ss;
	GameMessage *msg, *next;

	for ( ss = m_firstTranslator; ss; ss = ss->m_next )
	{
		for ( msg = m_firstMessage; msg; msg = next )
		{
			if ( ss->m_translator )
			{
				int disp = ss->m_translator->translateGameMessage( msg );
				next = msg->next();
				if ( disp == 1 )
				{
					msg->~GameMessage();
					::operator delete( msg );
				}
			}
			else
			{
				next = msg->next();
			}
		}
	}

	TheCommandList->appendMessageList( m_firstMessage );

	m_firstMessage = 0;
	m_lastMessage = 0;
}
