// cl: /DNDEBUG /MD /Oi-
#include <math.h>
#pragma function(fabs)

class RenderDeviceDescClass;
class WW3D
{
public:
	static const RenderDeviceDescClass &Get_Render_Device_Desc(int index);
};

struct Rva0045878Mode
{
	int m_width;
	int m_height;
	int m_bits;
	int m_pad;
};

int Rva0045878Count()
{
	int i = 0;
	const char *desc = (const char *)&WW3D::Get_Render_Device_Desc(i) + 0x5A0;
	int n = 0;
	for (; i < *(const int *)(desc + 0x10); i++)
	{
		if ((*(Rva0045878Mode *const *)(desc + 4))[i].m_bits < 24)
			continue;
		if ((*(Rva0045878Mode *const *)(desc + 4))[i].m_width < 800)
			continue;
		if (fabs((float)(*(Rva0045878Mode *const *)(desc + 4))[i].m_width / (*(Rva0045878Mode *const *)(desc + 4))[i].m_height - 1.3333f) < 0.01f)
			n++;
	}
	return n;
}

void __stdcall Rva00458E2Get(int index, int *w, int *h, int *bits)
{
	int i;
	int found = 0;
	const char *desc = (const char *)&WW3D::Get_Render_Device_Desc(0) + 0x5A0;
	for (i = 0; i < *(const int *)(desc + 0x10); i++)
	{
		if ((*(Rva0045878Mode *const *)(desc + 4))[i].m_bits < 24)
			continue;
		if ((*(Rva0045878Mode *const *)(desc + 4))[i].m_width < 800)
			continue;
		if (fabs((float)(*(Rva0045878Mode *const *)(desc + 4))[i].m_width / (*(Rva0045878Mode *const *)(desc + 4))[i].m_height - 1.3333f) < 0.01f)
		{
			if (found == index)
			{
				*w = (*(Rva0045878Mode *const *)(desc + 4))[i].m_width;
				*h = (*(Rva0045878Mode *const *)(desc + 4))[i].m_height;
				*bits = (*(Rva0045878Mode *const *)(desc + 4))[i].m_bits;
				return;
			}
			found++;
		}
	}
}
