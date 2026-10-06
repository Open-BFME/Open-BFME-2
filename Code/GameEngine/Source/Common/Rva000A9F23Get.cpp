// cl: /MD
// ?rva000A9F23@Rva000A9F23@@QAE?AVAssetReference@@XZ @0x000A9F23 37B by-value AssetReference getter forwarding sret
// Evidence: chain from 0x000A9DC4 just landed; EBP frame push ecx and ebp-4 0 guard is compiler by-value-return machinery per siblings Rva0007B9EEGet and Rva0007BB4BGet same cl; mov ecx [ecx+0x18] m_sub jne; mov eax ebp+8 and [eax] ecx clears with zero in ecx else push ebp+8 call ?rva000A9DC4 row; mov eax ebp+8 leave ret 4; caller 0x000AA2A7
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
class Rva000A9DC4
{
public:
	AssetReference rva000A9DC4();
};
class Rva000A9F23
{
public:
	AssetReference rva000A9F23();
private:
	int m_pad[6];
	Rva000A9DC4 *m_sub18;
};

AssetReference Rva000A9F23::rva000A9F23()
{
	Rva000A9DC4 *p = m_sub18;
	if (p == 0)
		return AssetReference();
	return p->rva000A9DC4();
}
