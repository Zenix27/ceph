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


#ifndef __MRENAMENOTIFYACK_H
#define __MRENAMENOTIFYACK_H

class MRenameNotifyAck : public Message {
  inodeno_t ino;

 public:
  inodeno_t get_ino() { return ino; }

  MRenameNotifyAck() {}
  MRenameNotifyAck(inodeno_t ino) :
	Message(MSG_MDS_RENAMENOTIFYACK) {
	this->ino = ino;
  }
  virtual char *get_type_name() { return "RnotA";}
  
  virtual void decode_payload(crope& s, int& off) {
	s.copy(off, sizeof(ino), (char*)&ino);
	off += sizeof(ino);
  }
  virtual void encode_payload(crope& s) {
	s.append((char*)&ino,sizeof(ino));
  }
};

#endif
