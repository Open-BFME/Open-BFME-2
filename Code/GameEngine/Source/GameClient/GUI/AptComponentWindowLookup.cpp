// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native4110C3..4110DC complete25B RET0; next owned54B lookup4110DC.
// The same existing61B string-key find as the adjacent411112 lookup is
// followed by ADDRESS node+8 (411112 instead loads a pointer there).
// Caller411EC3 independently consumes the returned component record's
// path+C/window10/coordinates14..20/drawn24/initName28.
// The target table at RVA00A02FE4 has a proven20-byte header and is
// initially zero in the image; constructor7AFF30 and the existing find
// establish its footprint. Store all20 bytes under one semantic symbol,
// preserving the legacy unowned views in the data ledger as evidence.
// O1/G7 plus explicit returns selects the native PUSH memory and branch;
// ternary form generates branchless NEG/SBB/AND and is not retail.
class AsciiString;
class Rva00056F61 {public:void*rva00056F61(const AsciiString*);};
unsigned int AptComponentWindowDataTableStorage[5];
void* Rva004110C3Get(const AsciiString*key) {
 void*node=reinterpret_cast<Rva00056F61*>(AptComponentWindowDataTableStorage)->rva00056F61(key);
 if(node)return(char*)node+8;return 0;
}
