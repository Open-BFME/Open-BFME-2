// cl: /O1 /MD /EHsc
// Target boundary and destructor purpose established independently from
// the native EH cleanup and deleting wrapper604572/vtableC7A94C slot0.
// Prefix views call already verified7B/56B providers; no donor payload name
// or full class size is asserted.
// Native604465..6044A0 destructor: derived vptr C7A94C tree cleanup at+4
// through rowed56B604396 then base reset7B60263E. Class identity remains
// opaque; wrapper604572 already rowed as scalar deleting dtor of this view.
class Rva0060263EBase { public:virtual ~Rva0060263EBase(); };
class Rva00604396TreeView { char unknown[12];public:~Rva00604396TreeView(); };
class Rva00604465:public Rva0060263EBase {
public:virtual ~Rva00604465();
private:Rva00604396TreeView m_tree;
};
Rva00604465::~Rva00604465() {}

#pragma comment(linker, "/alternatename:??1Rva0060263EBase@@UAE@XZ=?apply@Rva00060263EDwordImmSetter@@QAEXXZ")

#pragma comment(linker, "/alternatename:??1Rva00604396TreeView@@QAE@XZ=??1?$_Rb_tree@$$CBV?$BitFlags@$0BB@@@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@U?$_Select1st@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@3@UMapHelper@?$SparseMatchFinder@VWeaponTemplateSet@@V?$BitFlags@$0BB@@@@@V?$allocator@U?$pair@$$CBV?$BitFlags@$0BB@@@PBVWeaponTemplateSet@@@_STL@@@3@@_STL@@QAE@XZ")
