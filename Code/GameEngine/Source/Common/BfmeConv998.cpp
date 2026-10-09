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

	int bfmeGo998C(int a);
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
