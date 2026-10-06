// cl: /MD
// ?rva00069322@Rva00069322@@QAE?AVAssetReference@@XZ @0x00069322 27B
// By-value AssetReference getter returning member at +0x3C. Retail copies
// into hidden return buffer via rowed copy ctor 0x000424BB. Evidence: unlock
// lane; same EBP frame and-zero mov-eax leave ret-4 shape as Rva0007B9EEGet
// (0x0007B9EE) under same flags; unblocks 0x00069DB1.
class AssetReference
{
public:
	AssetReference(const AssetReference &that);
	~AssetReference();
};
class Rva00069322
{
public:
	AssetReference rva00069322();
private:
	int m_pad00[15];
	AssetReference m_ref3C;
};
AssetReference Rva00069322::rva00069322()
{
	return m_ref3C;
}
