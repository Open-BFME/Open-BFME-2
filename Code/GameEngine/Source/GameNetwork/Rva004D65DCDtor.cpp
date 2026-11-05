// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva004D65DC@@MAE@XZ retail 0x004D6708 69B.
// Dtor: vptr 0x860530 then Ascii releaseBuffer at +0x20 then at +0x1c then vptr 0x860130.
// Evidence: ctor 0x004D65DC plus setter 0x004D662D plus vtable 0x860530 plus caller 0x004D6B10.
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();

typedef int Int;
typedef bool Bool;
class AsciiString;

// Retail base vtable 0x860130: deleting dtor, getSortNumber, a bool slot,
// getContentsAsAsciiString; matches NetCommandMsgCtor.cpp's view.
class NetCommandMsg
{
public:
	NetCommandMsg();
protected:
	virtual ~NetCommandMsg();
public:
	virtual Int getSortNumber();
	virtual Bool vslot08() { return false; }
	virtual AsciiString getContentsAsAsciiString();
private:
	char m_pad04[0x1c - 0x04];
};
// ??1NetCommandMsg@@MAE@XZ present-unmatched
inline NetCommandMsg::~NetCommandMsg() {}
class Rva004D65DC : public NetCommandMsg
{
protected:
	virtual ~Rva004D65DC();
private:
	StringBase<char> m_str1c;
	StringBase<char> m_str20;
public:
	// retail vftable slot: the rowed override
	virtual AsciiString getContentsAsAsciiString();
};
Rva004D65DC::~Rva004D65DC()
{
}
