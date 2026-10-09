// cl: /O1 /MD /EHsc
// Notification-box ownership transfer: native004E6BF6..004E6C34 RET4;
// WorldBuilder013238A0 returns a consuming holder through a hidden result.
// Rva004E6A1D clear and Rva004E6A37 destructor/assignment establish the
// existing owner spellings. Copy empties its source before publishing the
// pointer; the returned holder has the independently rowed destructor.
// The original method name is unproven; preserve a neutral address name.
class Rva004E6935;
class Rva004E6A37 {
public:
 Rva004E6935 *m_ptr;
 Rva004E6A37(Rva004E6935 *p=0):m_ptr(p) {}
 Rva004E6A37(Rva004E6A37 &v) { Rva004E6935 *p=v.m_ptr; v.m_ptr=0; m_ptr=p; }
 ~Rva004E6A37();
 Rva004E6A37 &operator=(Rva004E6A37);
};
class Rva004E6A1D {
public:
 Rva004E6935 *m_ptr;
 void clear();
 Rva004E6A37 rva004E6BF6();
};
Rva004E6A37 Rva004E6A1D::rva004E6BF6() {
 Rva004E6A37 transfer(m_ptr);
 m_ptr=0;
 return Rva004E6A37(transfer);
}

// ?rva002B54BB@Rva002B54BB@@QAE?AVRva002B4349@@XZ @0x002B54BB (62B): the same ownership transfer on another owner whose
// consuming holder is Rva002B4349 (rowed destructor 0x002B4349). Target evidence: retail body and the destructor
// REL32 read byte for byte; names are address-derived.
class Rva002B4349 {
public:
 Rva004E6935 *m_ptr;
 Rva002B4349(Rva004E6935 *p=0):m_ptr(p) {}
 Rva002B4349(Rva002B4349 &v) { Rva004E6935 *p=v.m_ptr; v.m_ptr=0; m_ptr=p; }
 ~Rva002B4349();
};
class Rva002B54BB {
public:
 Rva004E6935 *m_ptr;
 Rva002B4349 rva002B54BB();
};
Rva002B4349 Rva002B54BB::rva002B54BB() {
 Rva002B4349 transfer(m_ptr);
 m_ptr=0;
 return Rva002B4349(transfer);
}
