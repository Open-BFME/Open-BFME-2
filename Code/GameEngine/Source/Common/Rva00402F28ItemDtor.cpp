// cl: /MD
//
// ??1Rva00402F28Item@@QAE@XZ retail 0x00402F23 5B.
// Evidence: a lone tail jump to the rowed Rva003F9FE6 dtor 0x003FA0C7. The
// item copy ctor 0x00402F28 in Rva00403055CopyCtor.cpp stores vtable
// 0x00C37898 over that base, while this dtor stores nothing, so the class is
// spelled novtable here only, as the base dtor TU does. clearItems 0x00402C4E
// calls it directly before operator delete.

class __declspec(novtable) Rva003F9FE6
{
public:
	virtual void v00() = 0;
	~Rva003F9FE6();
private:
	char m_04[0x58 - 4];
};

class __declspec(novtable) Rva00402F28Item : public Rva003F9FE6
{
public:
	virtual void v00();
	~Rva00402F28Item();
private:
	unsigned char m_58;
	unsigned char m_59;
	unsigned char m_5A;
};

Rva00402F28Item::~Rva00402F28Item()
{
}
