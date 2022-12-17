#define maxqueuesize 6                    /*�򳵳�������ͣ������һ*/
template <class Q>
class SqQueue   //ѭ��������
{
public:

    int CarNo[maxqueuesize];           /*���ƺ�*/
    int front, rear;         /*���׺Ͷ�βָ��*/
                             /*����Ϊѭ�����еĻ��������㷨*/
    void InitQueue(SqQueue*& q)/*��ʼ��ѭ������*/
    {
        q = (SqQueue*)malloc(sizeof(SqQueue));
        q->front = q->rear = 0;
    }
    int QueueEmpty(SqQueue* q)
    {
        return(q->front == q->rear);
    }
    int QueueFull(SqQueue* q)       /*�ж϶���*/
    {
        return ((q->rear + 1) % maxqueuesize == q->front);
    }
    int enQueue(SqQueue*& q, int e)      /*����*/
    {
        if ((q->rear + 1) % maxqueuesize == q->front)    /*����*/
            return 0;
        q->rear = (q->rear + 1) % maxqueuesize;
        q->CarNo[q->rear] = e;
        return 1;
    }
    int deQueue(SqQueue*& q, int& e)     /*����*/
    {
        if (q->front == q->rear)          /*�ӿյ����*/
            return 0;
        q->front = (q->front + 1) % maxqueuesize;
        e = q->CarNo[q->front];
        return 1;
    }
    void DispQueue(SqQueue* q)      /*�������Ԫ��*/
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
    void TopQueue(SqQueue* q)  /*չʾ��ͷԪ��*/
    {
        int i;
        i = (q->front + 1) % maxqueuesize;
        printf("%d ", q->CarNo[i]);
        printf("\n");
    }
};


