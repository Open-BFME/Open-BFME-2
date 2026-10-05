// ??0Rva00052568@@QAE@XZ
// partial score=0.93 date=2026-10-05
// cl: /EHsc /O1 /DNDEBUG /MD
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};
class TextureClass : public TextureBaseClass
{
};
template<class T>
class RefCountPtr
{
public:
	RefCountPtr();
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
private:
	T *Referent;
};
class Rva00052568
{
	unsigned char m_0;
	unsigned char m_1;
	unsigned char m_2;
	unsigned char m_3;
	int m_4;
	int m_8;
	int m_C;
	unsigned char m_10;
	char m_pad11[3];
	int m_14;
	int m_18;
	int m_1C;
	RefCountPtr<TextureClass> m_20;
	RefCountPtr<TextureClass> m_24;
	RefCountPtr<TextureClass> m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	unsigned char m_44;
public:
	Rva00052568();
};
Rva00052568::Rva00052568()
	: m_0(0), m_1(0), m_2(1), m_3(0), m_4(0), m_8(0), m_C(0), m_10(0)
	, m_14(0), m_18(0), m_1C(0)
	, m_2C(0), m_30(0), m_34(0), m_38(0), m_3C(0), m_40(0), m_44(0)
{
}
