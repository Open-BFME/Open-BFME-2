// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// The native37B550 caller copies16B with four MOVSD instructions before
// pushing the type. BFME1 Recorder::writeArgument confirms a by-value
// GameMessageArgumentType, not four unrelated integer parameters.
// NativeAF05 remains131B, writing4/1/12/8/16/2B from that payload.
struct FILE;
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, FILE *stream);

union GameMessageArgumentType {int integer;char payload[16];};

class Rva0037AF05
{
public:
	void rva0037AF05(int type, GameMessageArgumentType arg);
private:
	char m_pad00[0x10];
	FILE *m_file10; // +0x10
};

void Rva0037AF05::rva0037AF05(int type, GameMessageArgumentType arg)
{
	if (type == 0) {
		fwrite(&arg, 4, 1, m_file10);
		return;
	}
	if (type == 1) {
		fwrite(&arg, 4, 1, m_file10);
		return;
	}
	if (type == 2) {
		fwrite(&arg, 1, 1, m_file10);
		return;
	}
	if (type == 3) {
		fwrite(&arg, 4, 1, m_file10);
		return;
	}
	if (type == 4) {
		fwrite(&arg, 4, 1, m_file10);
		return;
	}
	if (type == 5) {
		fwrite(&arg, 4, 1, m_file10);
		return;
	}
	if (type == 6) {
		fwrite(&arg, 12, 1, m_file10);
		return;
	}
	if (type == 7) {
		fwrite(&arg, 8, 1, m_file10);
		return;
	}
	if (type == 8) {
		fwrite(&arg, 16, 1, m_file10);
		return;
	}
	if (type == 9) {
		fwrite(&arg, 4, 1, m_file10);
		return;
	}
	if (type == 10) {
		fwrite(&arg, 2, 1, m_file10);
		return;
	}
}
