// cl: /O1 /MD
// Native6016C9..60173A is the113B once-only character-class initialization.
// Parser601C53 and WB1646870 TextFile::ParseFile establish the table's role;
// original global spellings are unknown. The target reads256 DWORD entries
// atVA E06A50 and a one-byte guard atE06E50. Both initial storage extents
// are zero in retail; explicit data rows own them. Preserve target's256-byte
// clear, followed by isspace classification and its five explicit entries.
// This recovers the existing address-derived initializer, not a donor name.
extern "C" void *__cdecl memset(void *,int,unsigned);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
int TextFileCharacterClasses[256];
bool TextFileCharacterClassesInitialized;
void Rva006016C9Init() {
 if(TextFileCharacterClassesInitialized)return;
 TextFileCharacterClassesInitialized=true;
 memset(TextFileCharacterClasses,0,256);
 for(int i=0;i<256;++i)if(isspace(i))TextFileCharacterClasses[i]=2;
 TextFileCharacterClasses[0]=1;
 TextFileCharacterClasses['\n']=1;
 TextFileCharacterClasses['\r']=1;
 TextFileCharacterClasses[';']=3;
 TextFileCharacterClasses['/']=4;
}
