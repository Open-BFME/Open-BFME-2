// cl: /DNDEBUG /MD /EHsc
// ??1Rva00109C7F@@UAE@XZ @0x00109C7F 54B virtual dtor with StringClass member at +8.
// Retail stores derived vtable then calls rowed Free_String at +8 then stores base vtable with no base call.
// Evidence: pin ??1Rva00109C7F@@UAE@XZ; caller deleting dtor ??_GRva00109C7F@@UAEPAXI@Z at 0x00109C63 in OpaqueScalarDeletingDtorsB01.cpp; callee Free_String at 0x00610A40.
// Layout: vptr +0 with int at +4 then StringClass at +8; base inline empty virtual dtor supplies second store.
class StringClass
{
	void Free_String();
public:
	__forceinline ~StringClass(void) { Free_String(); }
private:
	char *m_Buffer;
};
class Rva00109C7FBase
{
public:
	virtual ~Rva00109C7FBase() {}
};
class Rva00109C7F : public Rva00109C7FBase
{
public:
	virtual ~Rva00109C7F();
private:
	int m_04;
	StringClass m_str;
};
Rva00109C7F::~Rva00109C7F()
{
}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
