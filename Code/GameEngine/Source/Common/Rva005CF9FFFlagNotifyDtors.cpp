// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva005CF9FF@@UAE@XZ @0x005CF9FF 68B, ??1Rva005CFA43@@UAE@XZ @0x005CFA43
// 68B and ??1Rva005CFA87@@UAE@XZ @0x005CFA87 68B: three sibling dtors,
// identical but for their own vtables 0x00C752CC, 0x00C752D4 and 0x00C752DC
// (callers: the rowed ??_G wrappers 0x005CFDDC, 0x005CFDF8, 0x005CFE14).
// Each stores its vtable; when its flag byte (+0x10, +0x08 and +0x0C respectively) is set and the global
// at VA 0x00E05FAC is non-null, calls the pinned Rva0054CBEFTarget::method
// 0x0054CBEF on it with 0 (the same gated call, with 1, as the rowed
// ??1Rva004FBCBE, whose (int)AptStrategicMessageBox::s_instance spelling is reused); then the inline
// base dtor resets to 0x00C75290 (Rva005CF872, as in Rva005CFDA6Dtor.cpp).
// Identities unproven; address-derived names.

class Rva0054CBEFTarget
{
public:
	void method(int arg);
};

class AptStrategicMessageBox {private: static AptStrategicMessageBox *s_instance; friend class Rva005CF9FF; friend class Rva005CFA43; friend class Rva005CFA87;};

class Rva005CF872
{
public:
	virtual ~Rva005CF872() {}
	virtual void slot1();
	virtual void slot2();

private:
	int m_04;
};

class Rva005CF9FF : public Rva005CF872
{
public:
	virtual ~Rva005CF9FF();
	virtual void slot1();

private:
	int m_08;
	int m_0C;
	bool m_flag;
};

Rva005CF9FF::~Rva005CF9FF()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

class Rva005CFA43 : public Rva005CF872
{
public:
	virtual ~Rva005CFA43();
	virtual void slot1();

private:
	bool m_flag;
};

Rva005CFA43::~Rva005CFA43()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

class Rva005CFA87 : public Rva005CF872
{
public:
	virtual ~Rva005CFA87();
	virtual void slot1();

private:
	int m_08;
	bool m_flag;
};

Rva005CFA87::~Rva005CFA87()
{
	if (m_flag && (int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
}

