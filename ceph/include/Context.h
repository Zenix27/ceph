// -*- mode:C++; tab-width:4; c-basic-offset:2; indent-tabs-mode:t -*- 
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */


#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "config.h"

#include <list>
#include <iostream>
using namespace std;


/*
 * Context - abstract callback class
 */
class Context {
 public:
  virtual ~Context() {}       // we want a virtual destructor!!!
  virtual void finish(int r) = 0;
};


/*
 * finish and destroy a list of Contexts
 */
inline void finish_contexts(list<Context*>& finished, 
							int result = 0)
{
  if (finished.empty()) return;

  dout(10) << finished.size() << " contexts to finish with " << result << endl;
  for (list<Context*>::iterator it = finished.begin(); 
	   it != finished.end(); 
	   it++) {
	Context *c = *it;
	dout(10) << "---- " << c << endl;
	c->finish(result);
	delete c;
  }
}

/*
 * C_Contexts - set of Contexts
 */
class C_Contexts : public Context {
  list<Context*> clist;
  
public:
  void add(Context* c) {
	clist.push_back(c);
  }
  void take(list<Context*>& ls) {
	clist.splice(clist.end(), ls);
  }
  void finish(int r) {
	finish_contexts(clist, r);
  }
};


#endif
