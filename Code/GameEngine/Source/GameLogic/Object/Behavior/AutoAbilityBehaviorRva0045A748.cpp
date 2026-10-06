// cl: /DNDEBUG /MD /EHsc
//
// ?rva0045A748@AutoAbilityBehavior@@QAEXPAX_N@Z, retail 0x0045A748, 71 bytes.
// If src is null or its string at +0x10 differs from the member at +0x20,
// or the flag differs from zero, copies via the rowed 0x0045A421; otherwise
// clears via the rowed 0x0045A413 plus rowed setWakeFrame FOREVER. Compare
// rides the rowed StringBase::compare at 0x000069D6. Layout follows the rowed
// dtor ??1AutoAbilityBehavior at 0x0045A37F (AsciiString at +0x20, Object at
// +8) and the sibling 0x0045A6FE. Callers at 0x003C32B0 plus 0x003C339E.

class Object;

template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &other) const;

private:
	void *m_data;
};

class AsciiString
{
public:
	StringBase<char> m_impl;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModule
{
	friend class AutoAbilityBehavior;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime delay);
};

struct Rva0045A748Arg
{
	unsigned char m_pad[0x10];
	AsciiString m_str10;
};

class AutoAbilityBehavior
{
public:
	void rva0045A748(void *src, bool flag);
	void rva0045A413();
	void rva0045A421(void *src);

private:
	unsigned char m_pad[8];
	Object *m_obj8;
	unsigned char m_mid[0x20 - 0xC];
	AsciiString m_str20;
};

void AutoAbilityBehavior::rva0045A748(void *src, bool flag)
{
	Rva0045A748Arg *s = (Rva0045A748Arg *)src;
	if (!s || s->m_str10.m_impl.compare(m_str20.m_impl) != 0 || flag != false) {
		rva0045A421(s);
		return;
	}
	rva0045A413();
	((UpdateModule *)this)->setWakeFrame(m_obj8, UPDATE_SLEEP_FOREVER);
}
