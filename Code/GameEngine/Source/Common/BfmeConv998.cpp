// Retail16AB90 returns the final get_vert_normals16AAE0 result in EAX.
// Caller1482B5 consumes it as the normals pointer; WB A0CF10 corroborates
// the validation wrapper. Preserve the existing opaque identity/layout.
class BfmeC998
{
public:
	virtual void bfmeVX0998();
	virtual void bfmeVX1998();
	virtual void bfmeVX2998();
	virtual void bfmeVX3998();
	virtual void bfmeApply998(int v, int a);

	// The independently bounded143A90 wrapper calls this body out of line.
	__declspec(noinline) int bfmeGo998C(int a);
	int bfmeConv998(int a);

	char m_bfmePad[0x14];
	int m_bfmeFlags;
};

int BfmeC998::bfmeGo998C(int a)
{
	if (m_bfmeFlags & 4)
		bfmeApply998(bfmeConv998(a), a);

	return bfmeConv998(a);
}

// Whole clean BF1 f98983a7 WW3D2/dx8renderer.cpp emits the source lead
// Vertex_Split_Table::Get_Vertex_Normal_Array. Native143A90..143A9A is
// independently INT3-bounded: receiver word0 becomes the receiver for the
// genuine16AB90 provider above, argument0 is passed, and EAX is unchanged.
// The donor's union recasts a void-return declaration; the established target
// provider already returns raw EAX, so no ABI cast or alias is needed here.
// No direct/address witnesses name this wrapper. Original enclosing owner,
// result type and payload interpretation remain unknown; retain its observed
// one-pointer prefix and the existing provider's declaration.
struct Rva00143A90ProviderHolder {
    BfmeC998 *provider;
    int queryZero() const;
};
int Rva00143A90ProviderHolder::queryZero() const {
    return provider->bfmeGo998C(0);
}
