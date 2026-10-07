// ?rva0051E9D2@Rva0051E9D2@@UAEMH@Z
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7
// ?rva0051E9D2@Rva0051E9D2@@UAEMH@Z @0x0051E9D2, 168 bytes.
// Target evidence: virtual slot 1 at 0x00867270. The function bounds an index
// against 12-byte records and selects signed 16-bit coordinates. The adjacent
// rowed copy helper at 0x0051E939 establishes the record's 0x04/0x06/0x08 fields.
// The scale offsets are structural inferences from retail loads, not named fields.
struct Rva0051E437
{
	int m00;
	short m04;
	short m06;
	short m08;
};

struct Rva0051E9D2Array
{
	char pad[0x20];
	char *begin;
	char *end;
	char *beginPtr() const { return begin; }
	char *endPtr() const { return end; }
};

class GlobalData
{
	char pad116c[0x116c];
public:
	float scale116c;
private:
	char pad1170[4];
public:
	float scale1174;
private:
	char pad1178[0x1c];
public:
	float scale1194;
};
extern GlobalData *TheWritableGlobalData;

class Rva0051E9D2
{
public:
	virtual float rva0051E9D2(int index);

private:
	Rva0051E9D2Array *m_array;
	int m_selector;
};

float Rva0051E9D2::rva0051E9D2(int index)
{
	if (index >= 0)
	{
		Rva0051E9D2Array *array = m_array;
		char *&beginRef = array->begin;
		int count = (array->end - beginRef) / 12;
		if ((unsigned)index < (unsigned)count)
		{
			Rva0051E437 *record = (Rva0051E437 *)(beginRef + index * 12);
			int selector = m_selector;
			switch (selector)
			{
			case 0:
				return record->m06;
			case 1:
				return record->m08;
			case 3:
				return record->m04;
			case 4:
				return record->m04 * TheWritableGlobalData->scale1194
					+ record->m08 * TheWritableGlobalData->scale1174
					+ record->m06 * TheWritableGlobalData->scale116c;
			}
		}
	}
	return 0.0f;
}
