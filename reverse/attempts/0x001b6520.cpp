// ?d_009a5aa0@@YAXPAXPAXPAXH@Z
// partial score=0.39 date=2026-09-22
// d_009a5aa0 (193B @0x001B6520) partial: clamp-table fill + staging copy + tier dispatch.
// Called once from Rva009A4D00Init with (table, table, table, 7): clamps the
// signed index range [-256, 512) into [0, 255] over the byte table at
// 0x00E23000, stages 64 dwords to 0x00E22BE0, then installs the tier dispatch
// pair and runs bfmeInstallCpuDispatchTable (rowed YAXXZ @0x1C1750, called
// through an int-taking cast so the push emits with zero new pins).
// Build with: // cl: /DNDEBUG /MD /O2 (TableInit family flags; /O1 merges the
// tier tails and hoists 0xFF to edx, both refuted by retail).

void __cdecl bfmeInstallCpuDispatchTable(void);

typedef void (__cdecl *TierDispatchFn)(int tier);

void d_009a5aa0(void *p1, void *p2, void *p3, int tier)
{
	int i;
	int v;
	for (i = -256; i < 512; ++i)
	{
		if (i < 0)
			v = 0;
		else
		{
			v = i;
			if (v > 255)
				v = 255;
		}
		((unsigned char *)0x00E23100)[i] = (unsigned char)v;
	}

	*(void **)0x00E22CE8 = p2;
	int *dst = (int *)0x00E22BE0;
	*(void **)0x00E22CF0 = p1;
	*(void **)0x00E22CE4 = p3;

	{
		unsigned int ofs = (unsigned char *)p3 - (unsigned char *)dst;
		for (; (int)dst < 0x00E22CE0; ++dst)
			*dst = *(int *)((unsigned char *)dst + ofs);
	}

	if (tier >= 6U)
	{
		*(int *)0x00E22CE0 = 0x00DB7728;
		*(int *)0x00E22CEC = 0x00DB7328;
		((TierDispatchFn)bfmeInstallCpuDispatchTable)(tier);
		return;
	}
	if (tier >= 5U)
	{
		*(int *)0x00E22CE0 = 0x00DB7628;
		*(int *)0x00E22CEC = 0x00DB7228;
		((TierDispatchFn)bfmeInstallCpuDispatchTable)(tier);
		return;
	}
	*(int *)0x00E22CE0 = 0x00DB7528;
	*(int *)0x00E22CEC = 0x00DB7128;
	((TierDispatchFn)bfmeInstallCpuDispatchTable)(tier);
}
