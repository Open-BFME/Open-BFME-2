// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva000B6E28@Rva000B4B23@@QAE?AVAsciiString@@ABVModelConditionFlags@@@Z,
// retail 0x000B6E28 (50 bytes, ret 8): the name of the condition-state entry
// matching the flags (rowed lookup 0x000B4B23, rowed name accessor
// 0x000B4A9F), or the empty string when no entry matches. Owner and entry
// names are address-derived.
#include "ascii_string.h"

class ModelConditionFlags;

#include "../../Include/Common/Rva000B4A9F.h"

class Rva000B4B23
{
public:
	void *rva000B4B23(const ModelConditionFlags &query);
	AsciiString rva000B6E28(const ModelConditionFlags &query);
};

AsciiString Rva000B4B23::rva000B6E28(const ModelConditionFlags &query)
{
	Rva000B4A9F *entry = (Rva000B4A9F *)rva000B4B23(query);
	if (entry)
		return *(const AsciiString *)entry->rva000B4A9F();
	return AsciiString::TheEmptyString;
}