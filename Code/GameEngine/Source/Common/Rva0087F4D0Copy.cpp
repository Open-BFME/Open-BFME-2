// cl: /Ob0

// `copyFrom` copies the narrow-string tail at +0x0C. The matched
// StringBase<char> copy constructor at 0x000365F0 shares that buffer under the
// refcount lock; both calls take the destination in ECX and a source pointer
// on the stack, and the constructor's EAX result is unused here. Bind the
// address-derived spelling to the row without changing the verified call.
#pragma comment(linker, "/alternatename:?copyFrom@BfmeTailF4@@QAEXPAU1@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")

struct BfmeTailF4
{
	void copyFrom(BfmeTailF4 *src);
};

struct BfmeElemF4
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTailF4 m_0C;
};

BfmeElemF4 *bfmeCopyF4(BfmeElemF4 *first, BfmeElemF4 *last, BfmeElemF4 *dest)
{
	BfmeElemF4 *d = dest;
	while (first != last)
	{
		if (d)
		{
			d->m_00 = first->m_00;
			d->m_04 = first->m_04;
			d->m_08 = first->m_08;
			d->m_0C.copyFrom(&first->m_0C);
		}
		first++;
		d++;
	}
	return d;
}
