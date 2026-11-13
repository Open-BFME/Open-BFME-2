// cl: /GS

// EA FESL client SDK ("jabba") blob-service result record populated constructor.
// The fixed keys and the adjacent default constructor identify the record as the
// 0x228-byte blob result returned by the FESL message object.

#include <stdio.h>

typedef __int64 FeslInt64;

#include "../../Include/GameNetwork/BfmeThingRF.h"

#include "../../Include/GameNetwork/BfmeThingUPB.h"

class Rva007E8810Message
{
public:
	bool hasError();
	void addInt(const char *key, int value);
	int getInt(const char *key, int defaultValue);
	void addBool(const char *key, bool value);
	bool getBool(const char *key, bool defaultValue);
	void addString(const char *key, const char *value);
	bool getString(const char *key, char *out, int size);
	void reset();
	void setError(int error);
	int getError();
	__int64 getInt64( const char *key, __int64 defaultValue );
	void addInt64(const char *key, __int64 value);
	char m_pad00[0x10];
private:
	char *m_record; // +0x10
	int m_capacity; // +0x14
	int m_position; // +0x18
public:
	unsigned int m_category; // +0x1C
	char m_pad20[0x4];
private:
	int m_error; // +0x24
	char m_pad28[0x4];
	int m_state; // +0x2C
};

#include "../../Include/Common/Rva007FF700Date.h"

class Rva007F0CB0BlobRecord
{
public:
	Rva007F0CB0BlobRecord( Rva007E8810Message *message );

private:
	Rva007E8810Message *m_message;
	char m_pad004[ 0x04 ];
	FeslInt64 m_blobId;
	FeslInt64 m_ownerId;
	int m_ownerType;
	char m_pad01C[ 0x04 ];
	int m_type;
	int m_formatType;
	FeslInt64 m_iconId;
	Rva007FF700Date m_creator;
	Rva007FF700Date m_update;
	char m_creatorName[ 0x20 ];
	char m_name[ 0x20 ];
	int m_downloadCount;
	float m_rating;
	int m_reviewCount;
	char m_version[ 0x20 ];
	char m_shortDescription[ 0x50 ];
	char m_longDescription[ 0xFF ];
	char m_locale[ 0x20 ];
	int m_224;
};

Rva007F0CB0BlobRecord::Rva007F0CB0BlobRecord( Rva007E8810Message *message )
	: m_ownerId( 0 ), m_ownerType( 0 )
{
	char text[ 0x4C ];

	m_blobId = ( m_message = message )->getInt64( "blobId", -1 );
	m_ownerId = m_message->getInt64( "ownerId", -1 );
	m_ownerType = (int)((BfmeThingRF *)m_message)->bfmeGoRF( (void *)"ownerType", (void *)-1 );
	m_type = (int)((BfmeThingRF *)m_message)->bfmeGoRF( (void *)"type", (void *)-1 );
	m_formatType = (int)((BfmeThingRF *)m_message)->bfmeGoRF( (void *)"formatType", (void *)-1 );
	m_iconId = m_message->getInt64( "iconId", -1 );

	text[ 0 ] = 0;
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"createDate", text, (void *)0x20 );
	m_creator.parse( text );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"updateDate", text, (void *)0x20 );
	m_update.parse( text );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"creator", m_creatorName, (void *)0x20 );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"name", m_name, (void *)0x20 );
	m_downloadCount = (int)((BfmeThingRF *)m_message)->bfmeGoRF( (void *)"downloadCount", (void *)-1 );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"rating", text + 0x0C, (void *)0x40 );
	sscanf( text + 0x0C, "%f", &m_rating );
	m_reviewCount = (int)((BfmeThingRF *)m_message)->bfmeGoRF( (void *)"reviewCount", (void *)-1 );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"version", m_version, (void *)0x20 );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"shortDescription", m_shortDescription, (void *)0x50 );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"longDescription", m_longDescription, (void *)0xFF );
	((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)"locale", m_locale, (void *)0x20 );
	m_224 = 0;
}
