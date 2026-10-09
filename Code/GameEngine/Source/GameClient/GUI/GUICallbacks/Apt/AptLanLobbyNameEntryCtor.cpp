// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0AptLanLobbyNameEntry@@QAE@XZ @0x00444055 (18B). Out-of-line default constructor of the LAN
// lobby name entry (vtable ??_7AptLanLobbyNameEntry 0x00C3DFA8, class view in
// AptLanLobbyDestructor.cpp where the constructor is inlined): rowed input-route base
// constructor ??0Rva0031455E 0x0031454D (BfmeThreeHundredFortyTwoBase.cpp), then the derived
// vtable; no member initialisation. Same shape as Rva00135E35Ctor.cpp.
class Rva0031455E
{
public:
	Rva0031455E();
	virtual ~Rva0031455E();
};

class AptLanLobbyNameEntry : public Rva0031455E
{
public:
	AptLanLobbyNameEntry();
};

AptLanLobbyNameEntry::AptLanLobbyNameEntry()
{
}
