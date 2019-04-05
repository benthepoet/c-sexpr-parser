#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../src/sexpr.h"

void run_tests(struct SNode *node);

int main(int argc, char *argv[]) {
  // Unused parameters
  (void)argc;
  (void)argv;
  
  // Open the file stream
  FILE *fp = fopen("test/data.lisp", "r");

  // Read the file into a tree
  struct SNode *node = snode_parse(fp);

  // Close the file stream
  fclose(fp);

  // Run tests
  run_tests(node);

  // Deallocate the memory used by the tree
  snode_free(node);

  return 0;
}

void run_tests(struct SNode *node) {
  printf("List - Root\n");
  assert(node != NULL);
  assert(node->type == LIST);
  
  printf("Symbol - Single-character\n");
  struct SNode *current = node->list;
  assert(current->type == SYMBOL);
  assert(!strcmp(current->value, "a"));

  printf("Symbol - Multi-character\n");
  current = current->next;
  assert(current->type == SYMBOL);
  assert(!strcmp(current->value, "abc-def"));
  
  printf("String - Empty\n");
  current = current->next;
  assert(current->type == STRING);
  assert(!strcmp(current->value, ""));
  
  printf("String - Multi-character\n");
  current = current->next;
  assert(current->type == STRING);
  assert(!strcmp(current->value, "def-hij"));
  
  printf("List - Child\n");
  struct SNode *child = current->next;
  assert(child->type == LIST);
  
  printf("Integer - Negative\n");
  child = child->list;
  assert(child->type == INTEGER);
  assert(!strcmp(child->value, "-123"));
  
  printf("Integer - Positive\n");
  child = child->next;
  assert(child->type == INTEGER);
  assert(!strcmp(child->value, "123"));
  
  printf("Float - Negative\n");
  child = child->next;
  assert(child->type == FLOAT);
  assert(!strcmp(child->value, "-1.234"));
  
  printf("Float - Positive\n");
  child = child->next;
  assert(child->type == FLOAT);
  assert(!strcmp(child->value, "1.234"));

  printf("Symbol - Keyword\n");
  current = current->next->next;
  assert(current->type == SYMBOL);
  assert(!strcmp(current->value, ":cba"));
}
