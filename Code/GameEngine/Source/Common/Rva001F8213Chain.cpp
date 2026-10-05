// cl: /O1 /DNDEBUG /MD
//
// Chained conditional-forward methods: each calls virtual slot 3 on its
// +0x00 pointer when non-null, then calls the previous family member on
// its +0x04 member object. The chain resolves inside this TU; only the
// root's predecessor 0x001F6492 (same shape, outside this lane) is pinned
// from the root body's own REL32.
// 0x001F8213 -> 0x001F6492. 0x001F8960 -> 0x001F8213.
// 0x001F8DE2 -> 0x001F8960. 0x001F9424 -> 0x001F8DE2.
// 0x001FA4C6 -> 0x001F9424. 0x001FA7CE -> 0x001FA4C6.

class Slot3Iface001F8213
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03(int a0, int a1) = 0;
};

class Rva001F6492Helper
{
public:
	void helper(int a0, int a1);
};

class Rva001F8213
{
public:
	void rva001F8213(int a0, int a1);
private:
	Slot3Iface001F8213 *m_00;
	Rva001F6492Helper m_04;
};
void Rva001F8213::rva001F8213(int a0, int a1)
{
	if (m_00)
		m_00->v03(a0, a1);
	m_04.helper(a0, a1);
}

class Rva001F8960
{
public:
	void rva001F8960(int a0, int a1);
private:
	Slot3Iface001F8213 *m_00;
	Rva001F8213 m_04;
};
void Rva001F8960::rva001F8960(int a0, int a1)
{
	if (m_00)
		m_00->v03(a0, a1);
	m_04.rva001F8213(a0, a1);
}

class Rva001F8DE2
{
public:
	void rva001F8DE2(int a0, int a1);
private:
	Slot3Iface001F8213 *m_00;
	Rva001F8960 m_04;
};
void Rva001F8DE2::rva001F8DE2(int a0, int a1)
{
	if (m_00)
		m_00->v03(a0, a1);
	m_04.rva001F8960(a0, a1);
}

class Rva001F9424
{
public:
	void rva001F9424(int a0, int a1);
private:
	Slot3Iface001F8213 *m_00;
	Rva001F8DE2 m_04;
};
void Rva001F9424::rva001F9424(int a0, int a1)
{
	if (m_00)
		m_00->v03(a0, a1);
	m_04.rva001F8DE2(a0, a1);
}

class Rva001FA4C6
{
public:
	void rva001FA4C6(int a0, int a1);
private:
	Slot3Iface001F8213 *m_00;
	Rva001F9424 m_04;
};
void Rva001FA4C6::rva001FA4C6(int a0, int a1)
{
	if (m_00)
		m_00->v03(a0, a1);
	m_04.rva001F9424(a0, a1);
}

class Rva001FA7CE
{
public:
	void rva001FA7CE(int a0, int a1);
private:
	Slot3Iface001F8213 *m_00;
	Rva001FA4C6 m_04;
};
void Rva001FA7CE::rva001FA7CE(int a0, int a1)
{
	if (m_00)
		m_00->v03(a0, a1);
	m_04.rva001FA4C6(a0, a1);
}
