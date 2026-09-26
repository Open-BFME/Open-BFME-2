// cl: /O1 /DNDEBUG /MD
//
// ??1W3DBuffDrawModuleData@@UAE@XZ 54B @0x000CEE5D.
// Gap between ctor 0xCEE4C and buildFieldParse 0xCEE93 in
// W3DBuffDrawModuleDataCtor.cpp; same flags. Single AsciiString at +08
// (BFME1 Destructor donor: m_modelName plus +0C flag) tears down through
// folded 0x36410 with derived-to-base vtable swap. Ctor models +08 as a
// word for its and-RMW, so the string view lives here.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	void *m_data;
};

class W3DBuffDrawModuleDataBase
{
public:
	virtual ~W3DBuffDrawModuleDataBase() {}

private:
	unsigned int m_word;
};

class W3DBuffDrawModuleData : public W3DBuffDrawModuleDataBase
{
public:
	virtual ~W3DBuffDrawModuleData();

private:
	AsciiString m_modelName; // +08
	bool m_flag; // +0C
	char m_pad0D[3];
};

W3DBuffDrawModuleData::~W3DBuffDrawModuleData()
{
}
