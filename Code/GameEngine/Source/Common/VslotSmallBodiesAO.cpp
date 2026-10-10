// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry whose
// shape needs /O1 /G7 (imul by a constant), batch AO. Classes and methods
// are address-derived and model only what each body touches.

typedef int Int;

// 0x0058AD9F (42 tables): five times the Int at VA 0x00DBA4E4.
extern Int g_Va00DBA4E4;
class Rva0058AD9F
{
public:
	Int rva0058AD9F();
};
Int Rva0058AD9F::rva0058AD9F()
{
	return g_Va00DBA4E4 * 5;
}


// Retail global spelled differently by the unit that defines it (same
// address in reverse/data_ledger.csv); bind this unit's name to it.
#pragma comment(linker, "/alternatename:?g_rva0058AD9FBase@@3HA=?g_Va00DBA4E4@@3HA")

// Installed-vtable modular word-difference zero test. Original owner and
// field meanings remain unknown. Only native data access and ABI are modeled.
struct Rva0056AA10Word {char prefix[0x1C]; unsigned int word;};
class Rva0056AA10 {public: int rva0056AA10(Rva0056AA10Word *value); private: char prefix[0x10]; unsigned int word;};
int Rva0056AA10::rva0056AA10(Rva0056AA10Word *value) {return (value->word-word) ? 0:1;}

// Installed-vtable modular word-difference zero test. Original owner and
// field meanings remain unknown. Only native data access and ABI are modeled.
struct Rva005E56B6Word {char prefix[0x20]; unsigned int word;};
class Rva005E56B6 {public: int rva005E56B6(Rva005E56B6Word *value); private: char prefix[0x8]; unsigned int word;};
int Rva005E56B6::rva005E56B6(Rva005E56B6Word *value) {return (value->word-word) ? 0:1;}

// Installed-vtable modular word-difference zero test. Original owner and
// field meanings remain unknown. Only native data access and ABI are modeled.
struct Rva005E56E7Word {char prefix[0x12C]; unsigned int word;};
class Rva005E56E7 {public: int rva005E56E7(Rva005E56E7Word *value); private: char prefix[0x8]; unsigned int word;};
int Rva005E56E7::rva005E56E7(Rva005E56E7Word *value) {return (value->word-word) ? 0:1;}
