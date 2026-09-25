// cl: /O1 /DNDEBUG /MD /EHsc
// INI::parseAsciiStringVectorAppend (retail 0x002E896, 169 bytes). BFME2
// growth of the BFME1 donor: each token is macro-expanded, and expansions
// differing from the token are split on the fly (nextToken with null seps)
// with every head pushed; unexpanded tokens push as-is. Element traffic
// rides the pinned vector<AsciiString>::push_back at 0x002DBE6 and the
// rowed StringBase pieces (PBD ctor 0x37BA0, nextToken 0x36D90, dtor).

typedef int Int;
typedef int Bool;

template <typename T> struct BfmeStringData;

template <typename T> class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

public:
	StringBase() : m_data(0) {}
	~StringBase();
	Bool compare(const char *other) const;
	void set(const T *text);
	bool nextToken(StringBase<T> *out, const T *seps);

protected:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
};

namespace _STL
{
template <typename T> class allocator
{
};

template <typename T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	static const char *preprocessMacro(const char *token);
	static void parseAsciiStringVectorAppend(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseAsciiStringVectorAppend@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseAsciiStringVectorAppend(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	_STL::vector<AsciiString> *vec = (_STL::vector<AsciiString> *)store;
	const char *token;
	while ((token = ini->getNextTokenOrNull(0)) != 0)
	{
		const char *macro = INI::preprocessMacro(token);
		if (macro != token)
		{
			AsciiString multi(macro);
			AsciiString head;
			while (multi.nextToken(&head, 0))
				vec->push_back(head);
		}
		else
		{
			AsciiString single(token);
			vec->push_back(single);
		}
	}
}
