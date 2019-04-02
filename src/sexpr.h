enum SNodeType {
  LIST,
  STRING,
  SYMBOL,
  INTEGER,
  FLOAT
};

struct SNode {
  struct SNode *next;
  enum SNodeType type;
  union {
    struct SNode *list;
    char *value;
  };
};

struct SNode *parse_sexpr_file(FILE *fp);
void snode_free(struct SNode *node);
