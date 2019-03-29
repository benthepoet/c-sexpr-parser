enum SNodeType {
  LIST = 0,
  STRING = 1,
  SYMBOL = 2
};

struct SNode {
  enum SNodeType type;
  struct SNode *next;

  union {
    struct SNode *list;
    char *string;
    char *symbol;
  };
};

void snode_free(struct SNode *node);
struct SNode *parse_sexpr_file(FILE *fp);
