#include "genericsorts.h"

void* mg(void *vet, int s, int mid, int e, size_t typesize, int (*comparefn)(const void*, const void*))
{
    int len1 = mid - s + 1;
    int len2 = e - mid;
    /* Using char* to be able to manipulate elements from the vector (that now is void*).
       We use memcpy and pointer arith to copy elements from the vector.
       The use of char* fits nicely because char is one byte long, so if we're working, for example, with int values.
       We know we must increment the array by 4 bytes to get to the next position.
       That's why we use char*, so that arr += 4 increments the address in four bytes.
       OBS: We could probably use our void* to perform these operations, but it isn't complient with C Standard,
       the Standard is to use char* to perform these operations. */
    char *arr = (char *)vet;
    char arr1[len1 * typesize];
    char arr2[len2 * typesize];
    void *ret = NULL;
    /* Constructing the aux arrays. */
    for (int x = 0; x < len1; x++)
    {
        ret = memcpy((void*)(arr1 + x * typesize), (void*)(arr + (s + x) * typesize), typesize);
        if (ret == NULL)
            return NULL;

    }
    for (int x = 0; x < len2; x++)
    {
        ret = memcpy((void*)(arr2 + x * typesize), (void*)(arr + (mid + 1 + x) * typesize), typesize);
        if (ret == NULL)
            return NULL;
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = s;

    while (i < len1 && j < len2)
    {
        /* We use these void ptrs to make use of our comparefn function*/
        void *elem1;
        void *elem2;
        elem1 = (void *)(arr1 + i * typesize);
        elem2 = (void *)(arr2 + j * typesize);
        if (comparefn(elem1, elem2))
        {
            ret = memcpy((void*)(arr + k * typesize), arr1 + i * typesize, typesize);
            if (ret == NULL)
                return NULL;
            ++i;
        }
        else
        {
            ret = memcpy((void*)(arr + k * typesize), arr2 + j * typesize, typesize);
            if (ret == NULL)
                return NULL;
            ++j;
        }
        ++k;
    }
    while (i < len1)
    {
        ret = memcpy(arr + k * typesize, (void*)(arr1 + i * typesize), typesize);
        if (ret == NULL)
            return NULL;
        ++i;
        ++k;
    }
    while (j < len2)
    {
        ret = memcpy(arr + k * typesize, (void*)(arr2 + j * typesize), typesize);
        if (ret == NULL)
            return NULL;
        ++j;
        ++k;
    }
    return vet;
}



void* ms(void *vet, int s, int e, size_t typesize,int (*comparefn)(const void*, const void*))
{
    if (s >= e)
    {
        return vet;
    }

    int mid = (s + e) / 2;
    void* ret = NULL;

    ret = ms(vet, s, mid, typesize,comparefn);
    if (ret == NULL)
        return NULL;

    ret = ms(vet, mid + 1, e, typesize,comparefn);
    if (ret == NULL)
        return NULL;

    ret = mg(vet, s, mid, e, typesize, comparefn);
    if (ret == NULL)
        return NULL;

    return vet;
}

void* mergesort(void *base, size_t nelem, size_t typesize, int (*comparefn)(const void*, const void*))
{
    if (base == NULL || nelem <= 0 || typesize <= 0)
        return NULL;
    
    void* ret = NULL;
    
    ret = ms(base, 0, nelem - 1, typesize, comparefn);
    if (ret == NULL)
        return NULL;

    return base;

}