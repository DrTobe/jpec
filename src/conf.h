#ifndef JPEC_CONF_H
#define JPEC_CONF_H

/* Common headers */
#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/** Standard JPEG quantizing table */
extern const uint8_t jpec_qzr[64];

/** DCT coefficients */
extern const float jpec_dct[7];

/** Zig-zag order */
extern const int jpec_zz[64];

/** JPEG standard Huffman tables */
/** Luminance (Y) - DC */
extern const uint8_t jpec_dc_nodes[17];
extern const int jpec_dc_nb_vals;
extern const uint8_t jpec_dc_vals[12];
/** Luminance (Y) - AC */
extern const uint8_t jpec_ac_nodes[17];
extern const int jpec_ac_nb_vals;
extern const uint8_t jpec_ac_vals[162];

/** Huffman inverted tables */
/** Luminance (Y) - DC */
extern const uint8_t jpec_dc_len[12];
extern const int jpec_dc_code[12];
/** Luminance (Y) - AC */
extern const int8_t jpec_ac_len[256];
extern const int jpec_ac_code[256];

#endif
