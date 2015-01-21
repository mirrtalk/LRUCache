liblrucache
-----------

##Features
* based on leveldb lru cache
* thread safe
* max key size: 64 (can modify cache.h:KEY_MAX_SIZE by yourself)
* support unfixed length value and fixed length value

##Usage
```
        // create cache.
        // leveldb_cache_t *lcache = leveldb_cache_create_lru(10000, -1);       // unfixed length value.
        leveldb_cache_t *lcache = leveldb_cache_create_lru(10000, 32);          // fixed length value.

        // insert entry.
        leveldb_cache_insert(lcache, "key", strlen("key"), "value", strlen("value"));

        // fix entry.
        void *handle = leveldb_cache_fix(lcache, "key", strlen("key"));

        // get value.
        size_t vlen = 0;
        char *v = leveldb_cache_value(lcache, handle, &vlen);

        // unfix entry.
        leveldb_cache_unfix(lcache, handle);

        // erase entry.
        leveldb_cache_erase(lcache, "key", strlen("key"));

        // destory cache.
        leveldb_cache_destroy(lcache);
```

##Connect
* chenjianfei@daoke.me

##Date
* 2014/12/15
