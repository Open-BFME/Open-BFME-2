// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc /DNDEBUG
// WBDEE010 names AttackPriorityInfo::doModPriorityByCombatChain in
// ScriptEngineSupport.cpp; retail357025..3570D1 and getPriority357CDE prove
// the float/const-object ABI and purpose. BF1 ba7ddda and ZH script reference
// units provide the sibling getPriority lookup, but no combat-chain donor.
// Target views: Object template+4 / chain+520; manager definitions+10 with
// 132-byte stride; TheAI+18 data / float+54. Existing rowed callees and
// ledger-owned globals retain their provisional names and measured ABIs.
// O1 G7 SSE preserves the native mixed SSE add and x87 comparison/return.
class Player;
struct CombatChainTemplateView { char unknown00[0x520]; int chain; };
class Object {
public:
 Player *getControllingPlayer() const;
 void *unknown00;
 const CombatChainTemplateView *m_template;
};
class Rva002A8A81 { public: float rva002A8A81(void *); };
struct Rva002A8AB1Record { void *rva002C6ACB(); };
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
struct CombatChainAIDataView { char unknown00[0x54]; float scale; };
class AI;
extern AI *TheAI;
struct CombatChainAIView { char unknown00[0x18]; CombatChainAIDataView *data; };
class AttackPriorityInfo { public: float doModPriorityByCombatChain(float,const Object *,const Object *) const; };
float AttackPriorityInfo::doModPriorityByCombatChain(float priority,const Object *searcher,const Object *target) const
{
    int chain = searcher->m_template->chain;
    if (chain != -1) {
        Rva002A8A81 *definition = reinterpret_cast<Rva002A8A81 *>(
            reinterpret_cast<char *>(g_00DFEEF8) + 0x10 + chain * 0x84);
        float modifier = definition->rva002A8A81(const_cast<Object *>(target));
        if (modifier != -1.0f) {
            Rva002A8AB1Record *ai = g_00DFEEF8->rva002A8AB1(searcher->getControllingPlayer());
            if (ai) {
                Player *targetPlayer = target->getControllingPlayer();
                if (ai->rva002C6ACB() == targetPlayer)
                    modifier += 100.0f;
            }
            return priority + modifier / reinterpret_cast<CombatChainAIView *>(TheAI)->data->scale;
        }
        return 0.0f;
    }
    return priority;
}
