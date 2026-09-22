// cl: /O1 /DNDEBUG /MD /EHsc
// stlport
// Retail RE: ?addUnitPrereq@ProductionPrerequisite@@QAEXVAsciiString@@_N@Z @0x004F52CB (105B).
//
// BFME1 donor: Code/GameEngine/Source/Common/RTS/ProductionPrerequisiteAddUnitPrereq.cpp
// (info.m_name = unit via op= + info.m_flags = or?1:0 + info.m_unit = 0 +
// push_back(info)). BFME2 adaptations (all retail-measured): push_back is the
// 1-arg stlport shape (retail 0x004F5243, ret 4, fast copy via 0x002CF99D +
// insert_aux 0x004F5165), not the donor's 2-arg tag form, so the tag line is
// dropped. Member order follows retail stores (m_name init-zero, op=, m_unit,
// m_flags). PrereqUnitRec keeps its implicit dtor so the member teardown
// reaches the folded AsciiString dtor pin 0x00036410 directly, and AsciiString
// keeps the inline default ctor (store-0) with declared-only op=/dtor to the
// folded pins 0x000366F0/0x00036410. /O1 selects the outlined __EH_prolog head
// (mov eax,scope + call 0x629188), same axis as the parse-thunk twins.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ThingTemplate;

namespace _STL
{

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	void push_back(const T &x);
	unsigned int size() const { return m_finish - m_start; }
	const T &operator[](unsigned int i) const { return m_start[i]; }

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};

}

template <typename T>
struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);
};

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		const ThingTemplate *m_unit;
		int m_flags;
		AsciiString m_name;
	};

	ProductionPrerequisite();
	~ProductionPrerequisite();

	void addUnitPrereq(AsciiString unit, bool orUnitWithPrevious);
	void addUnitPrereq(const _STL::vector<AsciiString> &units);

public:
	_STL::vector<PrereqUnitRec> m_prereqUnits;
	_STL::vector<ScienceType> m_prereqSciences;
	_STL::vector<ScienceType> m_unused;
};

void ProductionPrerequisite::addUnitPrereq(AsciiString unit, bool orUnitWithPrevious)
{
	PrereqUnitRec info;
	info.m_name = unit;
	info.m_unit = 0;
	info.m_flags = orUnitWithPrevious ? 1 : 0;
	m_prereqUnits.push_back(info);
}

void ProductionPrerequisite::addUnitPrereq(const _STL::vector<AsciiString> &units)
{
	bool orWithPrevious = false;
	for (int i = 0; i < units.size(); ++i)
	{
		addUnitPrereq(units[i], orWithPrevious);
		orWithPrevious = true;
	}
}
