#define maxstacksize 4                   /*ͣ����������ͣ����*/
template <class S>
class SqStack   //˳�����
{
public:
    int CarNo[maxstacksize];           /*���ƺ�*/
    int CarTime[maxstacksize];         /*����ʱ��*/
    int top;                /*ջָ��*/
    /*����Ϊ˳��ջ�Ļ��������㷨*/
    void InitStack(SqStack*& s)  /*��ʼ��*/
    {
        s = (SqStack*)malloc(sizeof(SqStack));
        s->top = -1;
    }
    int StackEmpty(SqStack* s)  /*��ջ��*/
    {
        return(s->top == -1);
    }
    int StackFull(SqStack* s)  /*��ջ��*/
    {
        return(s->top == maxstacksize - 1);
    }
    int Push(SqStack*& s, int e1, int e2)  /*��ջ*/
    {
        if (s->top == maxstacksize - 1)
            return 0;
        s->top++;
        s->CarNo[s->top] = e1;
        s->CarTime[s->top] = e2;
        return 1;
    }
    int Pop(SqStack*& s, int& e1, int& e2)  /*��ջ*/
    {
        if (s->top == -1)
            return 0;
        e1 = s->CarNo[s->top];
        e2 = s->CarTime[s->top];
        s->top--;
        return 1;
    }
    void DispStack(SqStack* s)  /*չʾջ*/
    {
        int i;
        for (i = s->top; i >= 0; i--)
            printf("%d ", s->CarNo[i]);
        printf("\n");
    }
    void TopStack(SqStack* s)  /*չʾջ��Ԫ��*/
    {

        printf("%d ", s->CarNo[s->top]);
        printf("\n");
    }
};

