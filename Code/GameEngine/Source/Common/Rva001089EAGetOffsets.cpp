// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva001089EA@Rva001089EA@@QAEXHPAM0@Z at 0x001089EA (33B). Address-derived method name; retail indexes pointers at this+0x58 and copies entry floats at +0x6C/+0x70 to caller outputs.
struct Rva001089EAEntry
{
	char pad00[0x6c];
	float x;
	float y;
};

class Rva001089EA
{
public:
	void rva001089EA(int index, float *x, float *y);

private:
	char pad00[0x58];
	Rva001089EAEntry *m_entries[1];
};

void Rva001089EA::rva001089EA(int index, float *x, float *y)
{
	Rva001089EAEntry *entry = m_entries[index];
	if (entry)
	{
		*x = entry->x;
		*y = entry->y;
	}
}
