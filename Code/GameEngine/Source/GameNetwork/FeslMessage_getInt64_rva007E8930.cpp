// flags: region default (reverse/retail_inventory/flag_regions.csv)
// 0x007E8930: Rva007E8810Message::getInt64. Five matched callers already
// name this member. Lookup goes through Rva007EBCA0; missing keys return
// the __int64 default; a hit is sscanf("%I64d").

#include <stdio.h>

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

char *Rva007EBCA0(const char *record, const char *key);

#include "../../Include/GameNetwork/Rva007E8810Message.h"

FeslInt64 Rva007E8810Message::getInt64(const char *key, FeslInt64 defaultValue)
{
	char *s = Rva007EBCA0(m_10, key);
	if (s == 0)
		return defaultValue;
	FeslInt64 v;
	sscanf(s, "%I64d", &v);
	return v;
}
