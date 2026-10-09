// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c69e0.md plus retail only.
// No decoder source was consulted.
// ?Rva009B60E0BuildTree@@YAXPAI0H@Z retail 0x001C69E0..0x001C6B98 (441 bytes)
// (spec name VP6_BuildHuffTree; the name is the existing pin that the
// matched caller Rva009AB320BuildTables.cpp already calls at its three
// sites). cdecl: 12-byte node array / symbol weights (a 0 weight becomes 1
// in place) / symbol count. Builds 64 stack sort records (successor /
// weight / edge) whose edge is a bitfield: bit 0 leaf and bits 1..7 the
// symbol or node index. Symbols are linked in ascending weight with the
// ordered insert of InsertSorted (0x001C6980) inlined twice. Each step joins
// the two lightest records into the next lower node (left = lighter edge /
// right = second edge / probability byte = 256 * lighter weight / sum
// signed) and inserts the combined record until one record remains so
// node 0 is the root. Indexing the node array by the node number gives
// retail's pointer biased to the probability byte.
struct Vp6HuffEdge { unsigned leaf : 1; unsigned value : 7; };
struct Vp6HuffNode { Vp6HuffEdge left; Vp6HuffEdge right; unsigned char prob; };
struct Vp6HuffRecord { int next; int weight; Vp6HuffEdge edge; };
struct Vp6HuffSort {
	static void Insert(Vp6HuffRecord *list, int index, int *head)
	{
		int cur = *head;
		int prev = *head;
		while (cur != -1) {
			if (list[index].weight <= list[cur].weight)
				break;
			prev = cur;
			cur = list[cur].next;
		}
		if (cur == *head) {
			*head = index;
			list[index].next = cur;
		} else {
			list[prev].next = index;
			list[index].next = cur;
		}
	}
};
void Rva009B60E0BuildTree(unsigned *nodeArray, unsigned *weights, int count)
{
	Vp6HuffRecord list[64];
	Vp6HuffNode *nodes = (Vp6HuffNode *)nodeArray;
	int head = 0;
	int nodeIndex = count - 1;
	int i;
	int next;
	for (i = 0; i < count; i++) {
		list[i].edge.value = i;
		list[i].edge.leaf = 1;
		if (weights[i] == 0)
			weights[i] = 1;
		list[i].weight = weights[i];
		list[i].next = -1;
	}
	next = count;
	for (i = 1; i < count; i++)
		Vp6HuffSort::Insert(list, i, &head);
	while (list[head].next != -1) {
		int second = list[head].next;
		int sum = list[head].weight + list[second].weight;
		nodeIndex--;
		nodes[nodeIndex].left = list[head].edge;
		nodes[nodeIndex].right = list[second].edge;
		nodes[nodeIndex].prob = (unsigned char)((list[head].weight << 8) / sum);
		list[next].weight = sum;
		list[next].next = -1;
		list[next].edge.value = nodeIndex;
		list[next].edge.leaf = 0;
		head = list[second].next;
		Vp6HuffSort::Insert(list, next, &head);
		next++;
	}
}
