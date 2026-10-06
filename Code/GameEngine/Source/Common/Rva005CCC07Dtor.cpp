// cl: /MD /EHsc
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
private:
	class RefHolder
	{
	public:
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
};

Rva005CCC07::~Rva005CCC07()
{
}
