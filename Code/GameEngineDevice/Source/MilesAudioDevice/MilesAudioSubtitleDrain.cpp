// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Native5B708..5B96D RET0 /613B; BF1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// MilesAudioManagerRva006AF840::rva006AF840 is the primary clean donor.
// Target establishes mutex9D4, table9E8, Unicode pending9FC and filesA08,
// GameText fetch slot14, global option9A2, pair ctor54AFA/dtor543F5,
// and reserve/insert5A0EE. Their layout evidence is separate from donor purpose.
// The canonical StringBase header establishes data+4 length /data+8 text.
// Target inlines those reads here; neutral helpers preserve them without a
// private StringBase/UnicodeString definition. The 261-byte filename buffer
// supports the 260-character bound plus terminator; target allocates264 bytes.
// The original buffer declaration is unasserted (261..264 have that extent).
// The 8B temporary record owns the same two strings that the verified
// ctor54AFA and destructor543F5 handle; its destructor forwards that cleanup.
#include <stdlib.h>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class MilesMutexGuard {public:MilesMutexGuard(void *,int);~MilesMutexGuard();private:void *mutex;bool held;};
class MilesAudioManager {
public:
 void rva0005B708();void rva00051353(const UnicodeString &);
 char at00[0x9D4];void *m_mutex;
 char at9D8[0x9E8-0x9D8];char m_fileText[0x14];
 _STL::vector<UnicodeString> m_pendingFileText;
 _STL::vector<AsciiString> m_unknownFileNames;
};

class GameTextInterface {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();
 virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();
 virtual void slot12();virtual void slot13();virtual UnicodeString fetch(const AsciiString &,bool *);
};
extern GameTextInterface *TheGameText;
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct SubtitleGlobalView {char at00[0x9A2];bool m_at9A2;};

class Rva000543F5Record {public:~Rva000543F5Record();};
struct BfmeStringRecord00054F57 {void *m_a;void *m_b;};
class Rva00054AFA {
public:Rva00054AFA(const AsciiString &,const UnicodeString &);
 // ?Rva00054AFA::~Rva00054AFA present-unmatched
 ~Rva00054AFA(){reinterpret_cast<Rva000543F5Record *>(this)->~Rva000543F5Record();}
 // ?Rva00054AFA::operator record present-unmatched
 operator const BfmeStringRecord00054F57 &()const{return *reinterpret_cast<const BfmeStringRecord00054F57 *>(this);}
 char storage[8];
};
struct Pair00058D4A {void *m_node;void *m_table;bool m_new;};
class Rva00058D4A {public:Pair00058D4A *rva0005A0EE(Pair00058D4A *,const BfmeStringRecord00054F57 &);};
// Clean BF1 f989 rva006AF840 supplies primary subtitle-drain semantics;
// target5B708..5B96D supplies manager offsets, mutex wrapper, global flag9A2,
// canonical string ABI, GameText slot14 and independently owned map provider.
// ?subtitleFirstChar present-unmatched
__forceinline unsigned short subtitleFirstChar(const UnicodeString &text) {
 const char *data=*reinterpret_cast<const char *const *>(&text);
 return data?*reinterpret_cast<const unsigned short *>(data+8):0;
}
// ?subtitleIsEmpty present-unmatched
__forceinline bool subtitleIsEmpty(const UnicodeString &text) {
 const char *data=*reinterpret_cast<const char *const *>(&text);
 return !data||!*reinterpret_cast<const unsigned short *>(data+4);
}
void MilesAudioManager::rva0005B708()
{
 MilesMutexGuard guard(&m_mutex,0);
 for(_STL::vector<UnicodeString>::iterator text=m_pendingFileText.begin();text!=m_pendingFileText.end();++text)rva00051353(*text);
 m_pendingFileText.clear();
 for(_STL::vector<AsciiString>::iterator file=m_unknownFileNames.begin();file!=m_unknownFileNames.end();++file) {
  AsciiString fileName(*file);
  if(fileName.getLength()>260) {AsciiString truncated(fileName,0,260);reinterpret_cast<StringBase<char> *>(&fileName)->swap(*reinterpret_cast<StringBase<char> *>(&truncated));}
  char fileBase[261];
  _splitpath(fileName.str(),0,0,fileBase,0);
  AsciiString label("DIALOGEVENT:");label.concat(fileBase);label.concat("SubTitle");
  bool exists=false;
  UnicodeString subtitle=TheGameText==0?UnicodeString::TheEmptyString:TheGameText->fetch(label,&exists);
  if(!exists)subtitle.clear();
  else if(subtitleFirstChar(subtitle)=='*') {
   if(reinterpret_cast<SubtitleGlobalView *>(TheWritableGlobalData)->m_at9A2) {UnicodeString unmarked(subtitle,1,subtitle.getLength()-1);subtitle.swap(unmarked);}
   else subtitle.clear();
  }
  Pair00058D4A result;
  reinterpret_cast<Rva00058D4A *>(&m_fileText)->rva0005A0EE(&result,Rva00054AFA(*file,subtitle));
  if(!subtitleIsEmpty(subtitle))rva00051353(subtitle);
 }
 m_unknownFileNames.clear();
}
