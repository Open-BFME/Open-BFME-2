// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift parseTextEntryData to clean C++.

#include <stdio.h>
#include <string.h>

typedef bool Bool;
typedef int Int;
typedef short Short;

class WinInstanceData;

struct EntryData
{
	void *text;
	void *secretTextDisplay;
	void *constructText;
	unsigned int flags;
	Short maxTextLen;
	Bool secretText;
};

static Int scanBool(const char *source, Bool &val)
{
	Int parsedValue = 0;
	Int ret = sscanf(source, "%d", &parsedValue);
	val = (Bool)parsedValue;
	return ret;
}

// ?scanShort@@YAHPBDAAF@Z
static Int scanShort(const char *source, Short &val)
{
	Int parsedValue = 0;
	Int ret = sscanf(source, "%d", &parsedValue);
	val = (Short)parsedValue;
	return ret;
}

// ?parseTextEntryData@@YA_NPADPAVWinInstanceData@@0PAX@Z rowed in
// GameWindowManagerScript_parseTextEntryData.cpp. This TU keeps a static
// (internal-linkage) copy so the scanShort/scanBool calls above still emit
// exactly as verified; the anchor forces its emission. It contributes no
// global symbol, so the link picks the row owner's copy.
static bool __cdecl parseTextEntryData(char *, WinInstanceData *, char *buffer, void *data)
{
	EntryData *entryData = (EntryData *)data;
	char *token;
	char *seps = " :,\n\r\t";

	token = strtok(buffer, seps);
	token = strtok(0, seps);
	scanShort(token, entryData->maxTextLen);

	token = strtok(0, seps);
	token = strtok(0, seps);
	scanBool(token, entryData->secretText);

	entryData->flags = 0;
	token = strtok(0, seps);
	token = strtok(0, seps);
	Bool numericalOnly;
	scanBool(token, numericalOnly);
	if (numericalOnly)
		entryData->flags |= 0x20;

	token = strtok(0, seps);
	token = strtok(0, seps);
	Bool alphaNumericalOnly;
	scanBool(token, alphaNumericalOnly);
	if (alphaNumericalOnly)
		entryData->flags |= 0x40;

	token = strtok(0, seps);
	token = strtok(0, seps);
	Bool asciiOnly;
	scanBool(token, asciiOnly);
	if (asciiOnly)
		entryData->flags |= 0x10;

	return true;
}

static const void *s_parseTextEntryDataAnchor = (const void *)parseTextEntryData;
