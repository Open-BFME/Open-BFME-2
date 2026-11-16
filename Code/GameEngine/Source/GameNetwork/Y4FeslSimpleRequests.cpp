// EA FESL client SDK ("jabba") -- the payload-free transaction request
// builders.
//
// Same SDK cluster and same message object as Y4FeslBuddyRequests.cpp.  Each
// row is nothing but `reset(); category = <FourCC>; depth = 3;`, so the ONLY
// thing that distinguishes one from another is the un-relocated imm32 written
// to +0x1C.  Those five FourCCs -- 'DISC', 'EPGT', 'RLST', 'RGAM', 'PING' --
// are hard evidence and are the whole content of these bodies.
//
// 0x007FBA70 is the one exception: it also stores its two remaining arguments
// into the message at +0x10 and +0x14, the buffer/size pair the V2 lane
// recovered for this object, so it is modelled with those two members named.

typedef __int64 FeslInt64;

#include "../../Include/GameNetwork/Rva007E8AC0.h"

#include "../../Include/GameNetwork/Rva007E8810Message.h"

#define FESL_RESET(message) ((Rva007E8AC0 *)(message))->run()

void __stdcall Rva007FAF90( Rva007E8810Message *msg )
{
	FESL_RESET(msg);
	msg->m_1C = 'DISC';
	msg->m_2C = 3;
}

void __stdcall Rva007FBA50( Rva007E8810Message *msg )
{
	FESL_RESET(msg);
	msg->m_1C = 'EPGT';
	msg->m_2C = 3;
}

void __stdcall Rva007FBA70( Rva007E8810Message *msg, void *buffer, int bufferSize )
{
	FESL_RESET(msg);
	msg->m_1C = 'PING';
	msg->m_2C = 3;
	msg->m_10 = static_cast<char *>(buffer);
	msg->m_14 = bufferSize;
}

void __stdcall Rva007FC270( Rva007E8810Message *msg )
{
	FESL_RESET(msg);
	msg->m_1C = 'RLST';
	msg->m_2C = 3;
}

void __stdcall Rva007FCC80( Rva007E8810Message *msg )
{
	FESL_RESET(msg);
	msg->m_1C = 'RGAM';
	msg->m_2C = 3;
}

void __stdcall Rva007FCCA0( Rva007E8810Message *msg )
{
	FESL_RESET(msg);
	msg->m_1C = 'PING';
	msg->m_2C = 3;
}
