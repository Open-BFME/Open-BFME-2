// cl: /O1 /G7 /arch:SSE /MD /EHsc
// ??1Rva005CCC07@@UAE@XZ retail 0x005CCC07 73B: virtual dtor stores vtable then destroys StringBase member at +8 via releaseBuffer then releases RefCount pointer at +4 then stores base vtable.
// Evidence: two vtable stores 0x00874F04 entry and 0x00877E7C exit with releaseBuffer and Release_Ref calls between; caller 0x005CCC69 tail-jmps here and deleting dtor 0x005CCC98 calls there.

class RefCountClass
{
public:
	void Release_Ref();
};

template <typename T>
class StringBase
{
private:
	void releaseBuffer();
	T *m_data;
public:
	StringBase() : m_data(0) {}
    ~StringBase() { releaseBuffer(); }
};

class Rva005CCC07Base
{
public:
	virtual ~Rva005CCC07Base() {}
};

class Rva005CCC07 : public Rva005CCC07Base
{
public:
	virtual ~Rva005CCC07();
    Rva005CCC07();
private:
	class RefHolder
	{
	public:
		RefHolder() : m_ptr(0) {}
            ~RefHolder()
		{
			if (m_ptr)
				m_ptr->Release_Ref();
		}
	private:
		RefCountClass *m_ptr;
	};
	RefHolder m_ref;
	StringBase<unsigned short> m_str;
    int m_0C;
    int m_10;
    float m_14, m_18, m_1C;
    unsigned char m_20, m_21, m_22, m_23;
};

Rva005CCC07::~Rva005CCC07()
{
}

Rva005CCC07::Rva005CCC07()
{
    m_10 = -1;
    m_0C = 0;
    m_14 = 0.0f;
    m_18 = 0.0f;
    m_1C = 0.0f;
    m_20 = 0;
    m_21 = 0;
    m_22 = 1;
    m_23 = 0;
}
class Rva005CCC69 : public Rva005CCC07 {
public:
    Rva005CCC69(void *arg);
    virtual ~Rva005CCC69();
    void *m_24;
};
Rva005CCC69::Rva005CCC69(void *arg) : m_24(arg) {}

// Native55B base constructor5CCBD0..5CCC07: real RefHolder and StringBase
// default construction explain why OR10,-1 follows the two initialized handles;
// the old flat-pointer bank let the optimizer move that OR ahead of the vptr.
// The 25B child5CCC50..5CCC69 keeps its receiver in EDX across the base ctor,
// because the definition here proves EDX preserved. Base extent24 from its
// last flag23 and the child member24; dtor identity from native C74F04/C74F24.
