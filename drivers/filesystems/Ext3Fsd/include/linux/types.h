#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H

typedef unsigned __int8     __u8;
typedef signed   __int8     __s8;

typedef	signed   __int16	__s16;
typedef	unsigned __int16	__u16;

typedef	signed   __int32	__s32;
typedef	unsigned __int32	__u32;

typedef	signed   __int64	__s64;
typedef	unsigned __int64	__u64;


#if 1 //#if MSC_VER
typedef __s16       s16;
typedef __u16       u16;
typedef __s32       s32;
typedef __u32       u32;
typedef __s64       s64;
typedef __u64       u64;
#endif

typedef __u16 __le16;
typedef __u32 __le32;
typedef __u64 __le64;

#define bool        BOOLEAN

typedef unsigned long       sector_t;
typedef unsigned __int64    loff_t;

//
// gcc special keyworks
//
#ifndef _REACTOS_
#define __attribute__(x)
#endif
#define __bitwise
#define __releases(x)

#ifdef _MSC_VER
#define inline __inline
#endif

typedef __u32 __bitwise __be32;
typedef __u16 __bitwise __be16;

typedef u16 uid_t;
typedef u16 gid_t;
typedef int         pid_t;
typedef unsigned __bitwise gfp_t;

typedef unsigned short umode_t; /* inode mode */

//
// bit spin lock
//

#define __acquire(x)
#define __release(x)

#define preempt_enable()
#define preempt_disable()

//
// __FUNCTION__ issue
//

#if _MSC_VER <= 1300
#define __FUNCTION__ ("jbd")
#endif


#endif /* LINUX_TYPES_H */
