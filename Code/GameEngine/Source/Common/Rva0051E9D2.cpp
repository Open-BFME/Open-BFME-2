// ?value@Rva0051E73E@@UAEMH@Z
// cl: /O1 /arch:SSE /G7
// ?value@Rva0051E73E@@UAEMH@Z @0x0051E9D2, 168 bytes.
// Target evidence: virtual slot 1 of table RVA 0x00867270; the constructor
// and count owners at 0x0051E73E/0x0051E754 establish this concrete series.
// The function bounds an index
// against 12-byte records and selects signed 16-bit coordinates. The adjacent
// rowed copy helper at 0x0051E939 establishes the record's 0x04/0x06/0x08 fields.
// The scale offsets are structural inferences from retail loads, not named fields.
class Rva0051E437
{
public:
	Rva0051E437 &rva0051E437(const Rva0051E437 &src);
	int m00;
	short m04;
	short m06;
	short m08;
};

template <class T>
struct Rva0051E716Range
{
	int size() const { return m_end - m_begin; }
	T *m_begin;
	T *m_end;
};

struct Rva0051E9D2Array
{
	char pad[0x20];
	Rva0051E716Range<Rva0051E437> m_range;
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

// Consuming two-slot interface; original class and inheritance names remain unknown.
class __declspec(novtable) TimelineSeries
{
public:
    virtual int count() = 0;
    virtual float value(int index) = 0;
};

// Existing constructor owners: native 12-byte series, table RVAs 867268/867270.
// The opaque row points at the player's native record ranges; it is not a new
// claim about the original source type or ownership of those fields in a base.
class Rva0051E716 : public TimelineSeries
{
public:
    Rva0051E716(int selector) { m_array = 0; m_selector = selector; }
    virtual int count();
    virtual float value(int index);
    void *m_array;
    int m_selector;
};
class Rva0051E73E : public Rva0051E716
{
public:
    Rva0051E73E(int selector) : Rva0051E716(selector) {}
    virtual int count();
    virtual float value(int index);
};

float Rva0051E73E::value(int index)
{
	if (index >= 0)
	{
		Rva0051E9D2Array *array = reinterpret_cast<Rva0051E9D2Array *>(m_array);
		Rva0051E437 *beginRef = array->m_range.m_begin;
		int count = array->m_range.m_end - array->m_range.m_begin;
		if ((unsigned)index < (unsigned)count)
		{
			Rva0051E437 *record = &array->m_range.m_begin[index];
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
