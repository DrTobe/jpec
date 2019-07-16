#ifndef JPEC_H
#define JPEC_H

#include <stdint.h>

/*************************************************
 * JPEG Encoder
 *************************************************/

/* -------------------------------------------------
 * LIMITATIONS
 * -------------------------------------------------
 * - Grayscale *only* (monochrome JPEG file): no support for color
 * - Baseline DCT-based  (SOF0), JFIF 1.01 (APP0) JPEG
 * - Block size of 8x8 pixels *only*
 * - Default quantization and Huffman tables *only*
 * - No border filling support: the input image *MUST* represent an integer
 *   number of blocks, i.e. each dimension must be a multiple of 8
 */

/** Type of a JPEG encoder object */
typedef struct jpec_enc_t_ jpec_enc_t;

/*
 * Create a JPEG encoder with default quality factor
 * `img' specifies the pointer to aligned image data.
 * `w' specifies the image width in pixels.
 * `h' specifies the image height in pixels.
 * Because the returned encoder is allocated by this function, it should be
 * released with the `jpec_enc_del' call when it is no longer useful.
 * Note: for efficiency the image data is *NOT* copied and the encoder just
 * retains a pointer to it. Thus the image data must not be deleted
 * nor change until the encoder object gets deleted.
 */
jpec_enc_t *jpec_enc_new(const uint8_t *img, uint16_t w, uint16_t h);
/*
 * `q` specifies the JPEG quality factor in 0..100
 */
jpec_enc_t *jpec_enc_new2(const uint8_t *img, uint16_t w, uint16_t h, int q);

/*
 * Release a JPEG encoder object
 * `e` specifies the encoder object
 */
void jpec_enc_del(jpec_enc_t *e);

/*
 * Run the JPEG encoding
 * `e` specifies the encoder object
 * `len` specifies the pointer to the variable into which the length of the
 * JPEG blob is assigned
 * If successful, the return value is the pointer to the JPEG blob. `NULL` is
 * returned if an error occurred.
 * Note: the caller should take care to copy or save the JPEG blob before
 * calling `jpec_enc_del` since the blob will no longer be maintained after.
 */
const uint8_t *jpec_enc_run(jpec_enc_t *e, int *len);

int jpec_enc_start(jpec_enc_t *e); // Returns the header length
void jpec_enc_run_segment(jpec_enc_t *e, uint8_t const *segment_data);
const uint8_t *jpec_enc_finish(jpec_enc_t *e, int *len);

#endif
