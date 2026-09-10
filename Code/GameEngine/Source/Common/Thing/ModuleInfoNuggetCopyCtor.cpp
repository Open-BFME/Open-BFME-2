// cl: /O2 /G7 /DNDEBUG /MD
//
// ModuleInfo::Nugget copy ctor, retail 0x00119A80, 78 bytes.
// First dword is a refcounted header pointer (word ++ at +4); the rest is
// four 28-byte POD copies.

struct NuggetString
{
	struct Header
	{
		int m_unreconstructed_00;
		unsigned short refCount;
	};
	Header *m_data;

	NuggetString(const NuggetString &that)
		: m_data(that.m_data)
	{
		if (m_data)
			m_data->refCount += 1;
	}
};

struct NuggetBlock
{
	int m_words[7];
};

class ModuleInfo
{
public:
	struct Nugget
	{
		Nugget(const Nugget &that);

		NuggetString name;
		NuggetBlock a;
		NuggetBlock b;
		NuggetBlock c;
		NuggetBlock d;
	};
};

ModuleInfo::Nugget::Nugget(const Nugget &that)
	: name(that.name),
	  a(that.a),
	  b(that.b),
	  c(that.c),
	  d(that.d)
{
}
