// cl: /DNDEBUG /MD /EHsc
// ?Rva005DB335Get@@YAHH@Z @0x005DB335 53B
// Unlock free function returning 0-3 via global at 0x00E05FB4 with virtuals at +0x10/+0x14.
// Evidence: callers 0x005DB3AC (55B pushes int via ftol2) 0x0059EE00 0x0059F8E7; two virtual thresholds then 1/2/3.
class Rva00E05FB4
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual int vf4();
	virtual int vf5();
};

extern class GameSpyConfigInterface *TheGameSpyConfig;

int __cdecl Rva005DB335Get(int v)
{
	if (!(*(Rva00E05FB4 **)&TheGameSpyConfig))
		return 0;
	if (v < (*(Rva00E05FB4 **)&TheGameSpyConfig)->vf4())
		return 1;
	return v >= (*(Rva00E05FB4 **)&TheGameSpyConfig)->vf5() ? 3 : 2;
}
