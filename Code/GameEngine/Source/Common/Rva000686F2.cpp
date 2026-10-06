// cl: /EHsc
// ?rva000686F2@Rva000686F2@@QAEXXZ @0x000686F2 198B
// Creates vertex + index buffers at +0x37a4/+0x37a8. Sizes at
// +0x37b8/+0x37bc come from TheWritableGlobalData+0xd45 flag
// (0xdac0/0x3fffc vs 0x36b0/0xffff). Evidence: leaf lane; callees
// rowed new BfmeDynamicNativeVB DX8IndexBufferClass EH_prolog;
// neighbours Rva000685E2Reset.cpp Rva000687B8.cpp share /O1;
// this+offsets match Rva000687B8 layout.
typedef unsigned int Uint;
typedef unsigned short UShort;
void *__cdecl operator new(Uint s);
class RefCountClass
{
public:
	virtual void Delete_This() {}
	int m_refs;
};
class BfmeDynamicNativeVB : public RefCountClass
{
public:
	BfmeDynamicNativeVB(Uint a, UShort b, Uint c, Uint d);
private:
	char _t[0x18];
};
class DX8IndexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(Uint count, UsageType u);
private:
	char _t[0x10];
};
class GlobalData
{
public:
	char _pad[0xD45];
	unsigned char m_flag;
};
extern GlobalData *TheWritableGlobalData;
class Rva000686F2
{
public:
	void rva000686F2();
private:
	char _pad[0x37A4];
	BfmeDynamicNativeVB *m_vb;
	DX8IndexBufferClass *m_ib;
	int m_37ac;
	int m_37b0;
	int m_37b4;
	Uint m_37b8;
	Uint m_37bc;
};
void Rva000686F2::rva000686F2()
{
	if (TheWritableGlobalData->m_flag)
	{
		m_37b8 = 0xDAC0;
		m_37bc = 0x3FFFC;
	}
	else
	{
		m_37b8 = 0x36B0;
		m_37bc = 0xFFFF;
	}
	m_vb = new BfmeDynamicNativeVB(0x142, (UShort)m_37b8, 0, 0);
	m_ib = new DX8IndexBufferClass(m_37bc, DX8IndexBufferClass::USAGE_DEFAULT);
	m_37b0 = 0;
	m_37b4 = 0;
}
