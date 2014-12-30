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
	int *head;		//首结点下标

	//静态链表
	struct node_t
	{
		elem_t elem;
		int next;
		node_t():next(-1){};
	}*node;

	int size; //实际元素个数
};