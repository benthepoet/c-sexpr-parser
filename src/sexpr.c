#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"

#define BUFFER_SIZE 512

int is_float(char *str) {
  char *ptr = NULL;
  strtod(str, &ptr);
  return !*ptr;
}

int is_integer(char *str) {
  char *ptr = NULL;
  strtol(str, &ptr, 0);
  return !*ptr;
}

int is_terminator(char c) {
  return isspace(c) || c == '(' || c == ')';
}

struct SNode *parse_sexpr_file(FILE *fp) {
  struct SNode *tail, *head = NULL;
  int c;

  while ((c = fgetc(fp)) != EOF) {
    struct SNode *node = NULL;

    if (c == ')') {
      break;
    } else if (c == '(') {
      node = calloc(1, sizeof(struct SNode));
      node->type = LIST;
      node->list = parse_sexpr_file(fp);
    } else if (c == '"') {
      int length = 0;
      char buffer[BUFFER_SIZE];

      while ((c = fgetc(fp)) != '"' && length < BUFFER_SIZE - 1) {
        buffer[length] = c;
        length++;
      }
      buffer[length] = '\0';

      node = calloc(1, sizeof(struct SNode));
      node->type = STRING;
      node->value = calloc(length + 1, sizeof(char));
      strcpy(node->value, buffer);
    } else if (!isspace(c)) {
      int length = 1;
      char buffer[BUFFER_SIZE] = { c };

      while (!is_terminator(c = fgetc(fp)) && length < BUFFER_SIZE - 1) {
        buffer[length] = c;
        length++;
      }
      buffer[length] = '\0';

      node = calloc(1, sizeof(struct SNode));
      node->value = calloc(length + 1, sizeof(char));
      strcpy(node->value, buffer);

      if (is_float(node->value)) {
        node->type = FLOAT;
      } else if (is_integer(node->value)) {
        node->type = INTEGER;
      } else {
        node->type = SYMBOL;
      }
    }

    if (node != NULL) {
      if (head == NULL) {
        head = tail = node;
      } else {
        tail = tail->next = node;
      }
    }
  }

  return head;
}

void snode_free(struct SNode *node) {
  struct SNode *tmp;

  while (node != NULL) {
    tmp = node;

    if (node->type == LIST) {
      snode_free(node->list);
    } else {
      free(node->value);
      node->value = NULL;
    }

    node = node->next;

    free(tmp);
    tmp = NULL;
  }
}
