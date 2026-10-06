// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037AF05@Rva0037AF05@@QAEXHHHHH@Z @0x0037AF05 131B: recorder message arg writer via fwrite sizes 4 1 12 8 16 2. Evidence: FILE at +0x10 plus IAT fwrite plus same sizes as Rva0037AF88Read plus ret 0x14 five dwords; same FILE+0x10 family as Rva0037ADB6Write and Rva0037AF88Read; caller 0x0037B567.
struct FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, FILE *stream);

class Rva0037AF05
{
public:
	void rva0037AF05(int type, int p1, int p2, int p3, int p4);
private:
	char m_pad00[0x10];
	FILE *m_file10; // +0x10
};

void Rva0037AF05::rva0037AF05(int type, int p1, int p2, int p3, int p4)
{
	if (type == 0) {
		fwrite(&p1, 4, 1, m_file10);
		return;
	}
	if (type == 1) {
		fwrite(&p1, 4, 1, m_file10);
		return;
	}
	if (type == 2) {
		fwrite(&p1, 1, 1, m_file10);
		return;
	}
	if (type == 3) {
		fwrite(&p1, 4, 1, m_file10);
		return;
	}
	if (type == 4) {
		fwrite(&p1, 4, 1, m_file10);
		return;
	}
	if (type == 5) {
		fwrite(&p1, 4, 1, m_file10);
		return;
	}
	if (type == 6) {
		fwrite(&p1, 12, 1, m_file10);
		return;
	}
	if (type == 7) {
		fwrite(&p1, 8, 1, m_file10);
		return;
	}
	if (type == 8) {
		fwrite(&p1, 16, 1, m_file10);
		return;
	}
	if (type == 9) {
		fwrite(&p1, 4, 1, m_file10);
		return;
	}
	if (type == 10) {
		fwrite(&p1, 2, 1, m_file10);
		return;
	}
}
