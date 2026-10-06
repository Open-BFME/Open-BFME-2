// ?rva00118CC0@Render2DRawArray@@QAEPAXH@Z
// partial score=0.97 date=2026-10-04
// cl: /DNDEBUG /MD /EHsc
// ?rva00118CC0@Render2DRawArray@@QAEPAXH@Z 0x00118CC0 121 unlock
// Render2DRawArray grow of 44-byte elements via realloc caller 0x0011BD80
extern "C" __declspec(dllimport) void *__cdecl realloc(void *ptr, unsigned int size);

struct Raw44
{
	int v[11];
};

class Render2DRawArray
{
public:
	void *rva00118CC0(int count);
	Raw44 *Data;
	unsigned int Size;
	unsigned int Count;
	int GrowthStep;
};

void *Render2DRawArray::rva00118CC0(int count)
{
	if (count == 0 || (unsigned int)count >= 0x80000000u)
		return 0;
	Count += count;
	if (Count <= Size)
	{
		Raw44 *data = Data;
		unsigned int old = Count - (unsigned int)count;
		return &data[old];
	}
	Size = Count + (unsigned int)GrowthStep;
	void *newData = realloc(Data, Size * sizeof(Raw44));
	Data = (Raw44 *)newData;
	if (!newData)
		return 0;
	unsigned int old = Count - (unsigned int)count;
	return &Data[old];
}