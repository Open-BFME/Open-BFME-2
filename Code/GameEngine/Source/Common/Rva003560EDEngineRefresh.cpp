// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00355DF4@Rva003560ED@@QAEXH@Z @0x00355DF4 44B
// ?rva00355E20@Rva003560ED@@QAEXHH@Z @0x00355E20 44B
// Slots 1 and 4 of vtable 0x00C14EA4 (class of the rowed dtor 0x003560ED and
// of rva00355DDD, slot 3), shared by the derived vtable 0x00C14EBC: both call
// TheGameEngine slot 23 and, when TheWritableGlobalData's +0x11C8 flag is set,
// TheDisplay slot 73 with 0. They differ only in their ignored stack
// arguments (ret 4 / ret 8), so ICF could not fold them.
template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};
class GameEngine : public VirtualSlots<23>
{
public:
	virtual void slot23();
};
class Display : public VirtualSlots<73>
{
public:
	virtual void slot73(int value);
};
class GlobalData
{
public:
	unsigned char m_pad0000[0x11C8];
	bool m_11c8; // +0x11C8
};
extern GameEngine *TheGameEngine;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
class Rva003560ED
{
public:
	void rva00355DF4(int);
	void rva00355E20(int, int);
};
void Rva003560ED::rva00355DF4(int)
{
	TheGameEngine->slot23();
	if (TheWritableGlobalData->m_11c8)
		TheDisplay->slot73(0);
}
void Rva003560ED::rva00355E20(int, int)
{
	TheGameEngine->slot23();
	if (TheWritableGlobalData->m_11c8)
		TheDisplay->slot73(0);
}
