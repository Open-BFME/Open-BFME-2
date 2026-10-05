class Rva000BB3D7Part
{
public:
	void Init();
};

class Rva000BB3D7Obj
{
public:
	char m_pad[4];
	Rva000BB3D7Part m_part;
	Rva000BB3D7Obj *Reset();
};

Rva000BB3D7Obj *Rva000BB3D7Obj::Reset()
{
	m_part.Init();
	return this;
}

class Rva004FFE72Part
{
public:
	void Init();
};

class Rva004FFE72Obj
{
public:
	char m_pad[4];
	Rva004FFE72Part m_part;
	Rva004FFE72Obj *Reset();
};

Rva004FFE72Obj *Rva004FFE72Obj::Reset()
{
	m_part.Init();
	return this;
}

class Rva00082E1DBase
{
public:
	void Init();
};

class Rva00082E1DObj
{
public:
	char m_pad[0x98];
	unsigned char m_enabled;
	void Start(int);
};

// Retail reaches the base 8 bytes below this (secondary-view wrapper),
// then raises the ready flag. The stack argument is unused.
void Rva00082E1DObj::Start(int)
{
	((Rva00082E1DBase *)((char *)this - 8))->Init();
	m_enabled = 1;
}

class Rva003733B5Base
{
public:
	void Init();
};

class Rva003733B5Obj
{
public:
	char m_pad[0x19];
	unsigned char m_enabled;
	void Start(int);
};

void Rva003733B5Obj::Start(int)
{
	((Rva003733B5Base *)((char *)this - 0x20))->Init();
	m_enabled = 1;
}
