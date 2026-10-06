// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005C70DB@Rva005C70DB@@QAEMMPAMH0H0H0H@Z @0x005C70DB 210B: scalar interp switch 0 step 1 line 2 catm via Evaluate.
// Calls row ?Rva00503D8EEvaluate@@YAMMMMMM@Z then same quaternion-style time deltas as Rva005C7098.
float __cdecl Rva00503D8EEvaluate(float p0, float p1, float p2, float p3, float t);
class Rva005C70DB
{
public:
	float rva005C70DB(float t, float *pa, int ta, float *pc, int tc, float *pf, int tf, float *pd, int td);
	int m_key;
};
float Rva005C70DB::rva005C70DB(float t, float *pa, int ta, float *pc, int tc, float *pf, int tf, float *pd, int td)
{
	switch (m_key) {
	case 1:
		return (1.0f - t) * (*pc) + t * (*pf);
	case 2: {
		float d0 = (float)(tc - ta);
		float d1 = (float)(tf - tc);
		float d2 = (float)(td - tf);
		float v0;
		if (d0 > 0.0f)
			v0 = *pc + ((*pa - *pc) / d0) * d1;
		else
			v0 = *pa;
		float v1 = (d2 > 0.0f) ? (*pf + ((*pd - *pf) / d2) * d1) : *pd;
		return Rva00503D8EEvaluate(v0, *pc, *pf, v1, t);
	}
	default:
		return *pc;
	}
}
