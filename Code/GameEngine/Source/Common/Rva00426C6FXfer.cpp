// cl: /O1 /MD /EHs-c-
// Target 426C6F: CRC early-out, two-byte version, presence boolean,
// load-only 16-byte objective list allocation, and virtual snapshot transfer.
// The receiver's original class name is open; the neighbouring getter says
// MapMissionObjectives and the parsed object's error says MissionObjectiveList.
class Rva00426C4D { public: Rva00426C4D(); virtual void *v0(int); char storage[12]; };
struct Rva00426C6FVersion { unsigned char current, maximum; Rva00426C6FVersion() : current(1), maximum(1) {} };
struct Rva00426C6FXfer {
 virtual void v0(); virtual bool IsLoading() const; virtual void v2(); virtual bool IsCRC() const;
 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
 virtual void version(Rva00426C6FVersion &);
 virtual void v11(); virtual void snapshot(Rva00426C4D *);
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void boolean(bool &);
};
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *);
class Rva00426C6F { public: void xfer(Rva00426C6FXfer *); void *vtable; Rva00426C4D *object; };
void Rva00426C6F::xfer(Rva00426C6FXfer *x)
{
 if (x->IsCRC()) return;
 Rva00426C6FVersion version;
 x->version(version);
 bool present = object != 0;
 x->boolean(present);
 if (present) {
  if (x->IsLoading()) {
   void *old = object ? object->v0(0) : 0;
   ::operator delete(old);
   object = new Rva00426C4D;
  }
  x->snapshot(object);
 } else if (x->IsLoading()) object = 0;
}
