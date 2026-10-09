// ?notify@Rva0020AA00Target@@QAEXHH@Z
// partial score=0.894547 date=2026-10-09
// stlport
// cl: /O1 /Oy- /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// Native284B33C965/WBbcc090 build four ModuleInfo lists, append base90
// plus retail literal .tga, walk six handles in each368B record, and load
// CommandSet assets by name70 when GlobalData1110 permits. Actual receiver
// is ThingTemplate by its named GetAssetList caller; original helper name
// remains unknown. Existing HH arguments carry opaque32-bit ABI values.
// Concat node layout and empty text-pair ctor come from verified RegistryAsciiPath;
// its real non-POD structure eliminates the bank's extra12B MOVS copy and
// restores this/argument register allocation. Canonical AsciiString cleanup
// and explicit StringBase isEmpty ABI view preserve genuine target lifetime.
// Both globals use existing canonical names; no pins/address globals added.
 #include <vector>
#include <set>
template<class T> struct StringInlineData {int m_refCount,m_length;T m_text[1];};
#include "ascii_string.h"
struct AsciiStringRef { const AsciiString *m_string; };
class Rva000B3F84Pair { public: Rva000B3F84Pair() {} const char *m_ptr;int m_len; };
struct AsciiStringPlusText : AsciiStringRef { operator AsciiString();Rva000B3F84Pair m_right; };

AsciiStringPlusText operator+(const AsciiString &left, const char *right);

struct AssetList00208F90
{
public:
	AssetList00208F90 &operator<<(const AsciiString &s);
};

class ModuleInfo
{
public:
	char m_data[12];
};

enum ModuleType
{
	MODULE_0,
	MODULE_1,
	MODULE_2,
	MODULE_3
};

void Rva0033B5B8Build(ModuleInfo *info, ModuleType type, int a1, int a2);

class Rva002CA9CA
{
public:
	void rva002CAC6E(int a1, int a2);
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);
};

class CommandSet
{
public:
	void rva00409F1B(int a1, int a2);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
class ControlBar;
extern ControlBar *TheControlBar;

struct Rva0033C965Rec
{
	char m_pad[0x14];
	Rva002CA9CA *m_slots[6];
	char m_tail[0x368 - 0x14 - 24];
};

class Rva0033C965
{
public:
	void rva0033C965(int a1, int val);

private:
	char m_pad00[0x70];
	AsciiString m_name70; // +0x70
	char m_pad74[0x90 - 0x74];
	AsciiString m_base90; // +0x90
	char m_pad94[0x2e4 - 0x94];
	ModuleInfo m_mod0; // +0x2e4
	ModuleInfo m_mod1; // +0x2f0
	ModuleInfo m_mod2; // +0x2fc
	ModuleInfo m_mod3; // +0x308
	char m_pad310[0x358 - 0x314];
	Rva0033C965Rec *m_recs; // +0x358
	Rva0033C965Rec *m_recsEnd; // +0x35c
};

void Rva0033C965::rva0033C965(int a1, int val)
{
	Rva0033B5B8Build(&m_mod0, MODULE_0, a1, val);
	Rva0033B5B8Build(&m_mod1, MODULE_1, a1, val);
	Rva0033B5B8Build(&m_mod2, MODULE_2, a1, val);
	Rva0033B5B8Build(&m_mod3, MODULE_3, a1, val);

	AsciiString &baseName = m_base90;
	if (!((const StringBase<char> *)&baseName)->isEmpty()) {
		*(AssetList00208F90 *)a1 << (baseName + ".tga");
	}

	for (Rva0033C965Rec *rec = m_recs; rec != m_recsEnd; rec++) {
		Rva002CA9CA **slot = rec->m_slots;
		int left = 6;
		do {
			if (*slot)
				(*slot)->rva002CAC6E(a1, val);
			slot++;
		} while (--left != 0);
	}

	if (*(char *)((char *)TheWritableGlobalData + 0x1110) == 0) {
		void *hit = ((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(&m_name70);
		if (hit != 0)
			((CommandSet *)hit)->rva00409F1B(a1, val);
	}
}

struct Rva001408C0Target;
class AssetList { public:
 AssetList &operator<<(const AssetList &);
 bool empty() const {return prototypes.empty();}
 _STL::set<Rva001408C0Target *,_STL::less<Rva001408C0Target *>,_STL::allocator<Rva001408C0Target *> > prototypes;
 unsigned pad;bool changed;
};
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva0020AA00Target { public:
 void notify(int,int);
 char prefix[0x330];_STL::vector<AsciiString> names;
 char pad33c[0x3c4-0x33c];AssetList cached[2];
};
void Rva0020AA00Target::notify(int a,volatile int b) {
 const bool *flag=reinterpret_cast<const bool *>(b);
 int mode=*flag!=0;
 if(!cached[mode].empty()) { *reinterpret_cast<AssetList *>(a)<<cached[mode];return; }
 const _STL::vector<AsciiString> &keys=names;
 if(!keys.empty()) {
  b=reinterpret_cast<int>(keys.begin());
  do {
   Rva0033C965 *source=static_cast<Rva0033C965 *>(reinterpret_cast<Rva002D06CA *>(TheThingFactory)->rva002D06CA(reinterpret_cast<AsciiString *>(b)));
   if(source) source->rva0033C965(reinterpret_cast<int>(&cached[mode]),reinterpret_cast<int>(flag));
   b+=sizeof(AsciiString);
  }while(b!=reinterpret_cast<int>(keys.end()));
 }else reinterpret_cast<Rva0033C965 *>(this)->rva0033C965(reinterpret_cast<int>(&cached[mode]),reinterpret_cast<int>(flag));
 *reinterpret_cast<AssetList *>(a)<<cached[mode];
}
