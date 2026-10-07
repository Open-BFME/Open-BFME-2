// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva0059B355@Rva0059B355@@QAE?AV?$StringBase@D@@XZ @0x0059B355 (108 bytes).
// Address-derived identity: retail calls AsciiStringPlusText::length at +0x10,
// adds the field at +0x18, writes through rowed 0x0059B1C7, and returns a copied
// narrow StringBase. The class layout follows those retail offsets.
class AsciiStringPlusText
{
public:
	int length() const;
private:
	const void *m_string;
};

template <class T> class StringBase;
template <> class StringBase<char>
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<char> &other);
	// The existing destructor alias resolves to retail releaseBuffer at RVA 0x36410.
	~StringBase();
	char *getBufferForRead(int len);
private:
	void releaseBuffer();
	void *m_data;
};

class Rva0059B1C7
    : public AsciiStringPlusText
{
public:
	int rva0059B1C7(char *dst);
protected:
	char m_pad[12];
	int m_first;
	char m_pad1[4];
	int m_second;
};

class Rva0059B355 : public Rva0059B1C7
{
public:
	StringBase<char> rva0059B355();
};

StringBase<char> Rva0059B355::rva0059B355()
{
	StringBase<char> result;
	int first = m_first;
	int len = length() + first;
	len += m_second;
	char *buffer = result.getBufferForRead(len);
	rva0059B1C7(buffer);
	return result;
}
