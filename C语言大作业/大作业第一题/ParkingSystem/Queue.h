#define maxqueuesize 6                    /*候车场内最多的停车数加一*/
template <class Q>
class SqQueue   //循环队列类
{
public:

    int CarNo[maxqueuesize];           /*车牌号*/
    int front, rear;         /*队首和队尾指针*/
                             /*以下为循环队列的基本运算算法*/
    void InitQueue(SqQueue*& q)/*初始化循环队列*/
    {
        q = (SqQueue*)malloc(sizeof(SqQueue));
        q->front = q->rear = 0;
    }
    int QueueEmpty(SqQueue* q)
    {
        return(q->front == q->rear);
    }
    int QueueFull(SqQueue* q)       /*判断队满*/
    {
        return ((q->rear + 1) % maxqueuesize == q->front);
    }
    int enQueue(SqQueue*& q, int e)      /*进队*/
    {
        if ((q->rear + 1) % maxqueuesize == q->front)    /*队满*/
            return 0;
        q->rear = (q->rear + 1) % maxqueuesize;
        q->CarNo[q->rear] = e;
        return 1;
    }
    int deQueue(SqQueue*& q, int& e)     /*出队*/
    {
        if (q->front == q->rear)          /*队空的情况*/
            return 0;
        q->front = (q->front + 1) % maxqueuesize;
        e = q->CarNo[q->front];
        return 1;
    }
    void DispQueue(SqQueue* q)      /*输出队中元素*/
    {
        int i;
        i = (q->front + 1) % maxqueuesize;
        printf("%d ", q->CarNo[i]);
        while ((q->rear - i + maxqueuesize) % maxqueuesize > 0)
        {
            i = (i + 1) % maxqueuesize;
            printf("%d ", q->CarNo[i]);
        }
        printf("\n");
    }
    void TopQueue(SqQueue* q)  /*展示队头元素*/
    {
        int i;
        i = (q->front + 1) % maxqueuesize;
        printf("%d ", q->CarNo[i]);
        printf("\n");
    }
};


