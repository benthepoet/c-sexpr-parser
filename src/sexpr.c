#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"

void snode_free(struct SNode *node) {
  struct SNode *tmp;

  while (node != NULL) {
    tmp = node;

    if (node->type == STRING) {
      free(node->string);
      node->string = NULL;
    }
    else if (node->type == SYMBOL) {
      free(node->symbol);
      node->symbol = NULL;
    }
    else if (node->type == LIST) {
      snode_free(node->list);
    }

    node = node->next;

    free(tmp);
    tmp = NULL;
  }
}

struct SNode *parse_sexpr_file(FILE *fp) {
  struct SNode *tail, *head = NULL;

  int c;
  char buffer[512];

  while ((c = fgetc(fp)) != EOF) {
    struct SNode *node = NULL;

    if (c == ')') {
      break;
    }
    else if (c == '(') {
      node = malloc(sizeof(struct SNode));
      node->next = NULL;
      node->type = LIST;
      node->list = parse_sexpr_file(fp);
    }
    else if (!isspace(c)) {
      ungetc(c, fp);

      node = malloc(sizeof(struct SNode));
      node->next = NULL;

      if (c == '"') {
        node->type = STRING;
        if (fscanf(fp, "\"%31[^\"]\"", buffer)) {
          node->string = malloc(strlen(buffer) + 1);
          strcpy(node->string, buffer);
        }
      } else {
        node->type = SYMBOL;
        if (fscanf(fp, "%31[^() \t\n\v\f\r]", buffer)) {
          node->symbol = malloc(strlen(buffer) + 1);
          strcpy(node->symbol, buffer);
        }
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
