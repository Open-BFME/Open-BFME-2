// cl: /O1 /G7 /arch:SSE /MD /EHs-c-
// Native 0x0052B497..0x0052B4B6,31B; slot0 of primary vtable0x00C68620
// reaches its deleting wrapper0x0052B56C. Primary base dtor calls0x0060D0B3,
// whose existing provider is donor-named XferSave; original derived name unknown.
// The pointer at+54 is scalar-deleted before the native tail jump into base.
// Base storage extent0x40 follows its matched destructor view; gap40..54 opaque.
void __cdecl operator delete(void *) throw();
class XferSave {
public: virtual ~XferSave() throw();
private: char storage[0x40-4];
};
class Rva0052B497 : public XferSave {
public: virtual ~Rva0052B497();
private: char opaque40[0x54-0x40];void *buffer;
};
Rva0052B497::~Rva0052B497()
{
 if(buffer) ::operator delete(buffer);
}
