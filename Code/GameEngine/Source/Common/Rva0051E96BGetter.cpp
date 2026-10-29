// ?value@Rva0051E716@@UAEMH@Z @0x0051E96B, 103 bytes.
// Target evidence: slot 1 of table RVA 0x00867268 is this existing owner;
// table RVA 0x00867270 instead uses sibling 0x0051E9D2. The constructor/count
// pair at 0x0051E716/0x0051E72C establishes the concrete series relationship.
// Bounds an index against 20-byte records; switch on
// selector with cases 0,1,2,4 (3 missing, like sibling's missing 2).
// Record layout from retail loads: int +0x04, float +0x08, shorts +0x0C/+0x0E.
// Array pad 0x14 from begin/end offsets (sibling uses 0x20).
// cl: /O1 /arch:SSE /G7
struct Rva0051E96BRecord
{
	int m00;
	int m04;
	float m08;
	short m0C;
	short m0E;
	char mPad10[0x14 - 0x10];
};

template <class T>
struct Rva0051E716Range
{
	int size() const { return m_end - m_begin; }
	T *m_begin;
	T *m_end;
};

struct Rva0051E96BArray
{
	char pad[0x14];
	Rva0051E716Range<Rva0051E96BRecord> m_range;
};

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

float Rva0051E716::value(int index)
{
	if (index >= 0)
	{
		Rva0051E96BArray *array = reinterpret_cast<Rva0051E96BArray *>(m_array);
		Rva0051E96BRecord *beginRef = array->m_range.m_begin;
		int count = array->m_range.m_end - array->m_range.m_begin;
		if ((unsigned)index <= (unsigned)count)
		{
			Rva0051E96BRecord *record = &array->m_range.m_begin[index];
			int selector = m_selector;
			switch (selector)
			{
			case 0:
				return record->m0C;
			case 1:
				return record->m0E;
			case 2:
				return (float)record->m04;
			case 4:
				return record->m08;
			}
		}
	}
	return 0.0f;
}
