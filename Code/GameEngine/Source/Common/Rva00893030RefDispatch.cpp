// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00894D80Accessor
{
public:
	static unsigned int increment(unsigned int *value);
};

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

void bfmeDropVGO(void *value);

class Rva006D07E0Key
{
public:
	Rva006D07E0Key(void *value) : m_value(value) {}
	Rva006D07E0Key(const Rva006D07E0Key &other) : m_value(other.m_value)
	{
		if (m_value)
			Rva00894D80Accessor::increment((unsigned int *)m_value);
	}
	~Rva006D07E0Key()
	{
		if (m_value && Rva00894D90Accessor::decrement((unsigned int *)m_value) == 0)
			bfmeDropVGO(m_value);
	}

	void *m_value;
};

class Rva008951B0Owner
{
public:
	void rva006D25C0(Rva006D07E0Key value, void *first, void *second, void *third);
};

class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
// g_rva00893030Manager: matched references place it at VA 0xe176cc (zero-filled .bss).
Rva00893030Manager * g_rva00893030Manager;

void Rva00893030(Rva006D07E0Key value, void *first, void *second, void *third)
{
	((Rva008951B0Owner *)g_rva00893030Manager)->rva006D25C0(value, first, second, third);
}
