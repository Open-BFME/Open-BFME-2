// cl: /O1 /arch:SSE /G7 /MD
// ?rva00531FD4@Rva002E99F9Sub460@@QAEGPAXG@Z, RVA 0x00531FD4, 18B.
// Identity is pinned and confirmed by both calls in Pathfinder::FindBrokenBridge
// at 0x002E9A8E and 0x002E9A9D. Retail forwards the second argument to the
// nested Rva00531A44 accessor at subobject offset 0x1B9F4.
class Rva00531A44
{
public:
	unsigned short rva00531B20(unsigned short value);
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva00531FD4(void *state, unsigned short value);

private:
	char m_pad[0x1B9F4];
	Rva00531A44 m_nested;
};

unsigned short Rva002E99F9Sub460::rva00531FD4(void *, unsigned short value)
{
	return m_nested.rva00531B20(value);
}
