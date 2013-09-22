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
/*
 * $XConsortium: WXmOpButton.h /main/3 1996/06/11 16:46:56 cde-hal $
 *
 * Copyright (c) 1991 HaL Computer Systems, Inc.  All rights reserved.
 * UNPUBLISHED -- rights reserved under the Copyright Laws of the United
 * States.  Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 * 
 * This software contains confidential information and trade secrets of HaL
 * Computer Systems, Inc.  Use, disclosure, or reproduction is prohibited
 * without the prior express written permission of HaL Computer Systems, Inc.
 * 
 *                         RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions as set forth in subparagraph (c)(l)(ii) of the Rights in
 * Technical Data and Computer Software clause at DFARS 252.227-7013.
 *                        HaL Computer Systems, Inc.
 *                  1315 Dell Avenue, Campbell, CA  95008
 * 
 */

#ifndef _WXmOpButton_h
#define _WXmOpButton_h

#include "../config.h"
#include <WWL/WXmPushButton.h>

class PRoot;

typedef bool (*is_sensitive_func_t) (PRoot *root, long position);
typedef void (*insert_op_func_t) (PRoot *root, long position);

class WXmOpButton : public WWL, public WXmPushButton {
public:
  WXmOpButton (WComposite &father, const char *name,
	       PRoot *&root, long &position,
	       is_sensitive_func_t sfunc, insert_op_func_t ifunc);

  void set_sensitive ();

protected:
  void insert_op (WCallback *wcb);

  PRoot               *&f_root;
  long                 &f_position;
  is_sensitive_func_t   f_is_sensitive;
  insert_op_func_t      f_insert;
  bool	               f_sensitive;
};

#endif /* _WXmOpButton_h */
/* DO NOT ADD ANY LINES AFTER THIS #endif */
