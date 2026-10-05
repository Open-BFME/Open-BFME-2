// Four null-guarded first-member forwards (14B each): mov ecx, [ecx],
// test ecx, ecx, je ret-4, jmp <run>, ret 4. Each forwards one dword
// argument to the run method of the owned pointer at +0x00, returning
// early on null. 0x000A8B4B is defined as its peer-pinned
// MilesStreamRef::rva000A8B4B (void taking unsigned); the other three are
// address-derived owners with the same shape. Callee identities unproven
// (opaque run pins). One ledger row per forward.

class Rva0010FA6BRun
{
public:
	void run(unsigned value);
};

class Rva0010FDE9Run
{
public:
	void run(unsigned value);
};

class Rva0010FEF3Run
{
public:
	void run(unsigned value);
};

class Rva0010FFA2Run
{
public:
	void run(unsigned value);
};

class Rva000A8AA6Owner
{
public:
	void fwd(unsigned value);

private:
	Rva0010FA6BRun *m_first;
};

class Rva000A8B23Owner
{
public:
	void fwd(unsigned value);

private:
	Rva0010FDE9Run *m_first;
};

class MilesStreamRef
{
public:
	void rva000A8B4B(unsigned value);

private:
	Rva0010FEF3Run *m_first;
};

class Rva000A8C6EOwner
{
public:
	void fwd(unsigned value);

private:
	Rva0010FFA2Run *m_first;
};

void Rva000A8AA6Owner::fwd(unsigned value)
{
	Rva0010FA6BRun *target = m_first;
	if (target)
		target->run(value);
}

void Rva000A8B23Owner::fwd(unsigned value)
{
	Rva0010FDE9Run *target = m_first;
	if (target)
		target->run(value);
}

void MilesStreamRef::rva000A8B4B(unsigned value)
{
	Rva0010FEF3Run *target = m_first;
	if (target)
		target->run(value);
}

void Rva000A8C6EOwner::fwd(unsigned value)
{
	Rva0010FFA2Run *target = m_first;
	if (target)
		target->run(value);
}
