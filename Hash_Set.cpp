///@file 开地址表示法（拉链法）散列表
///@author zhaowei
///@date 2014.12.30
///@version 1.0

template<typename elem_t>	//声明模板参数

///@brief 元素的哈希函数
int elem_hash(const elem_t &e);

template<typename elem_t>	//声明模板参数

///@brief 元素的比较函数
bool operator==(const elem_t &e1, const elem_t &e2);

///@brief 哈希集合
template<typename elem_t>
class hash_set
{
public:
	///@brief 构造函数
	///@param[in] prime 哈希函数的质数
	///@param[in] capacity 哈希表的容量
	hash_set(int prime, int capacity);

	///@brief 析构函数
	~hash_set();

	///@brief 在哈希表中寻找相应元素
	///@param[in] elem 待寻找的元素
	///@return 如果成功找到，则返回true，否则返回false
	bool find(const elem_t &elem);

	///@brief 在哈希表中插入新元素
	///@param[in] elem 待插入的新元素
	///@return 如果成功插入，则返回true，否则返回false
	bool insert(const elem_t &elem);

private:
	int prime;		//哈希表取模的质数，即哈希桶的个数，小于capacity
	int capacity;	//哈希表容量，一定要大于元素最大个数
	int *head;		//哈希表槽中链表首结点下标

	
	struct node_t	//静态链表
	{
		elem_t elem;
		int next;
		node_t():next(-1){};
	}*node;

	int size; //实际元素个数
};

template<typename elem_t>
hash_set<elem_t>::hash_set(int prime, int capacity)
{
	this->prime = prime;
	this->capacity = capacity;
	head = new int[prime];
	node = new node_t[capacity];
	fill(head head + prime, -1);	//将head填满-1
	fill(node, node + capacity, node_t());	//将node填满node_t()
	size = 0;	
}

template<typename elem_t>
hash_set<elem_t>::~hash_set()
{
	this->prime = 0;
	this->capacity = 0;
	delete[] head;
	delete[] node;
	head = NULL;
	node = NULL;
	size = 0;
}

template<typename elem_t>
bool hash_set<elem_t>::find(const elem_t &elem)
{
	for (int i = head[elem_hash(elem)]; i != -1; i = node[i].next)
		if (elem == node[i].elem)
		{
			return true;
		}
	return false;	
}

template<typename elem_t>
bool hash_set<elem_t>::insert(const elem_t &elem)
{
	const int hash_code = elem_hash(elem);

	for (int i = head[hash_code]; i != -1; i = node[i].next)
	{
		if (elem == node[i].elem)
		{
			return false;	//如果已经存在，返回false
		}

		//如果不存在，则插入首结点之前
		node[size].next = head[hash_code];
		node[size].elem = elem;
		head[hash_code] = size++;	//??
		return true;
	}
}