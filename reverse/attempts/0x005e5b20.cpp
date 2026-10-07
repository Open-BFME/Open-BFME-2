// ?rva005E5B20@Rva005E5B20@@QAEXPAXH@Z
// partial score=0.85 date=2026-10-07
// cl: /MD /O1 /arch:SSE /G7 /EHsc
// ?rva005E5B20@Rva005E5B20@@QAEXPAXH@Z @0x005E5B20 98B.
// Called from 0x005E5B82 with a rectangle and integer; target constructs
// Rva005E5A38 and applies a three-integer setter or clears the +0x38 field.
class Rva0005CB9F3DwordImmSetter
{
public:
	void apply();

private:
	int m_storage;
};

class Rva00574815 : public Rva0005CB9F3DwordImmSetter
{
public:
	void rva005CBB4A(int, int, int);
};

class Rva005E5A38 : public Rva00574815
{
public:
	Rva005E5A38(int);
	virtual ~Rva005E5A38() { apply(); }

private:
	int m_value;
};

class Rva000AD6F4
{
public:
	void clear();

private:
	char m_data[4];
};

class Rva005E5B20
{
public:
	void rva005E5B20(void *rect, int value);

private:
	char m_pad00[8];
	int m_value08;
	void *m_context0c;
	char m_pad10[0x20];
	int m_enabled30;
	char m_pad34[4];
	Rva000AD6F4 m_clearable38;
	bool m_active3c;
};

void Rva005E5B20::rva005E5B20(void *rect, int value)
{
	m_active3c = true;
	if (m_enabled30 != 0) {
		Rva005E5A38 setter((int)this);
		setter.rva005CBB4A(m_value08, (int)rect, *(int *)((char *)m_context0c + 0x1c));
	} else {
		m_clearable38.clear();
	}
}
