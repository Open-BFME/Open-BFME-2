// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/GameEngine/Include

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
#include "ascii_string.h"
#include "unicode_string.h"
#include "GameNetwork/BfmeNetAddress.h"
#include "GameNetwork/LANPlayerClass.h"

LANPlayer::LANPlayer(const LANPlayer &other)
	: m_name(other.m_name),
	  m_login(other.m_login),
	  m_host(other.m_host),
	  m_lastHeard(other.m_lastHeard),
	  m_next(other.m_next),
	  m_address(other.m_address)
{
}
