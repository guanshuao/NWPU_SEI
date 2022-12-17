#define maxstacksize 4                   /*停车场内最多的停车数*/
template <class S>
class SqStack   //顺序表类
{
public:
    int CarNo[maxstacksize];           /*车牌号*/
    int CarTime[maxstacksize];         /*进场时间*/
    int top;                /*栈指针*/
    /*以下为顺序栈的基本运算算法*/
    void InitStack(SqStack*& s)  /*初始化*/
    {
        s = (SqStack*)malloc(sizeof(SqStack));
        s->top = -1;
    }
    int StackEmpty(SqStack* s)  /*测栈空*/
    {
        return(s->top == -1);
    }
    int StackFull(SqStack* s)  /*测栈满*/
    {
        return(s->top == maxstacksize - 1);
    }
    int Push(SqStack*& s, int e1, int e2)  /*入栈*/
    {
        if (s->top == maxstacksize - 1)
            return 0;
        s->top++;
        s->CarNo[s->top] = e1;
        s->CarTime[s->top] = e2;
        return 1;
    }
    int Pop(SqStack*& s, int& e1, int& e2)  /*出栈*/
    {
        if (s->top == -1)
            return 0;
        e1 = s->CarNo[s->top];
        e2 = s->CarTime[s->top];
        s->top--;
        return 1;
    }
    void DispStack(SqStack* s)  /*展示栈*/
    {
        int i;
        for (i = s->top; i >= 0; i--)
            printf("%d ", s->CarNo[i]);
        printf("\n");
    }
    void TopStack(SqStack* s)  /*展示栈顶元素*/
    {

        printf("%d ", s->CarNo[s->top]);
        printf("\n");
    }
};

