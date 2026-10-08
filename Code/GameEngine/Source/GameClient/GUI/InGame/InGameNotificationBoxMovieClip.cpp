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
