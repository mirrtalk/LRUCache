/*
 * cache_test.c
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "ldb_cache.h"

#define CACHE_SIZE 1000
#define THREAD_CNT 10

void *worker(void *args)
{
    size_t i, klen, vlen;
    char key[32] = {0};
    char val[32] = {0};
    const char *v = NULL;
    void *handle = NULL;

    leveldb_cache_t *lcache = (leveldb_cache_t *)args;

    for (i = 0; i < 2*CACHE_SIZE; ++i) {
        sprintf(key, "key%ld", i);
        sprintf(val, "%s_value_%ld", key, i);
        leveldb_cache_insert(lcache, key, strlen(key), val, strlen(val));
    }

    for (i = 0; i < 2*CACHE_SIZE; ++i) {
        sprintf(key, "key%ld", i);
        klen = strlen(key);
        handle = leveldb_cache_fix(lcache, key, klen);
        if (handle != NULL) {
            v = (const char *)leveldb_cache_value(lcache, handle, &vlen);
            if (strncmp(key, v, klen) != 0) {
                printf("error. key: [%s], val: [%s]\n", key, v);
            }
            leveldb_cache_unfix(lcache, handle);
        } else {
            printf("not find key: [%s]\n", key);
        }
    }

    for (i = 0; i < 2*CACHE_SIZE; ++i) {
        sprintf(key, "key%ld", i);
        leveldb_cache_erase(lcache, key, strlen(key));
    }

    return NULL;
}


int main(void)
{
    size_t i;
    pthread_t pid[THREAD_CNT];

    /* open a cache. */
    leveldb_cache_t *lcache = leveldb_cache_create_lru(CACHE_SIZE, 32);

    /* check. */
    for (i = 0; i < THREAD_CNT; ++i) {
        if (pthread_create(&pid[i], NULL, worker, lcache) != 0) {
            perror("create thread error.\n");
        }
    }
//    worker(lcache);

    /* wait thread close. */
    for (i = 0; i < THREAD_CNT; ++i) {
        if (pthread_join(pid[i], NULL) != 0) {
            perror("create thread error.\n");
        }
    }
    /* destory the cache. */
    leveldb_cache_destroy(lcache);
    return 0;
}
