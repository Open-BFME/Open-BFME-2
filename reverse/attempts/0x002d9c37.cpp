// ?isPositionalAudio@AudioEventRTS@@QBE_NXZ
// partial score=0.95 date=2026-10-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct AudioEventInfo
{
	char m_pad00[0x48];
	UnsignedInt m_type;      // +0x48, ST_WORLD is bit 1
	char m_pad4C[0xB0 - 0x4C];
	int m_soundType;         // +0xB0
};

class AudioEventRTS
{
public:
	Bool isPositionalAudio() const;
	UnsignedInt getSoundClass() const;
private:
	char m_pad00[8];
	const AudioEventInfo *m_eventInfo; // +0x08
	char m_pad0C[0x34 - 0x0C];
	int m_ownerID;                     // +0x34
	int m_ownerType;                   // +0x38
};

Bool AudioEventRTS::isPositionalAudio() const
{
	if( m_eventInfo )
	{
		switch( m_eventInfo->m_soundType )
		{
			case 2:
				if( !(m_eventInfo->m_type & 2) )
					return false;
				break;
			case 3:
				break;
			case 4:
				return false;
		}
	}
	switch( m_ownerType )
	{
		case 0:
			return true;
		case 1:
			if( m_ownerID != 0 )
				return true;
			break;
		case 2:
			if( m_ownerID != 0 )
				return true;
			break;
		case 3:
			if( m_ownerID != 0 )
				return true;
			break;
		case 4:
			if( m_ownerID != 0 )
				return true;
			break;
		case 5:
			if( m_ownerID != 0 )
				return true;
			break;
	}
	return false;
}
UnsignedInt AudioEventRTS::getSoundClass() const
{
	if( !m_eventInfo )
		return 0;
	switch( m_eventInfo->m_soundType )
	{
			case 0: return 1;
			case 2: return isPositionalAudio() ? 4 : 2;
			case 3: return 16;
			case 1: return 8;
			case 4: return 2;
			case 5: return 0;
			default: return 0;
	}
}
