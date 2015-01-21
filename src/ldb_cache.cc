/*
 * ldb_cache.cc
 *
 *  Created on: Dec 6, 2014
 *      Author: chenjf
 */

#include <stdlib.h>

#include "ldb_cache.h"
#include "cache.h"
#include "slice.h"

using leveldb::Cache;

extern "C" {

struct _leveldb_cache {
    Cache* rep;
};

leveldb_cache_t* leveldb_cache_create_lru(size_t capacity, size_t max_val_len)
{
    leveldb_cache_t* c = (leveldb_cache_t *)malloc(sizeof(leveldb_cache_t));
    c->rep = leveldb::NewLRUCache(capacity, max_val_len);
    return c;
}

void leveldb_cache_destroy(leveldb_cache_t* lcache)
{
    if (lcache == NULL) {
        return;
    }
    leveldb::DelLRUCache(lcache->rep);
    free(lcache);
}

bool leveldb_cache_insert(leveldb_cache_t *lcache, const char *key, size_t klen, const char *value, size_t vlen)
{
    leveldb::Slice k(key, klen);
    leveldb::Slice v(value, vlen);

    lcache->rep->Release(lcache->rep->Insert(k, v));

    return true;
}

void leveldb_cache_erase(leveldb_cache_t *lcache, const char *key, size_t klen)
{
    leveldb::Slice k(key, klen);
    lcache->rep->Erase(k);
}

void *leveldb_cache_fix(leveldb_cache_t *lcache, const char *key, size_t klen)
{
    leveldb::Slice k(key, klen);
    return lcache->rep->Lookup(k);
}

const void *leveldb_cache_value(leveldb_cache_t *lcache, void *handle, size_t *vlen)
{
    leveldb::Slice v = lcache->rep->Value((Cache::Handle*)handle);
    *vlen = v.size();
    return v.data();
}

void leveldb_cache_unfix(leveldb_cache_t *lcache, void *handle)
{
    lcache->rep->Release((Cache::Handle*)handle);
}

}

