// cl: /DNDEBUG /MD /EHsc
// ?rva0028C20F@Object@@QAEXH@Z @0x0028C20F 61B
// Object module loop: for each module at +0x244 get inner via mid+0xC slot 0x6C; if inner key slot0 == param call slot2.
// Evidence: +0x244 module array shared with ObjectRva0028C197; lea ecx [eax+0xC] plus slots 0x6C 0x0 0x8; ret 4;
// callers 0x00296B31 0x0036DDE1; neighbours ObjectRva0028C1CC and ObjectRva0028C264 give TU and flags.
class Rva0028C20FInner
{
public:
	virtual int getKey();
	virtual void slot01();
	virtual void doNotify();
};

class Rva0028C20FMid
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Rva0028C20FInner *getInner();
};

struct Rva0028C20FModule
{
	char m_pad00[0xC];
	Rva0028C20FMid m_mid; // +0xC embedded; lea ecx [eax+0xC] reaches its vptr
};

class Object
{
public:
	void rva0028C20F(int key);

private:
	char m_pad[0x244];
	Rva0028C20FModule **m_modules; // +0x244 null-terminated
};

void Object::rva0028C20F(int key)
{
	for (Rva0028C20FModule **m = m_modules; *m; ++m)
	{
		Rva0028C20FInner *inner = (*m)->m_mid.getInner();
		if (inner != 0)
		{
			if (inner->getKey() == key)
				inner->doNotify();
		}
	}
}
