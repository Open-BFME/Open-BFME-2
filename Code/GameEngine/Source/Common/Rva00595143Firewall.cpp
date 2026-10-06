// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?Rva00595143Get@@YAPAVFirewallHelperClass@@XZ @0x00595143 25B: allocate 0x190 via rowed new then rowed FirewallHelperClass ctor. Evidence: push 0x190 calls row 0x0002FDA0 ??2@YAPAXI@Z and row 0x00594CDD ??0FirewallHelperClass@@QAE@XZ; caller 0x005A7330 stores result to global.
void *__cdecl operator new(unsigned int size) throw();

class FirewallHelperClass
{
public:
	FirewallHelperClass() throw();
private:
	char m_pad[0x190];
};

FirewallHelperClass * __cdecl Rva00595143Get(void)
{
	return new FirewallHelperClass;
}
