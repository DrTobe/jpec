#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "include/jpec.h"

/* Global variables */
const char *pname;

/* Function prototypes */
int main(int argc, char **argv);
uint8_t *load_image(const char *path, int *width, int *height);

/* implementation */
int main(int argc, char** argv) {
  pname = argv[0];
  if (argc == 2) {
    int w, h;
    uint8_t *img = load_image(argv[1], &w, &h);
    jpec_enc_t *e = jpec_enc_new(img, w, h);
    int len;
    const uint8_t *jpeg = jpec_enc_run(e, &len);
    FILE *file = fopen("result.jpg", "wb");
    fwrite(jpeg, sizeof(uint8_t), len, file);
    fclose(file);
    printf("Done: result.jpg (%d bytes)\n", len);
    jpec_enc_del(e);
    free(img);
  }
  else {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  %s /path/to/img\n", pname);
    exit(1);
  }
  return 0;
}

uint8_t *load_image(const char *path, int *width, int *height) {
  assert(path);
  IplImage *img = cvLoadImage(path, 1);
  if (!img) return NULL;
  if (img->nChannels != 1) {
    IplImage *tmp = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
    cvCvtColor(img, tmp, CV_BGR2GRAY);
    cvReleaseImage(&img);
    img = tmp;
  }
  int w = img->width;
  int h = img->height;
  int bpr = img->widthStep;
  uint8_t *data = (uint8_t*)malloc(w*h*sizeof(uint8_t));
  if (w == bpr) memcpy(data, img->imageData, w*h*sizeof(uint8_t));
  else {
    for (int i = 0; i < h; ++i) {
      memcpy(data + i*w*sizeof(uint8_t), img->imageData + i*bpr*sizeof(uint8_t),
             w*sizeof(uint8_t));
    }
  }
  cvReleaseImage(&img);
  *width = w;
  *height = h;
  return data;
}
