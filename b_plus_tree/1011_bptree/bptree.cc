#include "bptree.h"
#include <vector>
#include <sys/time.h>

void
print_tree_core(NODE *n)
{
	printf("[");
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]);
		printf("%d", n->key[i]);
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void
print_tree(NODE *node)
{
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *
alloc_leaf(NODE *parent)
{
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

NODE *
find_leaf(NODE *node, int key)
{
	int kid;

	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}

	return find_leaf(node->chi[kid], key);
}

NODE *
insert_in_leaf(NODE *leaf, int key, DATA *data)
{
	int i;
  int k;
	if (key < leaf->key[0]) {
    // shifting to the right: think from the end of the
    // leaf rather than the head
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i] = leaf->chi[i-1] ;
			leaf->key[i] = leaf->key[i-1] ;
		}
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}
	else {
    // Step 1: Find the place to insert
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}

    // Step 2: Shift and insert
    for (k = leaf->nkey; k > i; k--) {
			leaf->chi[k] = leaf->chi[k-1] ;
			leaf->key[k] = leaf->key[k-1] ;
		}
    leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}
	leaf->nkey++;

	return leaf;
}

void
insert(int key, DATA *data)
{
	NODE *leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}
	else {
		leaf = find_leaf(Root, key);
	}

	if (leaf->nkey < (N-1)) {
		insert_in_leaf(leaf, key, data);
	}
/*
	else {
    // split //
    //create new leaf
    NODE *new_leaf;
    new_leaf = alloc_leaf(NULL);
    //allocate extra memory with N+1 slots
    TMP *tmp_leaf;
    tmp_leaf = alloc_leaf(NULL);
    // copy original leaf to another memory with an extra slot
    int i;
    for (i = 0; i < leaf->nkey; i++) {
      tmp_leaf->chi[i] = leaf->chi[i];
      tmp_leaf->key[i] = leaf->key[i];
    }
    // insert into copy of copy of leaf
    insert_in_leaf(tmp_leaf, key, data);
    // reassigning pointers
    new_leaf->chi[new_leaf->nkey] = leaf->chi[leaf->nkey];
    leaf->chi[leaf->nkey] = new_leaf;
	}
*/
}

void
init_root(void)
{
	Root = NULL;
}

/*
void
search_core(const int key)
{
  NODE *n = find_leaf(Root, key);
	for (int i = 0; i < n->nkey+1; i++) {
		if (n->key[i] == key) return;
	}
  cout << "Key not found: " << key << endl;
	ERR;
}
*/

int
interactive()
{
  int key;

  std::cout << "Key: ";
  std::cin >> key;

  return key;
}

int
main(int argc, char *argv[])
{
	init_root();

  while (true) {
		insert(interactive(), NULL);
    print_tree(Root);
  }

	return 0;
}
