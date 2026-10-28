// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
template<class T> __forceinline volatile T &r1_vwrite(T &value) { return *(volatile T *)&value; }
// ?0W3DDisplay@@QAE@XZ, retail 0x00049DEA, 293 bytes.
// Stores through r1_vwrite keep the member zero-stores in retail's order (R1 paired volatile
// stores, 0x49DEA nd4 -> 2); the equal-arm receiver on m_1cc moves the XOR-EAX zero materialisation
// after the six stores (W7-S2 r4 sweepeq2). Both are scheduling spellings, not source semantics.
// W3DDisplay constructor (ZH W3DDisplay::W3DDisplay twin). Identity: stores vtable 0x7C3C80 whose
// init is the W3DDisplay::init at 0x00046A50 (same +0x144 initialized byte, +0x148/+0x158 light
// arrays, +0x168 Render2D, +0x27C debug display and the three scene globals it fills), and zeroes
// those globals. Base constructor 0x0025D489 is the Display ctor (see W3DDisplayRva0025D2F6.cpp).
// Layout beyond the stores below is unmeasured and left as padding.
namespace _STL

{
 template <class T> class allocator 
 {
  public: allocator() 
  {
   
  }
  
 }
 ;
 template <class T, class A> class _Vector_base
 
 {
  public:
  _Vector_base(const A &a);
  ~_Vector_base();
  T *m_start;
  T *m_finish;
  T *m_endOfStorage;
  
 }
 ;
 template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
 
 {
  public:
  vector(const A &a = A()) : _Vector_base<T, A>(a) 
  {
   
  }
  // Declared only: the unwind funclet calls retail's ~vector<int> (a 5-byte
  // jump to ~_Vector_base); this view's implicit copy is not retail's and,
  // from this unit's link place (0x00049DEA), would be the first copy.
  ~vector();
  
 }
 ;
 
}
class Rva00043511

{
 public:
 void rva00043511() throw();
 Rva00043511 *rva00045984();
 Rva00043511() 
 {
  rva00045984();
  
 }
 char data[0x24];
 
}
;
class Rva0065CA4;
// The list it allocates is constructed by 0x00065D40, the
// MultiListClass<CameraShakerClass> constructor (vtable 0x7C5C78).
class CameraShakeSystemClass
{
 public:
 class CameraShakerClass;
 void *m_shakers; // the one word retail keeps at 0x009E1E94
};
template <class ObjectType> class MultiListClass
{
 public:
 MultiListClass();
 virtual ~MultiListClass();
 char data[0x14];
};
struct GlobalDataView

{
 char pad00[0x28];
 int value28;
 
}
;
class Display

{
 public:
 Display();
 virtual ~Display(); // vtable view matches W3DDisplayDtor.cpp's (destructor only)
 char data[0x13c];
 char pad140[4];
 
}
;
class RTS3DScene;
class RTS2DScene;
class RTS3DInterfaceScene;
class W3DDisplay : public Display

{
 public:
 W3DDisplay();
 virtual ~W3DDisplay(); // rowed 0x00049FCB (W3DDisplayDtor.cpp)
 static RTS3DScene *m_3DScene; // 0x009E1B34
 static RTS2DScene *m_2DScene; // 0x009E1B38
 static RTS3DInterfaceScene *m_3DInterfaceScene; // 0x009E1B3C
 bool m_initialized;
 char pad145[3];
 void *m_lightA[4];
 void *m_lightB[4];
 void *m_2DRender;
 int m_16c;
 int m_170;
 int m_174;
 int m_178;
 bool m_17c;
 char pad17d[3];
 float m_180;
 int m_184;
 int m_188;
 int m_arr18c[16];
 int m_1cc;
 int m_arr1d0[25];
 int m_arr234[17];
 int m_278;
 int m_27c;
 Rva00043511 m_280;
 _STL::vector<int> m_2a4;
 
}
;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
// Retail .data starts it at 0; this ctor and the dtor null it.
RTS3DInterfaceScene *W3DDisplay::m_3DInterfaceScene = 0;
// CameraShakerSystem (0x009E1E94): this ctor fills it with the shaker list and
// W3DDisplay::~W3DDisplay deletes and nulls it. Retail .data starts it at 0.
CameraShakeSystemClass CameraShakerSystem;
W3DDisplay::W3DDisplay()

{
 m_184 = 0;
 m_188 = 0;
 m_initialized = false;
 m_3DScene = 0;
 m_2DScene = 0;
 m_3DInterfaceScene = 0;
 m_180 = (float)((GlobalDataView *)TheWritableGlobalData)->value28;
 for (int i = 0; i < 4; i++)
 
 {
  m_lightA[i] = 0;
  m_lightB[i] = 0;
  
 }
 m_2DRender = 0;
 m_17c = false;
 m_16c = 0;
 m_170 = 0;
 m_174 = 0;
 m_178 = 0;
 for (int i = 0; i < 16; i++)
 m_arr18c[i] = 0;
 for (int i = 0; i < 25; i++)
 m_arr1d0[i] = 0;
 for (int i = 0; i < 17; i++)
 m_arr234[i] = 0;
 r1_vwrite((m_184 ? m_1cc : m_1cc)) = 0;
 r1_vwrite(m_278) = 0;
 m_27c = 0;
 CameraShakerSystem.m_shakers = new MultiListClass<CameraShakeSystemClass::CameraShakerClass>;
 m_280.rva00043511();
 
}
