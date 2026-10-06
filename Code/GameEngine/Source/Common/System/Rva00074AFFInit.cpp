// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?Rva00074AFFGet@@YGPAVRva000748F6@@H@Z, retail 0x00074AFF, 60 bytes.
// Static initializer: first-call construct of global Rva000748F6, returns its address.
// Evidence: chain lane, calls just-landed ??0Rva000748F6@@QAE@XZ, guard/object are relocs.
class Rva000748F6
{
public:
	Rva000748F6();
	char m_data[0x34];
};

Rva000748F6 *__stdcall Rva00074AFFGet(int dummy)
{
	static Rva000748F6 s;
	return &s;
}
