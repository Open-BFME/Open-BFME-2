// cl: /DNDEBUG /MD
// ?Rva000B2BFFClamp@@YAXPAMM@Z @0x000B2BFF 190B, call sites 0x000B4DFF and
// 0x000B7227 (in the functions at 0x000B4CE2 and 0x000B710D). Steps the angle
// at p toward v by 0.1 (the long way round when the gap exceeds pi), snaps
// when within one step, then wraps the result into [-pi, pi].
// Target evidence: free cdecl, SSE compares; the pooled float constants 0.1
// at 0x00BC2424, pi at 0x00BC7468 and 2pi at 0x00BC746C/0x00BC7470 are
// compiler literals here (the banked attempt read them through globals).

void __cdecl Rva000B2BFFClamp(float *p, float v)
{
	if (*p > v)
	{
		float diff = *p - v;
		if (diff > 3.1415927410125732f)
		{
			*p += 0.1f;
		}
		else if (diff > 0.1f)
		{
			*p -= 0.1f;
		}
		else
		{
			*p = v;
		}
	}
	else if (v > *p)
	{
		float diff = v - *p;
		if (diff > 3.1415927410125732f)
		{
			*p -= 0.1f;
		}
		else if (diff > 0.1f)
		{
			*p += 0.1f;
		}
		else
		{
			*p = v;
		}
	}
	if (*p > 3.1415927410125732f)
	{
		*p -= 6.2831854820251465f;
	}
	if (-3.1415927410125732f > *p)
	{
		*p += 6.2831854820251465f;
	}
}
