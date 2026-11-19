// cl: /GS
// EA FESL client SDK ("jabba") -- feedback transaction request builder.
//
// Ported from reference/open-bfme-1/Code/GameEngine/Source/Common/../GameNetwork/V2FeslFeedbackRequest.cpp
// (BFME1 0x007F1F60, 174B). The BFME2 bodies are byte-identical to the donor
// modulo relocations: all six attribute-name literals agree verbatim
// ("TXN", "targetType", "originatorUserId", "message", "feedbackType",
// "extraFeedbackDetail", plus the "targetIds.%d"/"targetIds.[]"
// and "chatLog.%d.userId"/"chatLog.%d.chat"/"chatLog.[]" helpers), the
// 'fdbk' category word sits at msg+0x1C, and the TXN value still arrives via
// the global char* at retail 0x00E0A058 (kept ebx-resident across the calls).
//
// Retail layout, all measured:
//   0x0065EA80  buildRequest  174B, ret 0x2C
//   0x0065EB30  addTargetIds  107B, ret 0xC (sprintf loop over 8-byte records)
//   0x0065EBA0  addChatLog    148B, ret 0xC (0x208-byte stride, int64+string)
// Callees resolve through the established message pins (reset@0x655B50,
// addString@0x65AA0, addInt@0x65960, addInt64@0x65F00 row) and the CRT
// _sprintf import pin@0x6291B4; the /GS cookie shape matches the sibling
// Fesl builders.

#include <stdio.h>

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

// Transaction tag for this request; retail keeps it in a global pointer
// (mov ebx,[0x00E0A058] at 0x0065EA85) and passes it as the TXN value.
extern const char *g_feslFeedbackTxnName;
// g_feslFeedbackTxnName: matched references place it at VA 0xe0a058 (zero-filled .bss).
const char * g_feslFeedbackTxnName;

#include "../../Include/GameNetwork/Rva007E8810Message.h"

struct Rva007F2010TargetId
{
	int id;
	int unused;
};

struct Rva007F2080ChatLog
{
	FeslInt64 userId;
	char chat[ 0x200 ];
};

class Rva007F1F60Feedback
{
public:
	void addTargetIds( Rva007E8810Message *msg,
		const Rva007F2010TargetId *targetIds, int count );
	void addChatLog( Rva007E8810Message *msg,
		const Rva007F2080ChatLog *chatLog, int count );
	void buildRequest( Rva007E8810Message *msg, int targetType,
		const Rva007F2010TargetId *targetIds, int targetIdCount,
		FeslInt64 originatorUserId, const char *message, int feedbackType,
		const Rva007F2080ChatLog *chatLog, int chatLogCount,
		const char *extraFeedbackDetail );
};

void Rva007F1F60Feedback::addTargetIds( Rva007E8810Message *msg,
	const Rva007F2010TargetId *targetIds, int count )
{
	char key[ 32 ];
	Rva007E8810Message *message = msg;
	const Rva007F2010TargetId *ids = targetIds;
	int limit = count;
	for ( int i = 0; i < limit; ++i )
	{
		sprintf( key, "targetIds.%d", i );
		message->addInt( key, ids[ i ].id );
	}
	message->addInt( "targetIds.[]", count );
}

void Rva007F1F60Feedback::addChatLog( Rva007E8810Message *msg,
	const Rva007F2080ChatLog *chatLog, int count )
{
	char key[ 32 ];
	Rva007E8810Message *message = msg;
	const Rva007F2080ChatLog *logs = chatLog;
	int limit = count;
	for ( int i = 0; i < limit; ++i )
	{
		sprintf( key, "chatLog.%d.userId", i );
		message->addInt64( key, logs[ i ].userId );
		sprintf( key, "chatLog.%d.chat", i );
		message->addString( key, logs[ i ].chat );
	}
	message->addInt( "chatLog.[]", count );
}

void Rva007F1F60Feedback::buildRequest( Rva007E8810Message *msg, int targetType,
	const Rva007F2010TargetId *targetIds, int targetIdCount,
	FeslInt64 originatorUserId, const char *message, int feedbackType,
	const Rva007F2080ChatLog *chatLog, int chatLogCount,
	const char *extraFeedbackDetail )
{
	const char *txn = g_feslFeedbackTxnName;
	msg->reset();
	msg->m_1C = 'fdbk';
	msg->addString( "TXN", txn );
	addTargetIds( msg, targetIds, targetIdCount );
	msg->addInt( "targetType", targetType );
	msg->addInt64( "originatorUserId", originatorUserId );
	msg->addString( "message", message );
	msg->addInt( "feedbackType", feedbackType );
	addChatLog( msg, chatLog, chatLogCount );
	msg->addString( "extraFeedbackDetail", extraFeedbackDetail );
}
