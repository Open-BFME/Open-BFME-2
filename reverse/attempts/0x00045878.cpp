// ?Rva0045878Count@@YAHXZ
// partial score=0.7 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD
#include <math.h>
#pragma function(fabs)

class RenderDeviceDescClass;
class WW3D
{
public:
	static const RenderDeviceDescClass &Get_Render_Device_Desc(int index);
};

int Rva0045878Count()
{
	const char *desc = (const char *)&WW3D::Get_Render_Device_Desc(0) + 0x5A0;
	int count = *(const int *)(desc + 0x10);
	void *base = *(void *const *)(desc + 4);
	int n = 0;
	for (int i = 0; i < count; i++)
	{
		const char *m = (const char *)base + i * 16;
		if (*(const int *)(m + 8) < 24)
			continue;
		if (*(const int *)m < 800)
			continue;
		if (fabs((double)*(const int *)m / *(const int *)(m + 4) - 1.3333f) < 0.01f)
			n++;
	}
	return n;
}
