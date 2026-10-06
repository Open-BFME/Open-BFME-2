// cl: /DNDEBUG /MD
//
// BFME2's GuiFX screen Apt callback "AptGuiFX::OnInitialized", a static
// callback bound by that name through the holder 0x0023E8D8 by the
// screen's registration 0x00380B0C; that binding is its only reference.
// The class is named for the string's prefix.

// The GuiFX movie's ready flag (0x00E022E0, beside the "GuiFX.apt" name at
// 0x00E022E8).
extern bool g_Va00E022E0;

class AptGuiFX
{
public:
	static void OnInitialized(const char *unused);
};

// Retail 0x003808E8, 8 bytes: "AptGuiFX::OnInitialized" marks the GuiFX
// movie ready.
void AptGuiFX::OnInitialized(const char *unused)
{
	g_Va00E022E0 = true;
}
