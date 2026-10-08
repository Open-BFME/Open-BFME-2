// Native 0x004DD8FA..0x004DD9E3, 233 bytes, RET4.
// Existing 18-byte slot flushes pass this receiver and slots at +04/+1C/+34.
// Native removal follows cell->info, five heads at info+14, and 12-byte nodes
// with next/cell/object at 0/4/8; slot layer/cell are +10/+14. The fallback
// traverses the native AI +10 map, ground cells +0C with dimensions +1C/+20,
// then sixteen 40-byte layers at +60. All offsets and extents are target facts.
// WB 01286E90 calls this operation PathfinderPosGoalManager::RemoveObjPtr and
// corroborates its loops, failure fallback, ReleaseInfo, and -666666 reset.
// Preserve the existing receiver/slot names; the original slot and node type
// names are unknown. BFME1 ba7ddda and ZH provide no clean class implementation.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oy-
class Object;
struct Rva004DD8FAInfo;
class PathfindCell {
public:
    void ReleaseInfo();
    Rva004DD8FAInfo *m_info;
    unsigned char m_rest[12];
};
struct Rva004DD8FANode {
    Rva004DD8FANode *m_next;
    PathfindCell *m_cell;
    Object *m_object;
};
struct Rva004DD8FAInfo {
    unsigned char m_prefix[0x14];
    Rva004DD8FANode *m_heads[5];
};
struct Rva004DD843Slot {
    int m_value;
    unsigned char m_opaque[12];
    int m_layer;
    PathfindCell *m_cell;
};
struct Rva004DD8A6Entry;
void __cdecl rva004DD8A6(int key, Rva004DD8A6Entry *entries, int count);
void __cdecl rva004DD890(void *node);
struct Rva004DD8FALayer {
    PathfindCell *m_cells;
    unsigned char m_gap4[4];
    int m_width;
    int m_height;
    unsigned char m_tail[0x30];
};
struct Rva004DD8FAMap {
    unsigned char m_prefix[12];
    PathfindCell *m_cells;
    unsigned char m_gap10[12];
    int m_width;
    int m_height;
    unsigned char m_gap24[0x3c];
    Rva004DD8FALayer m_layers[16];
};
struct Rva004DD8FAAIView {
    unsigned char m_prefix[16];
    Rva004DD8FAMap *m_pathfinder;
};
class AI;
extern AI *TheAI;
class Rva004DD843 {
public:
    void rva004DD8FA(Rva004DD843Slot *slot);
    Object *m_object;
    Rva004DD843Slot m_position;
    Rva004DD843Slot m_goal;
    Rva004DD843Slot m_other;
};
void Rva004DD843::rva004DD8FA(Rva004DD843Slot *slot)
{
    PathfindCell *cur = slot->m_cell;
    while (cur) {
        if (!cur->m_info) break;
        Rva004DD8FANode **p = &cur->m_info->m_heads[slot->m_layer];
        for (; *p; p = &(*p)->m_next) {
            if ((*p)->m_object == m_object) break;
        }
        if (!*p) {
            Rva004DD8FAMap *map = ((Rva004DD8FAAIView *)TheAI)->m_pathfinder;
            rva004DD8A6((int)m_object, (Rva004DD8A6Entry *)map->m_cells,
                       (map->m_width + 1) * (map->m_height + 1));
            for (int i = 0; i < 16; ++i) {
                Rva004DD8FALayer *layer = &map->m_layers[i];
                if (layer->m_cells) {
                    rva004DD8A6((int)m_object, (Rva004DD8A6Entry *)layer->m_cells,
                               layer->m_width * layer->m_height);
                }
            }
            break;
        }
        PathfindCell *next = (*p)->m_cell;
        Rva004DD8FANode *removed = *p;
        *p = removed->m_next;
        rva004DD890(removed);
        if (!cur->m_info->m_heads[slot->m_layer]) {
            int i;
            for (i = 0; i < 5; ++i) {
                if (cur->m_info->m_heads[i]) break;
            }
            if (i == 5) cur->ReleaseInfo();
        }
        cur = next;
    }
    slot->m_cell = 0;
    slot->m_value = -666666;
}

// Native 004DD8A6..004DD8FA, 84 bytes, cdecl three-argument fallback.
// WB1286D20 ClearObjectPtr corroborates 16-byte cell traversal, five heads,
// key at node+8, and exactly one unlink per head. The sequenced node-key read
// preserves the observed cursor/key access order; no guessed owning type.
struct Rva004DD8A6Node
{
	Rva004DD8A6Node *m_next;
	int m_04;
	int m_key;
};

struct Rva004DD8A6Table
{
	char m_pad00[0x14];
	Rva004DD8A6Node *m_buckets[5];
};

struct Rva004DD8A6Entry
{
	Rva004DD8A6Table * volatile m_table;
	char m_pad04[0x0c];
};

void __cdecl rva004DD890(void *node);

__declspec(noinline) void __cdecl rva004DD8A6(volatile int key, Rva004DD8A6Entry *entries, int count)
{
	if (count <= 0)
		return;
	int remaining = count;

	do {
		if (entries->m_table != 0) {
			for (int offset = 0x14; offset < 0x28; offset += 4) {
				Rva004DD8A6Node **link =
					(Rva004DD8A6Node **)((char *)entries->m_table + offset);
                for (; *link; link = &(*link)->m_next) {
                    const int nodeKey = (*link)->m_key;
                    if (nodeKey == key) {
                        Rva004DD8A6Node *removed = *link;
                        *link = removed->m_next;
                        rva004DD890(removed);
                        break;
                    }
                }
			}
		}
		entries = (Rva004DD8A6Entry *)((char *)entries + 0x10);
	} while (--remaining != 0);
}

// Native004DD6CF..004DD722, 83B cdecl float-to-bin helper called by SetGoal.
// WB12875C0 corroborates normalizeAngle, positive wrap, twelve bins, half-up
// rounding, and wrap-to-zero above eleven. Native SSE retains two distinct
// float multiplies; sequencing the division and scale reproduces that rounding.
// Original helper name is unknown; use the existing investigation spelling.
float __cdecl normalizeAngle(float angle);
int __cdecl Rva004DD6CFGet(float angle)
{
    angle = normalizeAngle(angle);
    if (angle < 0.0f)
        angle += 6.2831855f;
    float steps = angle / 6.2831855f;
    steps *= 12.0f;
    if (steps > 11.0f)
        return 0;
    return (int)(steps + 0.5f);
}
