#ifndef __ATOMIC_H__
#define __ATOMIC_H__


#define atomic_add(v, n)	__sync_fetch_and_add(v, n)
#define atomic_sub(v, n)	__sync_fetch_and_sub(v, n)
#define atomic_get(vp)		__sync_fetch_and_add(vp, 0)
#define atomic_inc(v)		atomic_add(v, 1)
#define atomic_dec(v)		atomic_sub(v, 1)


#endif

