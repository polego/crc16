/*
 * main.c
 *
 * All rights reserved, Copyright Ogelop AB
 *
 * Created on: Feb 11, 2021
 *     Author: Niclas Wahllöf
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crc_16.h"

#define BUF_SZ 10000

void pbytes(const char* bytes, const size_t sz) {
  for (size_t i=0; i<sz; i++) {
    printf("%02hhX", *(bytes+i));
  }
  printf("\n");
}

int hex2byte(const char *s, char *out) {
  size_t sz = strlen(s);
  size_t i = 0;

  if (sz % 2) // odd length not allowed
    return -1;

  memset(out, 0, sz/2);

  while (i<sz) {
    char c = s[i];
    int val = 0;
    
    if (c >= '0' && c <= '9') {
      val = (c - '0');
    } else if (c >= 'A' && c <= 'F') {
      val = 10 + (c - 'A');
    } else if (c >= 'a' && c <= 'f') {
      val = 10 + (c - 'a');
    } else {
      return -2; // malformed
    }
    out[i/2] += val << (((i+1)%2)*4);
    i++;
  }

  return sz/2;
}

int byte2hex(const char *in, const size_t sz, char *out) {
  const char *hex = "0123456789ABCDEF";
  const char *pin = in;
  char *pout = out;
  for(; pin < in+sz; pout+=2, pin++) {
    pout[0] = hex[(*pin>>4) & 0xF];
    pout[1] = hex[*pin & 0xF];
  }
  *pout = 0;
  return 0;
}

int main(int argc, char** argv) {
  char buf[BUF_SZ];
  int len;
  uint16_t cksum;

  if ((argc == 2) && ((strlen(argv[1]) <= BUF_SZ * 2))){
      len = hex2byte(argv[1], buf);
      cksum = crc_16_reverse(buf, len);
      printf("\nChecksum = %04hX\n", cksum);
  } else {
      printf("usage %s <hex (max %i bytes)>\n", argv[0], BUF_SZ);
  }


  return 0;
}

