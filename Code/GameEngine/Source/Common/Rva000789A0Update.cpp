// cl: /DNDEBUG /MD
// ?Rva000789A0Update@@YGXPAVRva000789A0Outer@@@Z, retail 0x000789A0, 67 bytes.
// Free __stdcall setter: calls outer virtual at +0xC4 (slot 49), then if the
// holder at +0x2E8 is non-null stores nameToKey of the provider name (virtual
// at +0x18, slot 6) or "(NULL)" into holder+4. Evidence: ret 4 single stack
// arg used as this for both virtual calls; callee row
// ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z; string "(NULL)" at
// VA 0x007C6868; global dword at VA 0x009F36A4 used as NameKeyGenerator this.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva000789A0Named
{
public:
	virtual void na0();
	virtual void na1();
	virtual void na2();
	virtual void na3();
	virtual void na4();
	virtual void na5();
	virtual const char *getName();
};

struct Rva000789A0KeyHolder
{
	int m_unk;
	NameKeyType m_key;
};

class Rva000789A0Outer
{
public:
	virtual void a00();
	virtual void a01();
	virtual void a02();
	virtual void a03();
	virtual void a04();
	virtual void a05();
	virtual void a06();
	virtual void a07();
	virtual void a08();
	virtual void a09();
	virtual void a10();
	virtual void a11();
	virtual void a12();
	virtual void a13();
	virtual void a14();
	virtual void a15();
	virtual void a16();
	virtual void a17();
	virtual void a18();
	virtual void a19();
	virtual void a20();
	virtual void a21();
	virtual void a22();
	virtual void a23();
	virtual void a24();
	virtual void a25();
	virtual void a26();
	virtual void a27();
	virtual void a28();
	virtual void a29();
	virtual void a30();
	virtual void a31();
	virtual void a32();
	virtual void a33();
	virtual void a34();
	virtual void a35();
	virtual void a36();
	virtual void a37();
	virtual void a38();
	virtual void a39();
	virtual void a40();
	virtual void a41();
	virtual void a42();
	virtual void a43();
	virtual void a44();
	virtual void a45();
	virtual void a46();
	virtual void a47();
	virtual void a48();
	virtual Rva000789A0Named *getProvider();
	char m_pad[0x2E4];
	Rva000789A0KeyHolder *m_holder;
};

void __stdcall Rva000789A0Update(Rva000789A0Outer *obj)
{
	Rva000789A0Named *provider = obj->getProvider();
	if (obj->m_holder == 0)
		return;
	const char *name;
	if (provider != 0)
		name = provider->getName();
	else
		name = "(NULL)";
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	obj->m_holder->m_key = key;
}

// ?Rva0007898BClear@@YGXPAVRva000789A0Outer@@@Z, retail 0x0007898B, 21 bytes.
// Companion to Rva000789A0Update above: same outer (+0x2E8 holder) and holder
// (+4 m_key) layout; clears m_key to NK_UNKNOWN when holder is non-null.
// Evidence: ret 4 single stack arg; and [eax+4],0 under /O1; called from 0x78BAF.
void __stdcall Rva0007898BClear(Rva000789A0Outer *obj)
{
	if (obj->m_holder != 0)
		obj->m_holder->m_key = NK_UNKNOWN;
}
