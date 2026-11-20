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

class Rva00082D6A
{
public:
	void rva00082D6A();	// 0x00082D6A
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
	((Rva00082D6A *)((char *)this - 8))->rva00082D6A();
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

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00007850 reads ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:?Init@Rva000BB3D7Part@@QAEXXZ=??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")
//   0x0033C432 reads ??0?$map@EHU?$less@E@_STL@@V?$allocator@U?$pair@$$CBEH@_STL@@@2@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:?Init@Rva004FFE72Part@@QAEXXZ=??0?$map@EHU?$less@E@_STL@@V?$allocator@U?$pair@$$CBEH@_STL@@@2@@_STL@@QAE@XZ")
