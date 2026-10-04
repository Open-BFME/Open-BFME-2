// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva0073CE90@Gen_008F7CD0@@QAEXHHHH_NH@Z 86B @0x0073CE90: shroud circle wrapper building Rva0073BBE0 updater (grid=this mask&0xFFFFF) then rowed Raster 0x0073C820. Guards mask!=0 radius>=0 counter 0..2 flag!=0. Layout grid+0 mask+4 counter+8 amount+0xC from rowed BBE0. Evidence: rowed Raster plus callers at 0x00739E2E 0x00739FBD plus LINK BONUS name. Retail loads/stores 5th bool param as dword so it is read via int pun to keep bool mangling and dword bytes.
// Caller 0x00739FBD pushes int neg for 5th arg but LINK caller 0x00739E2E passes bool dword copy with no conversion so bool name links with no edit.
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
	void rva0073CE90(int x, int y, int radius, int counter, bool flag, int mask);
};
char __cdecl Rva0073C820Raster(int centerX, int centerY, int radius, Rva0073BBE0 updater);
void Gen_008F7CD0::rva0073CE90(int x, int y, int radius, int counter, bool flag, int mask)
{
	if (mask == 0)
		return;
	if (radius < 0)
		return;
	if (counter < 0 || counter >= 3)
		return;
	int flagInt = *(int *)&flag;
	if (flagInt == 0)
		return;
	Rva0073BBE0 updater;
	updater.m_grid = this;
	updater.m_mask = (unsigned int)mask & 0xFFFFF;
	updater.m_counter = counter;
	updater.m_amount = flagInt;
	Rva0073C820Raster(x, y, radius, updater);
}
