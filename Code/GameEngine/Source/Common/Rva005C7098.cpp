// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005C7098@Rva005C7098@@QAEPAVQuaternion@@PAV2@MHHPBV2@H1HHH@Z, retail 0x005C7098 67B.
// Quaternion interpolator: if m_key is 1 LINE or 2 CATM Slerp tmp from src1
// src2 with t then copy tmp to dst else copy src1 to dst. Evidence: int at +0
// 0 STEP 1 LINE 2 CATM like Rva005C706AWrite; Slerp row
// ?Slerp@@YAXAAVQuaternion@@ABV1@1M@Z; 10 stack args ret 0x28; caller 0x0053FED5.
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
};

void __cdecl Slerp(Quaternion &result, const Quaternion &a, const Quaternion &b, float t);

class Rva005C7098
{
public:
	Quaternion *rva005C7098(Quaternion *dst, float t, int a3, int a4, const Quaternion *src1, int a6, const Quaternion *src2, int a8, int a9, int a10);
	int m_key;
};

Quaternion *Rva005C7098::rva005C7098(Quaternion *dst, float t, int a3, int a4, const Quaternion *src1, int a6, const Quaternion *src2, int a8, int a9, int a10)
{
	Quaternion tmp;
	const Quaternion *src;
	if (m_key > 0 && m_key <= 2)
	{
		Slerp(tmp, *src1, *src2, t);
		src = &tmp;
	}
	else
	{
		src = src1;
	}
	*dst = *src;
	return dst;
}
