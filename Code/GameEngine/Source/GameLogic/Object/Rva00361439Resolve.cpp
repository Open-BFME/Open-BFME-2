// cl: /DNDEBUG /MD
//
// ?Rva00361439Resolve@@YAXXZ retail 0x00361439 55 bytes.
// Validity-table resolve-all: count is (g_validityEnd-g_validityBegin)/0x94
// via signed idiv; when positive each 0x94-byte element is passed to the
// just-landed ObjectFilter resolveNames at 0x003611EF. Evidence: calls the
// rowed resolveNames; steps 0x94 per element; same globals and size and flags
// as siblings ObjectFilterRelease.cpp and ObjectFilter_isValid.cpp. Caller at
// 0x002CF675. All callees rowed.
struct ValidityTableRecord
{
	char m_pad[0x94];
};

extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;

class ObjectFilter
{
public:
	static void rva003611EFResolveNames(ObjectFilter *filter);
};

void Rva00361439Resolve()
{
	if ((g_validityEnd - g_validityBegin) / (int)sizeof(ValidityTableRecord) <= 0)
		return;
	int offset = 0;
	int count = (g_validityEnd - g_validityBegin) / (int)sizeof(ValidityTableRecord);
	do
	{
		ObjectFilter *filter = (ObjectFilter *)(g_validityBegin + offset);
		ObjectFilter::rva003611EFResolveNames(filter);
		offset += 0x94;
	} while (--count != 0);
}
