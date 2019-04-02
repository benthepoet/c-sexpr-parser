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

      char buffer[512];

      if (c == '"') {
        if (fscanf(fp, "\"%511[^\"]\"", buffer)) {
          node = calloc(1, sizeof(struct SNode));
          node->type = STRING;
          node->string = calloc(strlen(buffer) + 1, sizeof(char));
          strcpy(node->string, buffer);
        }
      } else {
        if (fscanf(fp, "%511[^()\t\n\v\f\r ]", buffer)) {
          node = calloc(1, sizeof(struct SNode));
          node->type = SYMBOL;
          node->symbol = calloc(strlen(buffer) + 1, sizeof(char));
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
