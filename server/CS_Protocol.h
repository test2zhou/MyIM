#ifndef __CS_PTOTOCOL_H__
#define __CS_PTOTOCOL_H__


#define CS_VERSION 0x01

#define ST_LOGIN 0x0001
#define PT_LOGIN 0x0002


#define SAFE_DELETE(p) if (p) {delete p; p = nullptr;}


#endif//__CS_PTOTOCOL_H__