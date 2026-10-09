// cl: /O1 /G7 /arch:SSE /MD
// ?rva0045628C@BuildingBehavior@@QAEXPBUBuildingWindowList@@PAVDrawable@@H@Z @0x0045628C 52B
// BuildingBehavior::update (0x004562F8) loads the module into ecx before each
// of its five calls, so this is a thiscall member that ignores this. It walks
// one window-name list [start,finish) (AsciiString stride 4) of the module
// data and calls the rowed Drawable::rva002724FD 0x002724FD with
// (string, state, 1, 0.0f, 0.0f).
class AsciiString;
class Drawable {
public:
    void rva002724FD(const AsciiString &s, int a, int b, float c, float d);
};
struct BuildingWindowList {
    char *m_start;
    char *m_finish;
    char *m_end;
};
class BuildingBehavior {
public:
    void rva0045628C(const BuildingWindowList *names, Drawable *draw, int state);
};
void BuildingBehavior::rva0045628C(const BuildingWindowList *names, Drawable *draw, int state)
{
    char *cur = names->m_start;
    while (cur != names->m_finish) {
        draw->rva002724FD(*(const AsciiString *)cur, state, 1, 0.0f, 0.0f);
        cur += 4;
    }
}
