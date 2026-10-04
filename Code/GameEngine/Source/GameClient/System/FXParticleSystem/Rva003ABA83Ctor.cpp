// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva003ABA83@@QAE@PAX0@Z @0x003ABA83 42B
// Unlock lane: ctor calling rowed T1Base 0x0055C903 with same (a,b) then
// vtable g_00C1C334 plus address of s_slot3E4first at +0x14 and g_ data at
// +0x18 as immediates. Evidence: three mov-dword immediates; base ctor rowed;
// s_slot3E4first extern C; neighbours /O1 /EHsc; ret 8 frameless.
extern "C" void *s_slot3E4first;
extern const void *const g_00C1C334[];
extern const void *const g_00C1C780[];
extern const void *const g_00C1C324[];
class T1Base_005F3750
{
public:
	T1Base_005F3750(void *a, void *b);
	virtual ~T1Base_005F3750();
private:
	char m_pad[0x14 - 4];
};
class Rva003ABA83 : public T1Base_005F3750
{
public:
	Rva003ABA83(void *a, void *b);
private:
	void *m_14;
	void *m_18;
};
Rva003ABA83::Rva003ABA83(void *a, void *b) : T1Base_005F3750(a, b)
{
	*(void **)this = (void *)g_00C1C334;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)g_00C1C324;
}
