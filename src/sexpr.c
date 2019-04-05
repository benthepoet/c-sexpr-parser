#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"

#define BUFFER_MAX 512

int is_float(char *str) {
  char *ptr = NULL;
  strtod(str, &ptr);
  return !*ptr;
}

int is_integer(char *str) {
  char *ptr = NULL;
  strtol(str, &ptr, 10);
  return !*ptr;
}

int is_lst_term(int c) {
  return c == EOF || isspace(c) || c == '(' || c == ')';
}

int is_str_term(int c) {
  return c == EOF || c == '"';
}

char *read_value(FILE *fp, int *c, int (*is_term)(int)) {
  int len = 0;
  char buffer[BUFFER_MAX + 1];

  while (!is_term(*c = fgetc(fp)) && len < BUFFER_MAX) {
    buffer[len] = *c;
    len++;
  }
  buffer[len] = '\0';
  
  char *str = malloc((len + 1) * sizeof(char));
  return strcpy(str, buffer);
}

// Recursively parse an s-expression from a file stream
struct SNode *snode_parse(FILE *fp) {
  // Using a linked list, nodes are appended to the list tail until we 
  // reach a list terminator at which point we return the list head.
  struct SNode *tail, *head = NULL;
  int c;

  while ((c = fgetc(fp)) != EOF) {
    struct SNode *node = NULL;

    if (c == ')') {
      // Terminate list recursion
      break;
    } else if (c == '(') {
      // Begin list recursion
      node = malloc(sizeof(struct SNode));
      node->type = LIST;
      node->list = snode_parse(fp);
    } else if (c == '"') {
      // Read a string
      node = malloc(sizeof(struct SNode));
      node->type = STRING;
      node->value = read_value(fp, &c, &is_str_term);
    } else if (!isspace(c)) {
      // Read a float, integer, or symbol
      ungetc(c, fp);
      
      node = malloc(sizeof(struct SNode));
      node->value = read_value(fp, &c, &is_lst_term);

      // Put the terminator back
      ungetc(c, fp);

      if (is_integer(node->value)) {
        node->type = INTEGER;
      } else if (is_float(node->value)) {
        node->type = FLOAT;
      } else {
        node->type = SYMBOL;
      }
    }

    if (node != NULL) {
      // Terminate the node
      node->next = NULL;
      
      if (head == NULL) {
        // Initialize the list head
        head = tail = node;
      } else {
        // Append the node to the list tail
        tail = tail->next = node;
      }
    }
  }

  return head;
}

// Recursively free memory allocated by a node
void snode_free(struct SNode *node) {
  while (node != NULL) {
    struct SNode *tmp = node;

    if (node->type == LIST) {
      snode_free(node->list);
    } else {
      // Free current value
      free(node->value);
      node->value = NULL;
    }

    node = node->next;

    // Free current node
    free(tmp);
    tmp = NULL;
  }
}
