// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/stringinline
//
// ??1Rva0045EF90Object@@UAE@XZ, retail 0x00410421, 110 bytes. Dtor lane:
// class of ??0Rva0045EF90Object@@QAE@ABV0@@Z (vtable 0x00839630, base 0x0083962C).
// Layout from Code/GameEngine/Source/Common/Rva0045EF90CopyConstructor.cpp
// (3 strings at +8/+0xC/+0x28, handle at +0x10, ints to +0x20, byte +0x24).
// Callers of the dtor: 0x00410492 (its ??_G), 0x004104E1, 0x00411289.
// Callees all rowed/pinned: __EH_prolog, ??1?$StringBase@D@@QAE@XZ x3 (0x00036410).

template <typename T> class StringBase
{
public:
	~StringBase();
private:
	void *m_data;
};
typedef StringBase<char> AsciiString;

class Rva00410421Manager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void unregister(unsigned handle);
};
extern Rva00410421Manager *g_rva00410421Manager;

class Rva0045EF90Base
{
public:
// ??1Rva0045EF90Base@@UAE@XZ present-unmatched
	virtual ~Rva0045EF90Base() {}
private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	virtual ~Rva0045EF90Object();
private:
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	unsigned m_value14;
	unsigned m_value18;
	unsigned m_value1c;
	unsigned m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[3];
	AsciiString m_last;
};

Rva0045EF90Object::~Rva0045EF90Object()
{
	if (g_rva00410421Manager)
		g_rva00410421Manager->unregister(m_handle);
	m_handle = 0;
}

// ?g_rva00410421Manager@@3PAVRva00410421Manager@@A: the global at this VA is ?TheWindowManager@@3PAVGameWindowManager@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_rva00410421Manager@@3PAVRva00410421Manager@@A=?TheWindowManager@@3PAVGameWindowManager@@A")
// ?g_rva00410421Manager@@3PAVRva00410421Manager@@A: the global at VA 0xdfef1c is ?TheWindowManager@@3PAVGameWindowManager@@A.
#pragma comment(linker, "/alternatename:?g_rva00410421Manager@@3PAVRva00410421Manager@@A=?TheWindowManager@@3PAVGameWindowManager@@A")
