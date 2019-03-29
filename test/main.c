#include <stdio.h>

#include "../src/sexpr.h"

void print_node(struct SNode *node);

int main(int argc, char *argv[]) {
  FILE *fp = fopen("test/data.lisp", "r");

  // Read the file into a tree
  struct SNode *node = parse_sexpr_file(fp);

  // Walk the tree and print the nodes
  print_node(node);

  // Deallocate the memory used by the tree
  snode_free(node);

  return 0;
}

void print_node(struct SNode *node) {
  struct SNode *current = node;
  while (current != NULL) {
    if (current->type == LIST) {
      printf("LIST\n");
      print_node(current->list);
    } else if (current->type == STRING) {
      printf("STRING: %s\n", current->string);
    } else if (current->type == SYMBOL) {
      printf("SYMBOL: %s\n", current->symbol);
    }
    current = current->next;
  }
}
