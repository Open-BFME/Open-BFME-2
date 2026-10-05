// Five null-checked member forwards (13B each): mov ecx, [ecx+off],
// test ecx, ecx, je ret, jmp <run>, ret. Each loads an owned pointer,
// returns early on null, else tail-jumps its parameterless run method:
// 0x001EB72F (+0x10 -> 0x001EB68A), 0x001EB75C (+0x10 -> 0x001EB6FE),
// 0x0020EB41 (+0x08 -> 0x0020E9A1), 0x005CCB16 (+0x04 -> 0x005CB283),
// 0x005D13D5 (+0x0C -> 0x000B3FD0, shared folded empty body).
// Callee/member/owner identities unproven (opaque run pins, even where the
// target is a known fold); names are address-derived.
// One ledger row per forward.

class Rva001EB68ARun
{
public:
	void run();
};

class Rva001EB6FERun
{
public:
	void run();
};

class Rva0020E9A1Run
{
public:
	void run();
};

class Rva005CB283Run
{
public:
	void run();
};

class Rva000B3FD0Run
{
public:
	void run();
};

class Rva001EB72F
{
public:
	void poll();

private:
	char m_pad[0x10];
	Rva001EB68ARun *m_ptr;
};

class Rva001EB75C
{
public:
	void poll();

private:
	char m_pad[0x10];
	Rva001EB6FERun *m_ptr;
};

class Rva0020EB41
{
public:
	void poll();

private:
	char m_pad[8];
	Rva0020E9A1Run *m_ptr;
};

class Rva005CCB16
{
public:
	void poll();

private:
	char m_pad[4];
	Rva005CB283Run *m_ptr;
};

class Rva005D13D5
{
public:
	void poll();

private:
	char m_pad[0x0C];
	Rva000B3FD0Run *m_ptr;
};

void Rva001EB72F::poll()
{
	Rva001EB68ARun *target = m_ptr;
	if (target)
		target->run();
}

void Rva001EB75C::poll()
{
	Rva001EB6FERun *target = m_ptr;
	if (target)
		target->run();
}

void Rva0020EB41::poll()
{
	Rva0020E9A1Run *target = m_ptr;
	if (target)
		target->run();
}

void Rva005CCB16::poll()
{
	Rva005CB283Run *target = m_ptr;
	if (target)
		target->run();
}

void Rva005D13D5::poll()
{
	Rva000B3FD0Run *target = m_ptr;
	if (target)
		target->run();
}

class RadarEventRef
{
public:
	void release();
};

class Rva0010FAEARun
{
public:
	void run();
};

class Rva0010FBDERun
{
public:
	void run();
};

class Rva0004E4BD
{
public:
	void poll();

private:
	RadarEventRef *m_ptr;
};

class Rva000A8AB4
{
public:
	void poll();

private:
	Rva0010FAEARun *m_ptr;
};

class Rva000A8ACC
{
public:
	void poll();

private:
	Rva0010FBDERun *m_ptr;
};

void Rva0004E4BD::poll()
{
	RadarEventRef *target = m_ptr;
	if (target)
		target->release();
}

void Rva000A8AB4::poll()
{
	Rva0010FAEARun *target = m_ptr;
	if (target)
		target->run();
}

void Rva000A8ACC::poll()
{
	Rva0010FBDERun *target = m_ptr;
	if (target)
		target->run();
}
