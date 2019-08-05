#ifndef JPEC_HUFFMAN_H
#define JPEC_HUFFMAN_H

#include <stdint.h>

//#include <jpec.h>
#include "buf.h"

/** Entropy coding data that hold state along blocks */
typedef struct jpec_huff_state_t_ {
  int32_t buffer;             /* bits buffer */
  int nbits;                  /* number of bits remaining in buffer */
  int dc;                     /* DC coefficient from previous block (or 0) */
  jpec_buffer_t *buf;         /* JPEG global buffer */
} jpec_huff_state_t;

/** Type of an Huffman JPEG encoder */
/*
typedef struct jpec_huff_t_ {
  jpec_huff_state_t state;    // state from previous block encoding *
} jpec_huff_t;
*/

/** Skeleton initialization */
//void jpec_huff_skel_init(jpec_huff_skel_t *skel);

//jpec_huff_t *jpec_huff_new(void);

//void jpec_huff_del(jpec_huff_t *h);

void jpec_huff_init(jpec_huff_state_t *h);
void jpec_huff_finish(jpec_huff_state_t *h);
void jpec_huff_encode_block(jpec_huff_state_t *s, jpec_buffer_t *buf, int zz[], int zz_len);

#endif
