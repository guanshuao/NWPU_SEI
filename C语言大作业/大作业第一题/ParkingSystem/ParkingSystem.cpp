#include <cstdio>
#include <malloc.h>
#include "Stack.h"
#include "Queue.h"
#define Price 2             /*ÿ��λʱ��ͣ������*/
//main��������ģ��ͣ�����Ĺ���
int main()
{
    printf("C�������ҵһ��������˳��ջ��ѭ�����е�ͣ��������ϵͳ\n\n");
    printf("����:������\n");
    printf("���������飺\n");
    printf("����ָ�ϣ���һ����ѡ�񻷾�\n\n");
    printf("1������˳��ջ���� 2������ѭ�����л��� 3.����ģ��ͣ����ϵͳ\n\n");
    printf("          �ڶ�����ѡ�����\n\n");
    int comm1,comm;
    int no, e1, time, e2;
    int i, j, t;
    SqStack<int>* St, * St1, SS, SS1;  /*St��ͣ������St1�����г��뿪ʱҪʹ�õ���ʱ˳��ջ*/
    SqQueue<int>* Qu, Q1;   /*Qu�Ǻ򳵳�*/
    SS.InitStack(St);
    SS1.InitStack(St1);
    Q1.InitQueue(Qu);
    do
    {
        printf("ѡ�񻷾���*1:˳��ջ *2:ѭ������ *3:ͣ����ģ��\n "); 
        printf("          *0:�˳�\n ");
        scanf_s("%d", &comm1);
        switch (comm1)
        {
        case 1:     /*˳��ջʵ��*/
            do
            {
                printf("����ָ��**1:��ջ            2:��ջ           3:��ʾջ��Ԫ����ֵ**\n"); 
                printf("        **4��ȡջ��Ԫ����ֵ 5���ж�ջ��ջ��  0:�˳�            **\n");
                
                scanf_s("%d", &comm);
                switch (comm)
                {
                case 1:

                    if (!SS.StackFull(St))         /*˳��ջ����*/
                    {
                        printf("������ջԪ��(����������������ֵ��ʱ��): \n");
                        scanf_s("%d%d", &no, &time);
                        SS.Push(St, no, time);
                        printf("  >>Ԫ��λ��:%d\n", St->top + 1);
                    }
                    else                        /*˳��ջ��*/
                    {
                        printf("  >>˳��ջ����,������ջ\n");
                    }
                    break;
                case 2:     /*��ջ*/
                    SS1.InitStack(St1);
                    printf("�����ջԪ��(����������������ֵ��ʱ��): \n");
                    scanf_s("%d%d", &no, &time);
                    for (i = 0; i <= St->top && St->CarNo[i] != no; i++);  /*��ջ�в���*/
                    if (i > St->top)
                        printf("  >>δ�ҵ���Ԫ��\n");
                    else
                    {
                        t = St->top - i;  /*��Ҫ��ջ��Ԫ����Ŀ*/
                        for (j = 0; j < t; j++)
                        {
                            SS.Pop(St, e1, e2);
                            SS1.Push(St1, e1, e2);        /*��ջԪ�ط��뵽��ʱջSt1��*/
                        }
                        SS.Pop(St, e1, e2);              /*��Ԫ�س�ջ*/

                        while (!SS1.StackEmpty(St1))    /*����ʱջSt1��Ԫ�����»ص�St��*/
                        {
                            SS1.Pop(St1, e1, e2);
                            SS.Push(St, e1, e2);
                        }
                    }
                    break;
                case 3:     /*��ʾ˳��ջ��Ԫ��*/
                    if (!SS.StackEmpty(St))
                    {
                        printf("  >>˳��ջ��Ԫ����ֵ:\n"); /*���˳��ջ��Ԫ��*/
                        SS.DispStack(St);
                    }
                    else
                        printf("  >>˳��ջ����Ԫ��\n");
                    break;
                case 4:/*ȡջ��Ԫ��*/
                    if (!SS.StackEmpty(St))
                    {
                        printf("  >>˳��ջջ��Ԫ����ֵ:\n"); /*���˳��ջ��ջ��Ԫ��*/
                        SS.TopStack(St);
                    }
                    else
                        printf("  >>˳��ջ����Ԫ��\n");
                    break;
                case 5:/*�ж�ջ��ջ��*/
                    if (SS.StackEmpty(St)) printf("  >>˳��ջΪ��\n");
                    else if (SS.StackFull(St)) printf("  >>˳��ջ����\n");
                    else printf(">>˳��ջ��Ϊ����δջ��\n");
                case 0:     /*����*/
                    break;
                default:    /*�������*/
                    printf("  >>������������\n");
                    break;
                }
            } while (comm != 0);
            break;
        case 2:     /*ѭ������ʵ��*/
            do
            {
                printf("����ָ��**1:���            2:����              3:�ж϶ӿն���**\n ");
                printf("       **4:��ȡ��ͷԪ��    5����ʾ����Ԫ����ֵ 0:�˳�        **\n");
                scanf_s("%d", &comm);
                switch (comm)
                {
                case 1:     /*���*/
                    if (!Q1.QueueFull(Qu))     /*���в���*/
                    {
                        printf("�������Ԫ��(����������������ֵ��ʱ��): \n");
                        scanf_s("%d%d", &no, &time);
                        Q1.enQueue(Qu, no);
                        printf("  >>����λ��:%d\n", Qu->rear);
                    }
                    else
                        printf("  >>��������,�������\n");
                    break;
                case 2:     /*����*/
                    if (!Q1.QueueEmpty(Qu))        /*�Ӳ���ʱ,����ͷ��ջSt*/
                        Q1.deQueue(Qu, e1);
                    else  printf("  >>����Ϊ��,���ܳ���\n");
                    break;
                case 3:/*�ж϶ӿն���*/
                    if (Q1.QueueEmpty(Qu)) printf("  >>����Ϊ��\n");
                    else if (Q1.QueueFull(Qu)) printf("  >>��������\n");
                    else printf(">>���в�Ϊ����δ����\n");
                    break;
                case 4:/*��ȡ��ͷԪ��*/
                    if (!Q1.QueueEmpty(Qu))
                    {
                        printf("  >>��ͷԪ����ֵ:\n"); /*�����ͷԪ��*/
                        Q1.TopQueue(Qu);
                    }
                    else
                        printf("  >>��������Ԫ��\n");
                    break;
                case 5:     /*��ʾ����Ԫ�����*/
                    if (!Q1.QueueEmpty(Qu))
                    {
                        printf("  >>���е�Ԫ����ֵ:\n"); /*�������Ԫ����ֵ*/
                        Q1.DispQueue(Qu);
                    }
                    else
                        printf("  >>��������Ԫ��\n");
                    break;
                case 0:     /*����*/
                    break;
                default:    /*�������*/
                    printf("  >>������������\n");
                    break;
                }
            } while (comm != 0);
            break;
        case 3:     /*ͣ����ģ��*/
            do
            {
                printf("����ָ��**1:����        2:�뿪      ** \n");
                printf("        **3:��ʾͣ����  4:��ʾ�򳵳�**\n");
                printf("        **0:�˳�**\n");
                scanf_s("%d", &comm);
                switch (comm)
                {
                case 1:     /*��������*/
                    printf("���복�ź�ʱ��(�賵�ź�ʱ���Ϊ����):\n ");
                    scanf_s("%d%d", &no, &time);
                    if (!SS.StackFull(St))         /*ͣ��������*/
                    {
                        SS.Push(St, no, time);
                        printf("  >>ͣ����λ��:%d\n", St->top + 1);
                    }
                    else                        /*ͣ������*/
                    {
                        if (!Q1.QueueFull(Qu))     /*�򳵳�����*/
                        {
                            Q1.enQueue(Qu, no);
                            printf("  >>�򳵳�λ��:%d\n", Qu->rear);
                        }
                        else
                            printf("  >>�򳵳�����,����ͣ��\n");
                    }
                    break;
                case 2:     /*�����뿪*/
                    printf("���복�ź�ʱ��(�賵�ź�ʱ���Ϊ����):\n ");
                    scanf_s("%d%d", &no, &time);
                    for (i = 0; i <= St->top && St->CarNo[i] != no; i++);  /*��ջ�в���Ԫ��*/
                    if (i > St->top)
                        printf("  >>δ�ҵ��ñ�ŵ�����\n");
                    else
                    {
                        t = St->top - i;  /*��Ҫ��ջ�ĳ�����Ŀ*/
                        for (j = 0; j < t; j++)
                        {
                            SS.Pop(St, e1, e2);
                            SS1.Push(St1, e1, e2);       /*��������ʱջSt1��*/
                        }
                        SS.Pop(St, e1, e2);             /* �������뿪*/
                        printf("  >>����ͣ��ʱ��:%d ����ͣ������:%d\n", (time - e2), (time - e2) * Price);
                        while (!SS1.StackEmpty(St1))    /*����ʱջSt1���»ص�St��*/
                        {
                            SS1.Pop(St1, e1, e2);
                            SS.Push(St, e1, e2);
                        }
                        if (!Q1.QueueEmpty(Qu))        /*�Ӳ���ʱ,��ͷ��ջSt���򳵳���ͷ������ͣ����*/
                        {
                            Q1.deQueue(Qu, e1);
                            SS.Push(St, e1, time);     /*���¼Ʒ�ʱ��*/
                        }
                    }
                    break;
                case 3:     /*��ʾͣ�������*/
                    if (!SS.StackEmpty(St))
                    {
                        printf("  >>ͣ�����еĳ���:\n"); /*���ͣ�����еĳ���*/
                        SS.DispStack(St);
                    }
                    else
                        printf("  >>ͣ�������޳���\n");
                    break;
                case 4:     /*��ʾ�򳵳����*/
                    if (!Q1.QueueEmpty(Qu))
                    {
                        printf("  >>�򳵳��еĳ���:\n"); /*����򳵳��еĳ���*/
                        Q1.DispQueue(Qu);
                    }
                    else
                        printf("  >>�򳵳����޳���\n");
                    break;
                case 0:     /*����*/
                    break;
                default:    /*�������*/
                    printf("  >>�����������\n");
                    break;
                }
            } while (comm != 0);
            break;
        case 0:     /*����*/
            break;
        default:    /*�������*/
            printf("  >>�����������\n");
            break;
        }
    } while (comm1 != 0);
    return 0;
}
   
