#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef int DqItem;
typedef struct _item* Item;
typedef struct _deque* Deque;

Deque dq_create();

void dq_push_back(Deque deque, DqItem data);
void dq_push_front(Deque deque, DqItem data);

DqItem dq_pop_back(Deque deque);
DqItem dq_pop_front(Deque deque);

void dq_print(Deque deque);
void is_empty(Deque deque);
void dq_destroy (Deque deque);
int dq_size(Deque deque);

Deque linear_choose_rise(Deque deque);
Deque linear_rise_sort(Deque deque);

#endif