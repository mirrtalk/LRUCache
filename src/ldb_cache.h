/*
 * ldb_cache.h
 *
 *  Created on: Dec 6, 2014
 *      Author: chenjf
 */


#ifndef STORAGE_LEVELDB_INCLUDE_C_H_
#define STORAGE_LEVELDB_INCLUDE_C_H_


#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _leveldb_cache      leveldb_cache_t;

/*
 * create a LRU cache.
 */
extern leveldb_cache_t* leveldb_cache_create_lru(size_t capacity, size_t max_val_len);

/*
 * destroy the LRU cache.
 */
extern void leveldb_cache_destroy(leveldb_cache_t* lcache);

/*
 * insert key/value into cache.
 */
extern bool leveldb_cache_insert(leveldb_cache_t *lcache, const char *key, size_t klen, const char *value, size_t vlen);

/*
 * erase key/value from cache.
 */
extern void leveldb_cache_erase(leveldb_cache_t *lcache, const char *key, size_t klen);

/*
 * fix.
 */
extern void *leveldb_cache_fix(leveldb_cache_t *lcache, const char *key, size_t klen);

/*
 * get value by handle.
 */
extern const void *leveldb_cache_value(leveldb_cache_t *lcache, void *handle, size_t *vlen);

/*
 * unfix.
 */
extern void leveldb_cache_unfix(leveldb_cache_t *lcache, void *handle);


#ifdef __cplusplus
}
#endif

#endif
