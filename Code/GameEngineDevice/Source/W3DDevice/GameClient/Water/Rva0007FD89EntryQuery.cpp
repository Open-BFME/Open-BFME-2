// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native0007FD89..0007FE1B RET4. Receiver vector108/10C and entry owner40
// are measured; original receiver and predicate names are unresolved.
// Existing ReflectionTexture callback80168 independently binds globals
// TheWritableGlobalData+5E and TheRva00DFF488Setting final override+50.
// Reuse the existing native14B Rva001E35DFView getter without a new name.
// Callee308DF0 uses ECX and RET0, returning owned pointer84 in EAX.
// Callee7FB85 uses ECX and arg8, returns AL, RET4 after polygon clipping.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataGate {char unknown00[0x5e];bool enabled;};
class Rva001E35DFView {
public:
 const Rva001E35DFView *getFinalOverride() const {
  if(next)return next->getFinalOverride();
  return this;
 }
 void *unknown00;Rva001E35DFView *next;bool isOverride;
};
class Rva00DFF488Setting : public Rva001E35DFView {
public:char unknown0C[0x44];bool flag50;
};
template<class T> class OVERRIDE {
public:
 operator const T *() const {if(!pointer)return 0;return (const T *)pointer->getFinalOverride();}
 const T *operator->() const {if(!pointer)return 0;return (const T *)pointer->getFinalOverride();}
 const T *pointer;
};
extern OVERRIDE<Rva00DFF488Setting> TheRva00DFF488Setting;
struct Rva00308DF0Result {char unknown00[0x1c];int kind;};
class Rva00308DF0Owner {public:Rva00308DF0Result *rva00308DF0();};
class Rva0007FD89Entry {
public:char unknown00[0x40];Rva00308DF0Owner *owner;
 bool rva0007FB85(void *input);
};
class Rva0007FD89 {
public: bool rva0007FD89(void *input);
private:char unknown00[0x108];Rva0007FD89Entry **first,**last,**capacity;
};
bool Rva0007FD89::rva0007FD89(void *input)
{
 if(!input)return false;
 if(reinterpret_cast<GlobalDataGate *>(TheWritableGlobalData)->enabled && TheRva00DFF488Setting && TheRva00DFF488Setting->flag50) {
  for(Rva0007FD89Entry **it=first;it!=last;++it) {
   Rva0007FD89Entry *entry=*it;
   Rva00308DF0Result *data=entry->owner->rva00308DF0();
   if(data && data->kind>=2 && entry->rva0007FB85(input))return true;
  }
 }
 return false;
}
