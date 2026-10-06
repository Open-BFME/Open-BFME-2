// cl: /DNDEBUG /MD /EHsc
// ??1Rva004D60CA@@MAE@XZ retail 0x004D60E3 54B.
// Dtor lane: vptr 0x860464 then Wide releaseBuffer at +0x1c then vptr 0x860130.
// Evidence: ctor 0x004D60CA plus setter 0x004D6187 plus vtable 0x860464.

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

class NetCommandMsg
{
public:
	NetCommandMsg();
protected:
	virtual inline ~NetCommandMsg() {}
private:
	char m_pad04[0x1c - 0x04];
};

class Rva004D60CA : public NetCommandMsg
{
protected:
	virtual ~Rva004D60CA();
private:
	StringBase<unsigned short> m_str1c;
};

Rva004D60CA::~Rva004D60CA()
{
}
