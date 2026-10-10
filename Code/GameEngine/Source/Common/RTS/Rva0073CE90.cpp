// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// Native 73CE90..73CEE6 and WB ShroudManagerImpl::ChangeValue establish
// x, y, radius, counter, signed integer amount, and mask. Native 739FBD
// negates and passes the complete amount word. No bool aliasing is needed.
// The established neutral owner spelling and updater layout are retained.
class Gen_008F7CD0;
class Rva0073BBE0
{
public:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
	int m_counter;
	int m_amount;
};
class Gen_008F7CD0
{
public:
	void rva0073CE90(int x, int y, int radius, int counter, int amount, int mask);
};
char __cdecl Rva0073C820Raster(int centerX, int centerY, int radius, Rva0073BBE0 updater);
void Gen_008F7CD0::rva0073CE90(int x, int y, int radius, int counter, int amount, int mask)
{
	if (mask == 0)
		return;
	if (radius < 0)
		return;
	if (counter < 0 || counter >= 3)
		return;
	if (amount == 0)
		return;
	Rva0073BBE0 updater;
	updater.m_grid = this;
	updater.m_mask = (unsigned int)mask & 0xFFFFF;
	updater.m_counter = counter;
	updater.m_amount = amount;
	Rva0073C820Raster(x, y, radius, updater);
}
