#include <stdlib.h>
//#include <errno.h>
#include <stdio.h>
//#include <string.h>

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
    dequef* new;
    new = malloc(sizeof(dequef));
    if (!new) return NULL;
    new->data = malloc(capacity * sizeof(float));
    new->first = 0;
    new->size = 0;
    new->cap = capacity;
    new->mincap = capacity;
    new->factor = factor;

    return new;
}



/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
    free(D->data);
    free(D);
}



/**
   The size of the deque.
**/
long df_size(dequef* D) {
    return D->size;
}

// da realloc em uma lista circular
int realloc_data(dequef* D, size_t size) {
    float* temp = malloc(size);
    if (!temp) return 0;
    for (int i = 0; i < D->size; i ++) {
        temp[i] = D->data[(i+D->first) % D->cap];
    }
    free(D->data);
    D->data = temp;
    D->first = 0;
    int cap = size / sizeof(float);
    D->cap = cap;
    return 1;
}

/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
    if(D->size == D->cap) {
        if (!realloc_data(D, D->cap * D->factor * sizeof(float))) return 0;
    }
    D->data[(D->first + D->size) % D->cap] = x;
    D->size ++;
    return 1;
}

/**
   Remove a float from the end of D and return it.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_pop(dequef* D) {
    if (D->size == 0) return 0;
    int new_cap = (D->cap / (D->factor));
    if ((D->size - 1) <= new_cap/D->factor && D->cap > D->mincap) {
        if (!realloc_data(D, new_cap * sizeof(float))) return 0;
    }
    D->size --;
    return D->data[(D->first + D->size) % D-> cap];
}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
    if(D->size == D->cap) {
        if (!realloc_data(D, D->cap * D->factor * sizeof(float))) return 0;
    }
    D->data[(D->first + D->cap - 1) % D->cap] = x;
    D->first = (D->first + D->cap - 1) % D->cap;
    D->size ++;
    return 1;
}



/**
   Remove a float from the beginning of D and return it.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?
**/
float df_eject(dequef* D) {
    if (D->size == 0) return 0;
    int new_cap = (D->cap / (D->factor));
    if ((D->size - 1) <= new_cap/D->factor && D->cap > D->mincap) {
        if (!realloc_data(D, new_cap * sizeof(float))) return 0;
    }
    D->size --;
    float ret = D->data[D->first];
    D->first = (D->first + 1) % D->cap;
    return ret;
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?
**/
float df_get(dequef* D, long i) {
    return D->data[(D->first + i) % D->cap];
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?
**/
void df_set(dequef* D, long i, float x) {
    D->data[(D->first + i) % D->cap] = x;
}



/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
    printf("deque (%ld): ", D->size);
    for (int i = 0; i < D->size; i ++){
        printf("%.1f ", D->data[(i + D->first) % D->cap]);
    }
    printf("\n");
}
