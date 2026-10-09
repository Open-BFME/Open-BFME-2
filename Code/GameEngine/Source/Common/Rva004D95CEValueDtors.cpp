// cl: /O1 /G7 /MD /EHsc
// Native4D95CE destroys two independently counted 8-byte values in reverse
// member order. The upper native4D960C destroys that pair at+4 then its own
// reference at+0. Deleting wrapper4D96E4 and tree payload4D9B4B confirm dtor
// identity. Original aggregate types unknown; no donor labels inferred.
class OpaqueRefCounted { public: void Release_Ref(); };
class Rva002390CB {
    void *unknown00;
    OpaqueRefCounted *owner04;
public:
    ~Rva002390CB() { if(owner04) owner04->Release_Ref(); }
};
class Rva004D95CE {
public:
    ~Rva004D95CE();
private:
    Rva002390CB a,b;
};
Rva004D95CE::~Rva004D95CE() {}
class Rva004D960CHead {
    OpaqueRefCounted *p;
public:
    ~Rva004D960CHead() { if(p) p->Release_Ref(); }
};
class Rva004D960C {
public:
    ~Rva004D960C();
private:
    Rva004D960CHead head;
    Rva004D95CE pair;
};
Rva004D960C::~Rva004D960C() {}
