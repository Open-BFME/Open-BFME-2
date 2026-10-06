// cl: /EHsc /MD
// ?Rva00566E6CParse@@YAXPAUArg00566E6C@@PAVObjectTypes@@@Z at 0x00566E6C (113B). INI token to ObjectTypes.
// Evidence: temp copy via 0x365F0 plus inlined empty check; global ScriptEngine 0x00DFE16C via getObjectTypes 0x357651;
// ObjectTypes assign 0x376A9C when found else check-add 0x376B50; release 0x36410; chain via 0x376B50.
template <typename T> struct BfmeStringData;
template <typename T> class StringBase {
	friend class AsciiString;
	StringBase(const StringBase &);
	void releaseBuffer();
protected:
	BfmeStringData<T> *m_data;
public:
	void *data() const { return m_data; }
	void toLower();
};
class AsciiString : public StringBase<char> {
public:
	AsciiString(const AsciiString &o) : StringBase<char>(o) {}
	~AsciiString() { releaseBuffer(); }
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class ObjectTypes;
class ScriptEngine {
public:
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
};
extern ScriptEngine *TheScriptEngine;

class ObjectTypes {
public:
	ObjectTypes &operator=(const ObjectTypes &that);
};

class Rva00376A62 {
public:
	void rva00376B50(const AsciiString &val);
};

struct Arg00566E6C {
	unsigned char m_pad[0x10];
	StringBase<char> m_10;
};

void Rva00566E6CParse(struct Arg00566E6C *src, class ObjectTypes *dst);

void Rva00566E6CParse(struct Arg00566E6C *src, class ObjectTypes *dst)
{
	if (!dst)
		return;
	AsciiString tmp((const AsciiString &)src->m_10);
	void *p = tmp.data();
	if (!p || *(unsigned short *)((char *)p + 4) == 0)
		return;
	ObjectTypes *found = TheScriptEngine->getObjectTypes(tmp);
	if (!found)
		((Rva00376A62 *)dst)->rva00376B50(tmp);
	else
		*dst = *found;
}
