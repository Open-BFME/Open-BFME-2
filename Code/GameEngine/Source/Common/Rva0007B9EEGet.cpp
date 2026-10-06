// cl: /MD
//
// ?rva0007B9EE@Rva0007B9EE@@QAE?AVAssetReference@@XZ @ 0x0007B9EE (27B):
// by-value AssetReference getter returning the member at +0x08. Retail
// copies into the hidden return buffer via the rowed copy ctor
// ??0AssetReference@@QAE@ABV0@@Z (0x000424BB). Shape is the minimal member
// of the family proven by Rva000F5D1BGet (0x000F5D1B: same EBP frame,
// and-zeroed [ebp-4] return-machinery slot, single copy-ctor call,
// mov eax hidden, leave, ret 4) under the same // cl: /O1 /MD. Owner
// unproven (6 callers unclaimed), so the class carries the honest address
// name. AssetReference is layout plus copy-ctor mangling only; canonical
// class keeps m_object private
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva009EBDC0.cpp).

class AssetReference
{
public:
	AssetReference(const AssetReference &that);
	~AssetReference();
};

class Rva0007B9EE
{
public:
	AssetReference rva0007B9EE();

private:
	int m_pad00[2];
	AssetReference m_ref08;
};

AssetReference Rva0007B9EE::rva0007B9EE()
{
	return m_ref08;
}
