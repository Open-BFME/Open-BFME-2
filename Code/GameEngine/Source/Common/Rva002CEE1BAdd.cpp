// cl: /MD
// ?rva002CED84@Rva002CEE1B@@QAEXPAX00@Z @0x002CED84 83B
// Method of Rva002CEE1B (array at +0x0C, 128 x 0x1C from dtor TU) that finds
// first empty slot and fills {ptr + 12B + 12B}. Evidence: ecx+0x0C base with
// 0x80 x 0x1C search matches Rva002CEE1BDtor layout; caller at 0x0004C878
// passes (void* from 0x002CF21B, two 12B float vectors) with ecx=global.
struct Twelve002CED84
{
	int v0, v1, v2;
};

struct Elem002CED84
{
	void *ptr;
	Twelve002CED84 second;
	Twelve002CED84 third;
};

class GameEngineDeletingBase002CED84
{
public:
	virtual ~GameEngineDeletingBase002CED84();
};

class Rva002CEE1B : public GameEngineDeletingBase002CED84
{
public:
	void rva002CED84(void *p1, void *p2, void *p3);
	Elem002CED84 *rva002CED59(void *key);

private:
	char m_pad04[0x0C - 4];
	Elem002CED84 m_arr0C[128];
};

void Rva002CEE1B::rva002CED84(void *p1, void *p2, void *p3)
{
	if (p1 == 0)
		return;
	if (p2 == 0)
		return;
	if (p3 == 0)
		return;
	int i = 0;
check:
	if (m_arr0C[i].ptr == 0)
		goto fill;
	i++;
	if (i < 128)
		goto check;
	return;
fill:
	Elem002CED84 *slot = &m_arr0C[i];
	if (slot == 0)
		return;
	slot->ptr = p1;
	slot->second = *(Twelve002CED84 *)p2;
	slot->third = *(Twelve002CED84 *)p3;
}

// 0x002CED59 43B: find-by-key twin of the empty-slot search inlined in
// rva002CED84 above: scan the same 128 x 0x1C array at +0x0C for the first
// entry whose ptr equals key, returning its address, or NULL. Called twice
// from inside rva002CED84 past the row end, which with the identical base
// and constants proves the Rva002CEE1B thiscall class.
Elem002CED84 *Rva002CEE1B::rva002CED59(void *key)
{
	Elem002CED84 *result = 0;
	int i = 0;
check:
	if (m_arr0C[i].ptr == key)
	{
		result = &m_arr0C[i];
		goto done;
	}
	i++;
	if (i < 128)
		goto check;
done:
	return result;
}
