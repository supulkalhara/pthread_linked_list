struct list_node_s
{
    int data;
    struct list_node_s *next;
};

int Member(int value, struct list_node_s **head_p);
int Insert(int value, struct list_node_s **head_pp);
int Delete(int value, struct list_node_s **head_pp);
void Populate(struct list_node_s *head_p, int n);
void Display(struct list_node_s *head_p);
void DisplayStatistics(const char* label, int count, int countPerThread);
int16_t RandomIntegerGenerator();



