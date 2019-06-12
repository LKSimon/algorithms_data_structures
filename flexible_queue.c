#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void *(*handler)(void *);

typedef struct node_s {
    //void          *(*handler_ptr)(void *);
    handler       handler_ptr;
    void          *arg;
    struct node_s *next;
} node_t;

typedef struct queue_s {
    node_t *head;
    node_t *tail;
} queue_t;

typedef enum {
    QUEUE_OK = 0,
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_ERROR,
} queue_error_t;

queue_t       *queue_init();
queue_error_t  queue_enqueue(queue_t *queue, handler h, void *arg);
queue_error_t  queue_dequeue(queue_t *queue, handler *h, void *arg);//出队时销毁队列该节点。
void           queue_release(queue_t *queue);

queue_t *
queue_init()
{
    queue_t *queue;

    queue = (queue_t *)malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }

    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

queue_error_t
queue_enqueue(queue_t *queue, handler h, void *arg)//入队时移动tail指针。
{
    node_t *node = NULL;

    if (queue == NULL) {
        return QUEUE_EMPTY;
    }

    node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL) {
        return QUEUE_FULL;
    }
    node->handler_ptr = h;
    node->arg = arg;
    node->next = NULL;

    //enqueue.tail指针始终指向最后一个节点。
    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }

    return QUEUE_OK;
}

queue_error_t
queue_dequeue(queue_t *queue, handler *h, void *arg)//出队时移动head指针
{
    node_t *node;

    if (queue == NULL || queue->head == NULL) {
        return QUEUE_EMPTY;
    }

    node = queue->head;
    *h = node->handler_ptr;
    arg = node->arg;
    queue->head = node->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }//head指针指向null时，以处理完最后一个元素，此时tail指针需释放；

    free(node);//节点信息已通过函数参数返回，此时需释放该节点内存；

    return QUEUE_OK;
}

void
queue_release(queue_t *queue)
{
    node_t *node;

    if (queue == NULL) {
        return;
    } 

    for (; queue->head != NULL; ) {
        node = queue->head;
        queue->head = node->next;
        free(node);
    }
}


/*
 *通过单项链表实现队列， head指向队列头， tail指向队列尾部， head = NULL时，队列空；
 */


void *
func(void *arg)
{
    time_t t;

    time(&t);
    printf("%s\n", asctime(localtime(&t)));

    return ((void *)0);
}


int
main()
{
    int i;
    queue_t *q = NULL;
    handler h;
    void *arg1;

    q = queue_init();
    for (i = 0; i < 3; i++) {
        queue_enqueue(q, func, NULL);
    }
    
    for (i = 0; i < 3; i++) {
        queue_dequeue(q, &h, arg1);
        h(arg1);
    }

    return 0;
}
