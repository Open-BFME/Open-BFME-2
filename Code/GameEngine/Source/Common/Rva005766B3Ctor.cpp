// cl: /MD
// Native86E7D0 contains callback5766D3, not a virtual destructor.
// Caller576778 passes three pointer-sized words; original types unresolved.
class LivingWorldPendingBattle;
class PendingBattleVisitor {
public:
 virtual bool Visit(LivingWorldPendingBattle *) = 0;
 ~PendingBattleVisitor() {}
};
class Rva005766B3 : public PendingBattleVisitor {
public:
 Rva005766B3(int,int,int);
 ~Rva005766B3() {}
 virtual bool Visit(LivingWorldPendingBattle *);
private:
 int a,b,c;
};


Rva005766B3::Rva005766B3(int a, int b, int c)
	: a(a), b(b), c(c)
{
}
