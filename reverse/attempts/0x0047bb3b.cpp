// ?rva0047BB3B@Rva0047BB3BOwner@@QAEXPAVObject@@@Z
// partial score=0.85 date=2026-10-08
// cl: /MD /EHsc
// ?rva0047BB3B@Rva0047BB3BOwner@@QAEXPAVObject@@@Z @0x0047BB3B 48B: thiscall, one pointer argument, ret 4.
// Null-guarded: when the argument's flag byte at +0x126 has bit 1, clear it and run the
// matched Object notifier 0x0028AE6D; then hand the argument to the owner's address-named
// member at 0x00467AB8 (pinned in symbols.csv). Names are address-derived views only.
class Object
{
public:
	void rva0028AE6D();
private:
	char pad00[0x126];
public:
	unsigned char m_126;
};

class Rva0047BB3BOwner
{
public:
	void rva0047BB3B(Object *obj);
	void rva00467AB8(Object *obj);
};

void Rva0047BB3BOwner::rva0047BB3B(Object *obj)
{
	if (obj) {
		if (obj->m_126 & 2) {
			obj->m_126 = obj->m_126 & 0xfd;
			obj->rva0028AE6D();
		}
		rva00467AB8(obj);
	}
}
