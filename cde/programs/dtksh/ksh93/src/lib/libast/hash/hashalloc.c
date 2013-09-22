/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: hashalloc.c /main/3 1995/11/01 17:31:52 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*         THIS IS PROPRIETARY SOURCE CODE LICENSED BY          *
*                          AT&T CORP.                          *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*                     All Rights Reserved                      *
*                                                              *
*           This software is licensed by AT&T Corp.            *
*       under the terms and conditions of the license in       *
*       http://www.research.att.com/orgs/ssr/book/reuse        *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                     gsf@research.att.com                     *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif
static const char id_hash[] = "\n@(#)hash (AT&T Bell Laboratories) 05/09/95\0\n";

#include "hashlib.h"

#if _DLL_INDIRECT_DATA && !_DLL
static Hash_info_t	hash_info_data;
Hash_info_t		hash_info = &hash_info_data;
#else
Hash_info_t		hash_info = { 0 };
#endif

/*
 * create a new hash table
 */

Hash_table_t*
hashalloc __PARAM__((Hash_table_t* ref, ...), (va_alist)) __OTORP__(va_dcl)
{ __OTORP__(Hash_table_t* ref; )
	register Hash_table_t*	tab;
	register Hash_table_t*	ret = 0;
	register int		internal;
	int			n;
	va_list			ap, vl;
	va_list			va[4];
	va_list*		vp = va;
	HASHregion		region = 0;
	__V_*			handle;

	__VA_START__(ap, ref); __OTORP__(ref = va_arg(ap, Hash_table_t* );)

	/*
	 * check for HASH_region which must be first
	 */

	n = va_arg(ap, int);
	if (!ref && n == HASH_region)
	{
		region = va_arg(ap, HASHregion);
		handle = va_arg(ap, __V_*);
		n = va_arg(ap, int);
		if (!(tab = (Hash_table_t*)(*region)(handle, NiL, sizeof(Hash_table_t), 0)))
			goto out;
		memset(tab, 0, sizeof(Hash_table_t));
	}
	else if (!(tab = newof(0, Hash_table_t, 1, 0)))
		goto out;
	tab->bucketsize = (sizeof(Hash_header_t) + sizeof(char*) - 1) / sizeof(char*);
	if (ref)
	{
		tab->flags = ref->flags & ~HASH_RESET;
		tab->root = ref->root;
		internal = HASH_INTERNAL;
	}
	else
	{
		if (region)
		{
			if (!(tab->root = (Hash_root_t*)(*region)(handle, NiL, sizeof(Hash_root_t), 0)))
				goto out;
			memset(tab->root, 0, sizeof(Hash_root_t));
		}
		else if (!(tab->root = newof(0, Hash_root_t, 1, 0)))
			goto out;
		if (!(tab->root->local = newof(0, Hash_local_t, 1, 0)))
			goto out;
		if (tab->root->local->region = region)
			tab->root->local->handle = handle;
		tab->root->meanchain = HASHMEANCHAIN;
		internal = 0;
	}
	tab->size = HASHMINSIZE;
	for (;;)
	{
		switch (n) 
		{
		case HASH_alloc:
			if (ref) goto out;
			tab->root->local->alloc = va_arg(ap, HASHalloc);
			break;
		case HASH_bucketsize:
			n = (va_arg(ap, int) + sizeof(char*) - 1) / sizeof(char*);
			if (n > UCHAR_MAX) goto out;
			if (n > tab->bucketsize) tab->bucketsize = n;
			break;
		case HASH_clear:
			tab->flags &= ~(va_arg(ap, int) & ~internal);
			break;
		case HASH_compare:
			if (ref) goto out;
			tab->root->local->compare = va_arg(ap, HASHcompare);
			break;
		case HASH_free:
			if (ref) goto out;
			tab->root->local->free = va_arg(ap, HASHfree);
			break;
		case HASH_hash:
			if (ref) goto out;
			tab->root->local->hash = va_arg(ap, HASHhash);
			break;
		case HASH_meanchain:
			if (ref) goto out;
			tab->root->meanchain = va_arg(ap, int);
			break;
		case HASH_name:
			tab->name = va_arg(ap, char*);
			break;
		case HASH_namesize:
			if (ref) goto out;
			tab->root->namesize = va_arg(ap, int);
			break;
		case HASH_region:
			goto out;
		case HASH_set:
			tab->flags |= (va_arg(ap, int) & ~internal);
			break;
		case HASH_size:
			tab->size = va_arg(ap, int);
			if (tab->size & (tab->size - 1)) tab->flags |= HASH_FIXED;
			break;
		case HASH_table:
			tab->table = va_arg(ap, Hash_bucket_t**);
			tab->flags |= HASH_STATIC;
			break;
		case HASH_va_list:
#if defined(CSRG_BASED) && defined(__i386__)
			if (vp < &va[elementsof(va)]) *vp++ = ap;
			ap = va_arg(ap, va_list);
#else
			if (vp < &va[elementsof(va)])
			{
				__va_copy( *vp, ap );
				vp++;
			}
			vl = va_arg(ap, va_list);
			__va_copy(ap, vl);
#endif
			break;
		case 0:
			if (vp > va)
			{
#if defined(CSRG_BASED) && defined(__i386__)
				ap = *--vp;
#else
				vp--;
				__va_copy( ap, *vp );
#endif
				break;
			}
			if (tab->flags & HASH_SCOPE)
			{
				if (!(tab->scope = ref)) goto out;
				ref->frozen++;
			}
			if (!tab->table)
			{
				if (region)
				{
					if (!(tab->table = (Hash_bucket_t**)(*region)(handle, NiL, sizeof(Hash_bucket_t*) * tab->size, 0)))
						goto out;
					memset(tab->table, 0, sizeof(Hash_bucket_t*) * tab->size);
				}
				else if (!(tab->table = newof(0, Hash_bucket_t*, tab->size, 0))) goto out;
			}
			if (!ref)
			{
				tab->root->flags = tab->flags & HASH_INTERNAL;
				tab->root->next = hash_info.list;
				hash_info.list = tab->root;
			}
			if (!region)
			{
				tab->next = tab->root->references;
				tab->root->references = tab;
			}
			ret = tab;
			goto out;
		default:
			goto out;
		}
		n = va_arg(ap, int);
	}
 out:
	va_end(ap);
	if (!ret) hashfree(tab);
	return(ret);
}
