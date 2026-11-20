// cl: /O1 /G7 /arch:SSE /MD /GX- /DNDEBUG
//
// ?rva00599870@Rva005997CD@@QAE?AW4ObjectID@@PBUVec2@@_N@Z, retail 0x00599870..0x0059992A
// (186 bytes, EH-free, thiscall RET 8): the nearest-dozer search of Rva005997CD (its ctor
// 0x00599784 and dtor 0x005997CD are rowed): walk the object-id list at +0, resolve each
// id, skip objects whose AI filter result is valid, skip status 0x5A unless the flag is
// set, and keep the id with the smallest squared 2D distance to the position (the first
// candidate always wins). The position is read through a by-value Vec2 copy made with
// retail's inline member-wise copy constructor (the Coord2D view of Lib/Coord2DCtorView.h):
// that is what gives retail's xmm move pairs; the winner test is `best == 0` directly.
// Evidence: native bytes; every callee rowed. Identity of the owner is address-derived.
#include "GameLogicObjectLookupView.h"

struct Vec2
{
    float x;
    float y;
    Vec2() {}
    Vec2(const Vec2 &vec2) : x(vec2.x), y(vec2.y) {}
};


enum ObjectStatusTypes;

class Object
{
public:
    bool testStatus(ObjectStatusTypes bit) const;
};

extern GameLogic *TheGameLogic;

struct ListNode
{
    ListNode *next;
    int unk04;
    ObjectID id;
};

class FilterResult
{
public:
    virtual void _s00();
    virtual void _s01();
    virtual void _s02();
    virtual void _s03();
    virtual void _s04();
    virtual void _s05();
    virtual void _s06();
    virtual void _s07();
    virtual bool isValid();
};

class FilterSource
{
public:
    virtual void _t00();
    virtual void _t01();
    virtual void _t02();
    virtual void _t03();
    virtual void _t04();
    virtual void _t05();
    virtual void _t06();
    virtual void _t07();
    virtual void _t08();
    virtual void _t09();
    virtual void _t10();
    virtual void _t11();
    virtual void _t12();
    virtual void _t13();
    virtual void _t14();
    virtual void _t15();
    virtual void _t16();
    virtual void _t17();
    virtual void _t18();
    virtual void _t19();
    virtual void _t20();
    virtual void _t21();
    virtual void _t22();
    virtual void _t23();
    virtual void _t24();
    virtual void _t25();
    virtual void _t26();
    virtual void _t27();
    virtual void _t28();
    virtual void _t29();
    virtual void _t30();
    virtual void _t31();
    virtual void _t32();
    virtual void _t33();
    virtual void _t34();
    virtual void _t35();
    virtual void _t36();
    virtual void _t37();
    virtual void _t38();
    virtual void _t39();
    virtual void _t40();
    virtual void _t41();
    virtual void _t42();
    virtual void _t43();
    virtual void _t44();
    virtual void _t45();
    virtual void _t46();
    virtual void _t47();
    virtual void _t48();
    virtual void _t49();
    virtual void _t50();
    virtual void _t51();
    virtual void _t52();
    virtual void _t53();
    virtual void _t54();
    virtual void _t55();
    virtual void _t56();
    virtual void _t57();
    virtual void _t58();
    virtual void _t59();
    virtual void _t60();
    virtual void _t61();
    virtual void _t62();
    virtual void _t63();
    virtual void _t64();
    virtual void _t65();
    virtual void _t66();
    virtual void _t67();
    virtual void _t68();
    virtual void _t69();
    virtual void _t70();
    virtual void _t71();
    virtual void _t72();
    virtual void _t73();
    virtual void _t74();
    virtual void _t75();
    virtual void _t76();
    virtual void _t77();
    virtual void _t78();
    virtual void _t79();
    virtual void _t80();
    virtual void _t81();
    virtual void _t82();
    virtual void _t83();
    virtual void _t84();
    virtual void _t85();
    virtual void _t86();
    virtual void _t87();
    virtual void _t88();
    virtual void _t89();
    virtual void _t90();
    virtual void _t91();
    virtual void _t92();
    virtual FilterResult *getResult();
};

struct ObjectFull
{
    float m_00[14];
    float m_x38;
    float m_y3C;
    unsigned char m_40[536];
    FilterSource *m_258;
};

class Rva005997CD
{
public:
    ObjectID rva00599870(const Vec2 *pos, bool flag);
private:
    ListNode *m_list;
};

ObjectID Rva005997CD::rva00599870(const Vec2 *pos, bool flag)
{
    ListNode *head = m_list;
    float bestDist = 0.0f;
    ObjectID best = INVALID_OBJECT_ID;
    for (ListNode *node = head->next; node != head; node = node->next) {
        Object *obj = TheGameLogic->findObjectByID(node->id);
        if (obj != 0) {
            ObjectFull *full = (ObjectFull *)obj;
            FilterResult *res = full->m_258->getResult();
            if (!res->isValid()) {
                if (!obj->testStatus((ObjectStatusTypes)0x5A) || flag) {
                    Vec2 a(*pos);
                    float dx = a.x - full->m_x38;
                    float dy = a.y - full->m_y3C;
                    float d2 = dx * dx + dy * dy;
                    if (bestDist > d2 || best == INVALID_OBJECT_ID) {
                        bestDist = d2;
                        best = node->id;
                    }
                }
            }
        }
    }
    return best;
}
