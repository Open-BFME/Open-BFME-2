// cl: /O1 /EHsc /MD /arch:SSE
// Target constructor 2FD6F6 installs the table at VA C0719C and fixes the
// filter's next/object/flag/scalar fields at +4/+8/+C/+10. The table's
// slot 1 names this 34B predicate at 261513; its destructor and player-mask
// slots are 395A19 and 36CC7A. Existing filter-chain consumers pass Object*.
// The helper's original operation name remains unknown; keep its admitted
// address-derived spelling and four-byte argument representation.
class Object;
#include "../../Include/GameLogic/Module/Rva0028F326Owner.h"
class Rva00261513Filter
{
public:
 virtual ~Rva00261513Filter();
 virtual bool allow(Object *value);
 virtual int getPlayerMask();
private:
 unsigned char m_next04[4];
 Rva0028F326Owner *m_helper08;
 unsigned char m_expected0C;
 unsigned char m_pad0D[3];
 float m_scalar10;
};
bool Rva00261513Filter::allow(Object *value)
{
 return m_helper08->rva0028F326(reinterpret_cast<unsigned int>(value),m_scalar10)==m_expected0C;
}
