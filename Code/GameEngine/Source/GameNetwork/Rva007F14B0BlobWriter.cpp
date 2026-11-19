// cl: /GS
//
// Retail 0x007F14B0 writes the metadata and removal attributes of a FESL blob.
// The address-derived class preserves its unresolved original owner.

#include <stdio.h>

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

class Rva007E8810Message
{
public:
	void reset();
	void addString(const char *key, const char *value);
	void addInt(const char *key, int value);
	void addInt64(const char *key, FeslInt64 value);
	char m_pad00[0x1c];
	unsigned int m_category;
};

struct BlobAttribute
{
	const char *type;
	const char *name;
};

struct Rva007F14B0Record
{
	int formatType;
	int unused04;
	FeslInt64 iconId;
	const char *creator;
	const char *name;
	const char *version;
	const char *shortDescription;
	const char *longDescription;
	const char *locale;
	BlobAttribute *attributes;
	int downloadCount;
};

class Rva007F14B0BlobWriter
{
public:
	static void __stdcall write(Rva007E8810Message *message,
		FeslInt64 ownerId,
		bool includeDownloadCount,
		const char *const *removeAttributes,
		int removeCount,
		const Rva007F14B0Record *record);
};

// The blob/UpdateBlobInfo TXN value is this record's m_name at VA 0x00E0A010.
struct Rva007B55E0TxnName
{
	__declspec(noinline) Rva007B55E0TxnName( const char *type, const char *name );

	const char *m_type;
	const char *m_name;
	int m_reserved;
};

extern Rva007B55E0TxnName TheBlobUpdateInfoTransaction;

// ?write@Rva007F14B0BlobWriter@@SGXPAVRva007E8810Message@@_J_NPBQBDHPBURva007F14B0Record@@@Z
void __stdcall Rva007F14B0BlobWriter::write(Rva007E8810Message *message,
	FeslInt64 ownerId,
	bool includeDownloadCount,
	const char *const *removeAttributes,
	int removeCount,
	const Rva007F14B0Record *record)
{
	const char *txn = TheBlobUpdateInfoTransaction.m_name;
	message->reset();
	message->m_category = 'blob';
	message->addString("TXN", txn);
	message->addInt64("blobId", ownerId);
	if (record->formatType > -1)
		message->addInt("formatType", record->formatType);
	if (record->iconId > -1)
		message->addInt64("iconId", record->iconId);
	if (record->creator)
		message->addString("creator", record->creator);
	if (record->name)
		message->addString("name", record->name);
	if (record->version)
		message->addString("version", record->version);
	if (record->shortDescription)
		message->addString("shortDescription", record->shortDescription);
	if (record->longDescription)
		message->addString("longDescription", record->longDescription);
	if (record->locale)
		message->addString("locale", record->locale);
	if (includeDownloadCount)
		message->addInt("downloadCount", 0);

	message->addInt("attributes.[]", record->downloadCount);
	unsigned int index;
	for (index = 0; index < (unsigned int)record->downloadCount; ++index)
	{
		char key[64] = { 0 };
		sprintf(key, "attributes.%d.name", index);
		message->addString(key, record->attributes[index].type);
		sprintf(key, "attributes.%d.type", index);
		message->addInt(key, 0);
		sprintf(key, "attributes.%d.value", index);
		message->addString(key, record->attributes[index].name);
	}

	message->addInt("removeAttributes.[]", removeCount);
	for (index = 0; index < (unsigned int)removeCount; ++index)
	{
		char key[64] = { 0 };
		sprintf(key, "removeAttributes.%d", index);
		message->addString(key, removeAttributes[index]);
	}
}
