// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Address-derived debug-color helper, retail2EBD99..2EBE54 RET cdecl.
// Target loads Object.drawable through rowed Thing/Object getter5508E2,
// sets Drawable+118 bit20, and calls rowed271779 RGB-envelope setter.
// Contain+250 slot118 writes an8-byte item view; its second word points
// to a list whose header is word0. Target recursively colors contained
// items magenta. The default parent color is red. View's first word is
// opaque, and the virtual's original identity is not asserted.
// ZH ContainModule.h supplies contained-object list semantics; this debug
// helper itself was not found in the ZH Pathfinder donor.
struct RGBColor00271779 { float red,green,blue; };
class Rva00271779 {public: void rva00271779(RGBColor00271779,int,int,int,float,float);};
class Drawable {public: char pad00[0x118];unsigned int flags;};
class Object;
struct Rva002EBD99Node {Rva002EBD99Node *next,*prev;Object *obj;};
struct Rva002EBD99List {Rva002EBD99Node *head;};
struct Rva002EBD99Items {void *opaque;Rva002EBD99List *list;};
class Rva002EBD99Contain {
public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
 S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
 S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
 S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
 S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
 S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
 S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69)
#undef S
 virtual Rva002EBD99Items items() const;
};
class Object {
public:
 Drawable *getDrawable() const;
 char pad00[0x250];Rva002EBD99Contain *contain;
};
void Rva002EBD99(Object *obj,const RGBColor00271779 *color)
{
 Drawable *d=obj->getDrawable();
 if(d) {
  d->flags|=0x20;
  RGBColor00271779 red={1.0f,0.0f,0.0f};
  if(!color)color=&red;
  ((Rva00271779 *)d)->rva00271779(*color,0,0,100,0.0f,0.0f);
 }
 Rva002EBD99Contain *contain=obj->contain;
 if(contain) {
  Rva002EBD99Items view=contain->items();
  for(Rva002EBD99Node *n=view.list->head->next;n!=view.list->head;n=n->next) {
   RGBColor00271779 magenta={1.0f,0.0f,1.0f};
   Rva002EBD99(n->obj,&magenta);
  }
 }
}
