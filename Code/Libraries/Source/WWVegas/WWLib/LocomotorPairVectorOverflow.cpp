// cl: /MD /DNDEBUG
// stlport
// Reference: STLport 4.5.3 vector::_M_insert_overflow (nontrivial element).
// Target: 0x004C77C4, 180B; 16-byte stride and calls to the pair destroy
// chain 0x004C7542/0x004C77A6 establish pair storage. Address-derived views
// retain uncertainty about the enclosing vector instantiation.
// The clear is the rowed Rva004C77A6::rva004C77A6.
class Rva004C77A6
{
public:
	void rva004C77A6();
};

struct Rva004C77C4Pair { char data[16]; };
struct Rva004C77C4Tag {};
// Retail borrows byte 3 of the four-byte final argument slot for the empty tag.
struct Rva004C77C4EndSlot { bool value; char padding[2]; Rva004C77C4Tag tag; };
Rva004C77C4Pair *Rva004C737ACopy(Rva004C77C4Pair *,Rva004C77C4Pair *,Rva004C77C4Pair *,const Rva004C77C4Tag &);
Rva004C77C4Pair *Rva004C73A0Fill(Rva004C77C4Pair *,unsigned int,const Rva004C77C4Pair &,const Rva004C77C4Tag &);
void Rva004C734DConstruct(Rva004C77C4Pair *,const Rva004C77C4Pair &);
struct Rva004C77C4Storage {
    Rva004C77C4Pair *end;
    Rva004C77C4Pair *allocate(unsigned int,const void *);
};
class Rva004C77C4 {
public:
    void overflow(Rva004C77C4Pair *,const Rva004C77C4Pair &,const Rva004C77C4Tag &,unsigned int,Rva004C77C4EndSlot);
    void clear();
private:
    Rva004C77C4Pair *start,*finish;
    Rva004C77C4Storage storage;
};
inline const unsigned int &Rva004C77C4Max(const unsigned int &left,const unsigned int &right) { return left<right?right:left; }
void Rva004C77C4::overflow(Rva004C77C4Pair *position,const Rva004C77C4Pair &value,const Rva004C77C4Tag &,unsigned int count,Rva004C77C4EndSlot at_end) {
    const unsigned int old_size=finish-start;
    const unsigned int length=old_size+Rva004C77C4Max(old_size,count);
    Rva004C77C4Pair *new_start=storage.allocate(length,0);
    Rva004C77C4Pair *new_finish=Rva004C737ACopy(start,position,new_start,at_end.tag);
    if (count==1) {
        Rva004C734DConstruct(new_finish,value);
        ++new_finish;
    } else new_finish=Rva004C73A0Fill(new_finish,count,value,at_end.tag);
    if (!at_end.value) new_finish=Rva004C737ACopy(position,finish,new_finish,at_end.tag);
    ((Rva004C77A6 *)this)->rva004C77A6();
    start=new_start;
    finish=new_finish;
    storage.end=new_start+length;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x004C73A0 reads ??$__uninitialized_fill_n@PAURva004C7878Record@@IU1@@_STL@@YAPAURva004C7878Record@@PAU1@IABU1@ABU__false_type@0@@Z
#pragma comment(linker, "/alternatename:?Rva004C73A0Fill@@YAPAURva004C77C4Pair@@PAU1@IABU1@ABURva004C77C4Tag@@@Z=??$__uninitialized_fill_n@PAURva004C7878Record@@IU1@@_STL@@YAPAURva004C7878Record@@PAU1@IABU1@ABU__false_type@0@@Z")
//   0x004C734D reads ??$_Construct@URva004C734DElement@@U1@@_STL@@YAXPAURva004C734DElement@@ABU1@@Z
#pragma comment(linker, "/alternatename:?Rva004C734DConstruct@@YAXPAURva004C77C4Pair@@ABU1@@Z=??$_Construct@URva004C734DElement@@U1@@_STL@@YAXPAURva004C734DElement@@ABU1@@Z")
//   0x004C737A reads ??$__uninitialized_copy@PAURva004C7878Record@@PAU1@@_STL@@YAPAURva004C7878Record@@PAU1@00ABU__false_type@0@@Z
#pragma comment(linker, "/alternatename:?Rva004C737ACopy@@YAPAURva004C77C4Pair@@PAU1@00ABURva004C77C4Tag@@@Z=??$__uninitialized_copy@PAURva004C7878Record@@PAU1@@_STL@@YAPAURva004C7878Record@@PAU1@00ABU__false_type@0@@Z")
//   0x002226BE reads ?allocate@?$allocator@UBfmeE16@@@_STL@@QBEPAUBfmeE16@@IPBX@Z
#pragma comment(linker, "/alternatename:?allocate@Rva004C77C4Storage@@QAEPAURva004C77C4Pair@@IPBX@Z=?allocate@?$allocator@UBfmeE16@@@_STL@@QBEPAUBfmeE16@@IPBX@Z")
