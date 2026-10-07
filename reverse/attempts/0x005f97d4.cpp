// ??1Gen_uwm_005f97d4@@QAE@XZ
// partial score=1.0 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD
// Native5F97D4..5F9813 RET0; storage/record identity remains unknown.
struct BfmeContainerRecord005FDEC7;
void free(void *pointer);
namespace _STL { template<class Pointer> void _Destroy(Pointer begin, Pointer end); }
struct Gen_uwm_005f97d4Storage {
 BfmeContainerRecord005FDEC7 *begin, *end, *limit;
 // ?Gen_uwm_005f97d4Storage::~Gen_uwm_005f97d4Storage absent-from-retail
 __forceinline ~Gen_uwm_005f97d4Storage() { if (begin) free(begin); }
};
class Gen_uwm_005f97d4 : private Gen_uwm_005f97d4Storage {
public: ~Gen_uwm_005f97d4();
};
Gen_uwm_005f97d4::~Gen_uwm_005f97d4() { _STL::_Destroy(begin, end); }
class Rva0052413E { public: ~Rva0052413E(); private: char bytes[12]; };
