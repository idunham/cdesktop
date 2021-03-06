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
/* $XConsortium: doc_test.h /main/4 1996/07/18 16:32:48 drk $ */

#ifndef _doc_test_h
#define _doc_test_h

#ifdef REGRESSION_TEST

#include "oliasdb/doc_hd.h"
#include "object/random_gen.h"

void print_doc(doc_smart_ptr& x, ostream& out, Boolean out_it_oid, 
		Boolean out_tag_list);

int compare_doc(doc_smart_ptr& pattern, info_base* base_ptr);

void generate_doc_instance(random_gen&, ostream& out, int seq_num, int min_tabs = 1, int max_tabs = 20);
#endif


#endif
