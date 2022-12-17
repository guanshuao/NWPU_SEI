#include <cstdio>
#include <malloc.h>
#include "Stack.h"
#include "Queue.h"
#define Price 2             /*每单位时间停车费用*/
//main函数用于模拟停车场的工作
int main()
{
    printf("C程序大作业一——基于顺序栈和循环队列的停车场管理系统\n\n");
    printf("姓名:王偲怡\n");
    printf("程序操作简介：\n");
    printf("操作指南：第一步：选择环境\n\n");
    printf("1：进入顺序栈环境 2：进入循环队列环境 3.进入模拟停车场系统\n\n");
    printf("          第二步：选择操作\n\n");
    int comm1,comm;
    int no, e1, time, e2;
    int i, j, t;
    SqStack<int>* St, * St1, SS, SS1;  /*St是停车场，St1是在有车离开时要使用的临时顺序栈*/
    SqQueue<int>* Qu, Q1;   /*Qu是候车场*/
    SS.InitStack(St);
    SS1.InitStack(St1);
    Q1.InitQueue(Qu);
    do
    {
        printf("选择环境：*1:顺序栈 *2:循环队列 *3:停车场模拟\n "); 
        printf("          *0:退出\n ");
        scanf_s("%d", &comm1);
        switch (comm1)
        {
        case 1:     /*顺序栈实现*/
            do
            {
                printf("输入指令**1:入栈            2:出栈           3:显示栈中元素数值**\n"); 
                printf("        **4：取栈顶元素数值 5：判断栈空栈满  0:退出            **\n");
                
                scanf_s("%d", &comm);
                switch (comm)
                {
                case 1:

                    if (!SS.StackFull(St))         /*顺序栈不满*/
                    {
                        printf("输入入栈元素(包括两个整数：数值和时间): \n");
                        scanf_s("%d%d", &no, &time);
                        SS.Push(St, no, time);
                        printf("  >>元素位置:%d\n", St->top + 1);
                    }
                    else                        /*顺序栈满*/
                    {
                        printf("  >>顺序栈已满,不能入栈\n");
                    }
                    break;
                case 2:     /*出栈*/
                    SS1.InitStack(St1);
                    printf("输入出栈元素(包括两个整数：数值和时间): \n");
                    scanf_s("%d%d", &no, &time);
                    for (i = 0; i <= St->top && St->CarNo[i] != no; i++);  /*在栈中查找*/
                    if (i > St->top)
                        printf("  >>未找到该元素\n");
                    else
                    {
                        t = St->top - i;  /*需要出栈的元素数目*/
                        for (j = 0; j < t; j++)
                        {
                            SS.Pop(St, e1, e2);
                            SS1.Push(St1, e1, e2);        /*出栈元素放入到临时栈St1中*/
                        }
                        SS.Pop(St, e1, e2);              /*该元素出栈*/

                        while (!SS1.StackEmpty(St1))    /*将临时栈St1中元素重新回到St中*/
                        {
                            SS1.Pop(St1, e1, e2);
                            SS.Push(St, e1, e2);
                        }
                    }
                    break;
                case 3:     /*显示顺序栈中元素*/
                    if (!SS.StackEmpty(St))
                    {
                        printf("  >>顺序栈中元素数值:\n"); /*输出顺序栈中元素*/
                        SS.DispStack(St);
                    }
                    else
                        printf("  >>顺序栈中无元素\n");
                    break;
                case 4:/*取栈顶元素*/
                    if (!SS.StackEmpty(St))
                    {
                        printf("  >>顺序栈栈顶元素数值:\n"); /*输出顺序栈中栈顶元素*/
                        SS.TopStack(St);
                    }
                    else
                        printf("  >>顺序栈中无元素\n");
                    break;
                case 5:/*判断栈空栈满*/
                    if (SS.StackEmpty(St)) printf("  >>顺序栈为空\n");
                    else if (SS.StackFull(St)) printf("  >>顺序栈已满\n");
                    else printf(">>顺序栈不为空且未栈满\n");
                case 0:     /*结束*/
                    break;
                default:    /*其他情况*/
                    printf("  >>输入的命令错误\n");
                    break;
                }
            } while (comm != 0);
            break;
        case 2:     /*循环队列实现*/
            do
            {
                printf("输入指令**1:入队            2:出队              3:判断队空队满**\n ");
                printf("       **4:获取队头元素    5：显示队伍元素数值 0:退出        **\n");
                scanf_s("%d", &comm);
                switch (comm)
                {
                case 1:     /*入队*/
                    if (!Q1.QueueFull(Qu))     /*队列不满*/
                    {
                        printf("输入入队元素(包括两个整数：数值和时间): \n");
                        scanf_s("%d%d", &no, &time);
                        Q1.enQueue(Qu, no);
                        printf("  >>队列位置:%d\n", Qu->rear);
                    }
                    else
                        printf("  >>队列已满,不能入队\n");
                    break;
                case 2:     /*出队*/
                    if (!Q1.QueueEmpty(Qu))        /*队不空时,将队头进栈St*/
                        Q1.deQueue(Qu, e1);
                    else  printf("  >>队列为空,不能出队\n");
                    break;
                case 3:/*判断队空队满*/
                    if (Q1.QueueEmpty(Qu)) printf("  >>队列为空\n");
                    else if (Q1.QueueFull(Qu)) printf("  >>队列已满\n");
                    else printf(">>队列不为空且未队满\n");
                    break;
                case 4:/*获取队头元素*/
                    if (!Q1.QueueEmpty(Qu))
                    {
                        printf("  >>队头元素数值:\n"); /*输出队头元素*/
                        Q1.TopQueue(Qu);
                    }
                    else
                        printf("  >>队列中无元素\n");
                    break;
                case 5:     /*显示队列元素情况*/
                    if (!Q1.QueueEmpty(Qu))
                    {
                        printf("  >>队列的元素数值:\n"); /*输出队列元素数值*/
                        Q1.DispQueue(Qu);
                    }
                    else
                        printf("  >>队列中无元素\n");
                    break;
                case 0:     /*结束*/
                    break;
                default:    /*其他情况*/
                    printf("  >>输入的命令错误\n");
                    break;
                }
            } while (comm != 0);
            break;
        case 3:     /*停车场模拟*/
            do
            {
                printf("输入指令**1:到达        2:离开      ** \n");
                printf("        **3:显示停车场  4:显示候车场**\n");
                printf("        **0:退出**\n");
                scanf_s("%d", &comm);
                switch (comm)
                {
                case 1:     /*汽车到达*/
                    printf("输入车号和时间(设车号和时间均为整数):\n ");
                    scanf_s("%d%d", &no, &time);
                    if (!SS.StackFull(St))         /*停车场不满*/
                    {
                        SS.Push(St, no, time);
                        printf("  >>停车场位置:%d\n", St->top + 1);
                    }
                    else                        /*停车场满*/
                    {
                        if (!Q1.QueueFull(Qu))     /*候车场不满*/
                        {
                            Q1.enQueue(Qu, no);
                            printf("  >>候车场位置:%d\n", Qu->rear);
                        }
                        else
                            printf("  >>候车场已满,不能停车\n");
                    }
                    break;
                case 2:     /*汽车离开*/
                    printf("输入车号和时间(设车号和时间均为整数):\n ");
                    scanf_s("%d%d", &no, &time);
                    for (i = 0; i <= St->top && St->CarNo[i] != no; i++);  /*在栈中查找元素*/
                    if (i > St->top)
                        printf("  >>未找到该编号的汽车\n");
                    else
                    {
                        t = St->top - i;  /*需要出栈的车辆数目*/
                        for (j = 0; j < t; j++)
                        {
                            SS.Pop(St, e1, e2);
                            SS1.Push(St1, e1, e2);       /*倒车到临时栈St1中*/
                        }
                        SS.Pop(St, e1, e2);             /* 该汽车离开*/
                        printf("  >>汽车停车时间:%d 汽车停车费用:%d\n", (time - e2), (time - e2) * Price);
                        while (!SS1.StackEmpty(St1))    /*将临时栈St1重新回到St中*/
                        {
                            SS1.Pop(St1, e1, e2);
                            SS.Push(St, e1, e2);
                        }
                        if (!Q1.QueueEmpty(Qu))        /*队不空时,队头进栈St，候车场队头车进入停车场*/
                        {
                            Q1.deQueue(Qu, e1);
                            SS.Push(St, e1, time);     /*更新计费时间*/
                        }
                    }
                    break;
                case 3:     /*显示停车场情况*/
                    if (!SS.StackEmpty(St))
                    {
                        printf("  >>停车场中的车辆:\n"); /*输出停车场中的车辆*/
                        SS.DispStack(St);
                    }
                    else
                        printf("  >>停车场中无车辆\n");
                    break;
                case 4:     /*显示候车场情况*/
                    if (!Q1.QueueEmpty(Qu))
                    {
                        printf("  >>候车场中的车辆:\n"); /*输出候车场中的车辆*/
                        Q1.DispQueue(Qu);
                    }
                    else
                        printf("  >>候车场中无车辆\n");
                    break;
                case 0:     /*结束*/
                    break;
                default:    /*其他情况*/
                    printf("  >>输入命令错误\n");
                    break;
                }
            } while (comm != 0);
            break;
        case 0:     /*结束*/
            break;
        default:    /*其他情况*/
            printf("  >>输入命令错误\n");
            break;
        }
    } while (comm1 != 0);
    return 0;
}
   
