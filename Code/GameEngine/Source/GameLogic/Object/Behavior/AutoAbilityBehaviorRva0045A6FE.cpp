// cl: /DNDEBUG /MD /EHsc
//
// ?rva0045A6FE@AutoAbilityBehavior@@QAEXPAX@Z, retail 0x0045A6FE, 74 bytes.
// If src is null or its byte at +0x10C is clear, or its string at +0x10
// matches the member at +0x20, clears via the rowed 0x0045A413 plus rowed
// setWakeFrame FOREVER; otherwise copies via the rowed 0x0045A421.
// Compare rides the rowed StringBase::compare at 0x000069D6. Layout follows
// the rowed dtor ??1AutoAbilityBehavior at 0x0045A37F (AsciiString at +0x20,
// Object at +8) and callers at 0x00379545 plus 0x0045A892.

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

struct Rva0045A6FEArg
{
	unsigned char m_pad[0x10];
	AsciiString m_str10;
	unsigned char m_mid[0x10C - 0x10 - 4];
	bool m_flag10C;
};

class AutoAbilityBehavior
{
public:
	void rva0045A6FE(void *src);
	void rva0045A413();
	void rva0045A421(void *src);

private:
	unsigned char m_pad[8];
	Object *m_obj8;
	unsigned char m_mid[0x20 - 0xC];
	AsciiString m_str20;
};

void AutoAbilityBehavior::rva0045A6FE(void *src)
{
	Rva0045A6FEArg *s = (Rva0045A6FEArg *)src;
	if (!s || !s->m_flag10C || s->m_str10.m_impl.compare(m_str20.m_impl) == 0) {
		rva0045A413();
		((UpdateModule *)this)->setWakeFrame(m_obj8, UPDATE_SLEEP_FOREVER);
		return;
	}
	rva0045A421(s);
}
