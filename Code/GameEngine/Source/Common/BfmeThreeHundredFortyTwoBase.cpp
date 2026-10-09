// cl: /O1 /G7 /arch:SSE /MD
// Native17B31454D is the C0BBF8 input-route base constructor: it clears
// next/owner at4/8 and installs the same table as the verified link/unlink
// and destructor in GameWindow.cpp. AptLanLobby445EE3 constructs this base
// at6AC before installing its derived route table. Replaces the earlier
// BfmeThingTC::bfmeBaseTC placeholder without changing the17 native bytes.
// This is a consumed12-byte prefix; the target owner argument to Link is
// a different receiver view and its1DC list head is not part of this object.
class Rva0031455E {
public:
 Rva0031455E();
 virtual ~Rva0031455E();
 virtual void Rva0031455ELink(Rva0031455E *);
 virtual void Rva00314581Unlink();
private: void *next; void *window;
};
Rva0031455E::Rva0031455E() : next(0),window(0) {}
