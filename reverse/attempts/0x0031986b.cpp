// ?rva0031986B@Drawable@@QAEXPBURva0031986BPair@@H@Z
// partial score=0.94 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
#include <vector>
// Retail 0x0031986B, 77 bytes, RET8. Rowed Drawable::getWheelInfo
// establishes this owner and returns the +88 holder's +3C wheel record.
// Native begin/end subtraction uses 16-byte entries. The 41B update and
// 36B copy helpers take two words and one output pointer respectively.
// Rowed sibling 0x00319831 confirms the owner pair +3C, gate 0x003195C9,
// listener list +8 and callback 0x005CB26A (vcall slot4 forwarding thunk).
// Original method meaning and the second argument's meaning are unresolved.
struct Rva0031986BPair { float x, y; };
struct Rva0031986BEntry { char bytes[16]; };
struct TWheelInfo
{
 _STL::vector<Rva0031986BEntry> entries;
 void rva00538DC1(const Rva0031986BPair *pair, int word);
 bool rva00538D17(Rva0031986BPair *pair);
};
class Rva003197EEListener
{
public:
 virtual void notify(void *);
 void rva005CB26A(void *);
};
class Rva003197EEList
{
public:
 void forEach(void (Rva003197EEListener::*callback)(void *), void *arg);
};
class Rva003195C9Owner
{
public:
 void rva003195C9();
};
class Drawable
{
public:
 const TWheelInfo *getWheelInfo() const;
 void rva0031986B(const Rva0031986BPair *pair, int word);
private:
 char unknown00[0x3C];
 Rva0031986BPair currentPair;
};
void Drawable::rva0031986B(const Rva0031986BPair *pair, int word)
{
 TWheelInfo *info = const_cast<TWheelInfo *>(getWheelInfo());
 if (info != 0 && info->entries.size() != 0)
 {
  info->rva00538DC1(pair, word);
  info->rva00538D17(&currentPair);
  reinterpret_cast<Rva003195C9Owner *>(this)->rva003195C9();
  reinterpret_cast<Rva003197EEList *>(reinterpret_cast<char *>(this) + 8)->forEach(
   &Rva003197EEListener::rva005CB26A, this);
 }
}
