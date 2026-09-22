// cl: /O1 /DNDEBUG /MD /EHsc
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
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	val = (Bool)temp;
	return ret;
}

static Int scanShort(const char *source, Short &val)
{
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	val = (Short)temp;
	return ret;
}

// ?parseTextEntryData@@YA_NPADPAVWinInstanceData@@0PAX@Z
bool __cdecl parseTextEntryData(char *, WinInstanceData *, char *buffer, void *data)
{
	EntryData *entryData = (EntryData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	c = strtok(buffer, seps);
	c = strtok(0, seps);
	scanShort(c, entryData->maxTextLen);

	c = strtok(0, seps);
	c = strtok(0, seps);
	scanBool(c, entryData->secretText);

	entryData->flags = 0;
	c = strtok(0, seps);
	c = strtok(0, seps);
	Bool numericalOnly;
	scanBool(c, numericalOnly);
	if (numericalOnly)
		entryData->flags |= 0x20;

	c = strtok(0, seps);
	c = strtok(0, seps);
	Bool alphaNumericalOnly;
	scanBool(c, alphaNumericalOnly);
	if (alphaNumericalOnly)
		entryData->flags |= 0x40;

	c = strtok(0, seps);
	c = strtok(0, seps);
	Bool asciiOnly;
	scanBool(c, asciiOnly);
	if (asciiOnly)
		entryData->flags |= 0x10;

	return true;
}
