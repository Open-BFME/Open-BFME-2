// cl: /DNDEBUG /MD /EHsc
// ??0Rva003FD789@@QAE@ABV?$StringBase@D@@@Z @0x003FD716 109B
// Ctor of Rva003FD789 (vtable 0x00837D78): empty unwindable base arms EH 0,
// StringBase<char> at +0x0C default-cleared, bytes/float/word at +0x10/+0x11/
// +0x14/+0x18 zeroed, StringBase<char> at +0x1C copy-constructed from the
// single reference param via rowed ??0?$StringBase@D@@AAE@ABV0@@Z (pin at
// 0x000365F0, EH 1), then tail floats at +0x20/+0x24/+0x28 and words at
// +0x04/+0x08 zeroed. Same ModuleData EH recipe as ProductionUpdateModuleDataCtor.
// Unblocks 0x0021294A and 0x0021219E.
extern "C" const void *const vtbl_00837D78[];  // ??_7Rva003FD789@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00837D78=??_7Rva003FD789@@6B@")
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	~StringBase();
private:
	StringBase(const StringBase &other);
	friend class Rva003FD789;
	T *m_data;
};

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class Rva003FD789 : public EmptyBase
{
public:
	Rva003FD789(const StringBase<char> &src);
private:
	const void *m_vtable; // +0, retail 0x00837D78 (explicit so no vtable emitted)
	int volatile m_04;
	float volatile m_08;
	StringBase<char> m_0c;
	bool m_10;
	bool m_11;
	float m_14;
	short m_18;
	StringBase<char> m_1c;
	float volatile m_20;
	float volatile m_24;
	float volatile m_28;
};

Rva003FD789::Rva003FD789(const StringBase<char> &src)
	: m_vtable(vtbl_00837D78)
	, m_10(false)
	, m_11(false)
	, m_14(0.0f)
	, m_18(0)
	, m_1c(src)
{
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_04 = 0;
	m_08 = 0.0f;
}
