// ?processItems@LivingWorldEyeTower@@AAEXXZ @0x003F9A99 193B
// Chain from just-landed getPair 0x003F9A2B in same TU. BFME1 donor
// LivingWorldEyeTowerState.cpp processItems with LivingWorld path lines 366/374.
// Layout 0x74 proven by retail offsets. Globals 1.0f (1.0f) and g_009BA4E8.
// Best probe chain2: 193B same size 0 branch 0 layout; only 2 xmm reg swaps in
// second rate block (ours xmm1=g xmm0=frames vs retail xmm0 xmm1) plus the
// +0x6c store register. First block loop and stores all match.
// cl: /DNDEBUG /MD /GX-
// Built from the banked attempt reverse/attempts/0x003f9a99.cpp; fix: the float
// read through g_Va007BB8D8 is a compiler literals holding the retail
// values, not extern globals, which is what gives retail's operand order.
int GetGameLogicRandomValue(int low, int high, char *file, int line);

extern int g_009BA4E8;
// g_009BA4E8: matched references place it at VA 0xdba4e8 (retail .data initial value 30).
int g_009BA4E8 = 30;
struct EyeTowerPair {
  EyeTowerPair(float x, float y) : first(x), second(y) {}
  ~EyeTowerPair() {}
  float first;
  float second;
};
// Donor type and interface from BFME1 LivingWorldEyeTowerState.cpp.
struct Gen0060CBB0Pair { float first; float second; };
class BfmeStateDF {
public:
  void interpolate(Gen0060CBB0Pair *from, Gen0060CBB0Pair *to,
                   Gen0060CBB0Pair *current, float progress);
};
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class LivingWorldEyeTower {
  char m_head[0x3C];
  EyeTowerPair *m_begin;
  EyeTowerPair *m_end;
  EyeTowerPair *m_capacity;
  void *getPair();
  void processItems();
  void beginState();
public:
  void rva003F9B5A();
  unsigned int m_state;
  EyeTowerPair m_to;
  EyeTowerPair m_from;
  EyeTowerPair m_current;
  float m_rate64;
  float m_progress68;
  float m_rate6C;
  float m_progress70;
};
void LivingWorldEyeTower::processItems() {
  m_from = m_current;
  int frames = (GetGameLogicRandomValue(0, 2, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\LivingWorld\\LivingWorldEyeTower.cpp", 366) + 4) * g_009BA4E8;
  m_rate64 = 1.0f / (float)frames;
  m_progress68 = 0.0f;
  do {
    EyeTowerPair *pair = (EyeTowerPair *)getPair();
    m_to = *pair;
  } while (m_to.first == m_current.first && m_to.second == m_current.second);
  frames = (GetGameLogicRandomValue(0, 8, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\LivingWorld\\LivingWorldEyeTower.cpp", 374) + 4) * g_009BA4E8;
  m_rate6C = 1.0f / (float)frames;
  m_progress70 = 0.0f;
  m_state = 1;
}
void LivingWorldEyeTower::rva003F9B5A()
{
  m_current = *(EyeTowerPair *)getPair();
  if ((((char *)m_end - (char *)m_begin) & 0xFFFFFFF8) == 0)
  {
    m_state = 1;
    m_rate6C = 0.0f;
    return;
  }
  processItems();
}

// ?beginState@LivingWorldEyeTower@@AAEXXZ @0x003F9B93 90B
// BFME1 donor: game/GameEngine/Source/GameClient/LivingWorldEyeTowerState.cpp
// at 6583b3c1ff21db4a561285717028fdafc780b7db. Target bytes prove the +0x64/
// +0x68 rate and progress fields, singleton load at VA 0x00DFEF18, pair pointers
// at +0x54/+0x4c/+0x5c, and call at 0x003F9BD0. The BfmeStateDF name/signature
// follows the donor declaration; target body semantics and call ABI agree.
void LivingWorldEyeTower::beginState()
{
  m_progress68 = m_rate64 + m_progress68;
  if (m_progress68 >= 1.0f)
    m_progress68 = 1.0f;

  ((BfmeStateDF *)g_00DFEF18)->interpolate(
      (Gen0060CBB0Pair *)&m_from,
      (Gen0060CBB0Pair *)&m_to,
      (Gen0060CBB0Pair *)&m_current,
      m_progress68);

  if (m_progress68 >= 1.0f)
    processItems();
}
