enum SNodeType {
  LIST,
  STRING,
  SYMBOL,
  INTEGER,
  FLOAT
};

struct SNode {
  enum SNodeType type;
  struct SNode *next;

  union {
    struct SNode *list;
    char *value;
  };
};

struct SNode *parse_sexpr_file(FILE *fp);
void snode_free(struct SNode *node);
