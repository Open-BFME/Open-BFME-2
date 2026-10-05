// cl: /O1 /EHsc /MD
class Rva0015326DTarget { public: void apply(unsigned,void*); };
struct Rva001514B2Inner { unsigned words[2]; Rva0015326DTarget*target; };
struct Rva001514B2Outer { unsigned words[5]; Rva001514B2Inner*inner; };
class Rva001514B2 { public: Rva001514B2Outer*root; void*get(); void apply(unsigned,void*); };
void Rva001514B2::apply(unsigned n,void*p) {
 if(root && root->inner && root->inner->target) root->inner->target->apply(n,p);
}
class DX8Wrapper { public: static void Apply_Render_State_Changes(); };
class Rva00151D1A {
 unsigned head[2];
 Rva001514B2 handle;
 unsigned middle[5];
 void*extra;
 public: void apply(unsigned);
};

void Rva00151D1A::apply(unsigned n) {
 if(handle.root && handle.get() && extra) {
  DX8Wrapper::Apply_Render_State_Changes();
  handle.apply(n,extra);
  void*p=handle.get();
  typedef void(__stdcall*Slot104)(void*);
  ((Slot104*)(*(void***)p))[65](p);
 }
}

// Native 001514B2 ret8: guarded pointer walk at +0/+14/+8, then
// tail-forward both unchanged stack words to 0015326D. Original owner
// and argument semantic types remain unknown; names are address-derived.
// Native 00151D1A ret4: handle +8, extra word +20, matched getter twice,
// matched DX8 render-state application, then one-argument stdcall vtable
// dispatch at byte offset104. These offsets/ABIs come from native code.
#pragma comment(linker, "/alternatename:?get@Rva001514B2@@QAEPAXXZ=?rva0015148D@Rva0015148D@@QAEPAXXZ")
