// cl: /MD
// ?rva000A9DC4@Rva000A9DC4@@QAE?AVAssetReference@@XZ @0x000A9DC4 47B by-value AssetReference getter via iface GetRef slot 4
// Evidence: EBP frame push ecx and ebp-4 0 guard is compiler by-value-return machinery not source local per siblings Rva0007B9EEGet 0x0007B9EE and Rva0007BB4BGet 0x0007BB4B same cl; mov ecx [ecx] m_p at +0 test je; mov eax [ecx] call [eax+0x10] GetRef test jne; mov eax ebp+8 and [eax] 0 default inline m_object 0 else mov ecx ebp+8 push eax call copy ??0AssetReference@@QAE@ABV0@@Z rowed 0x000424BB; mov eax ebp+8 leave ret 4; caller 0x000A9F23 forwards sret; canonical AssetReference default inline plus copy plus dtor declared-only from Rva009EBDC0.cpp
#pragma optimize("t", on)
class AssetReference
{
public:
	AssetReference() : m_object(0) {}
	AssetReference(const AssetReference &that);
	~AssetReference();
private:
	void *m_object;
};
#pragma optimize("", on)
class Rva000A9DC4Iface
{
public:
	virtual void _0();
	virtual void _1();
	virtual void _2();
	virtual void _3();
	virtual const AssetReference *GetRef() const;
};
class Rva000A9DC4
{
public:
	AssetReference rva000A9DC4();
private:
	Rva000A9DC4Iface *m_p;
};

AssetReference Rva000A9DC4::rva000A9DC4()
{
	Rva000A9DC4Iface *p = m_p;
	if (p == 0)
		return AssetReference();
	const AssetReference *ref = p->GetRef();
	if (ref == 0)
		return AssetReference();
	return *ref;
}
