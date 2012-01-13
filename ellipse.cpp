#include <cv.h>
#include <highgui.h>
#include <stdio.h>

#include "utils.h"

const int factor = 16;
const int trackNum = 16;
int ellipseW, ellipseH;
unsigned char *mask;
int num;

int if_in_ellipse(int sizeW, int sizeH) {
    float val1 = sizeW / (float)ellipseW;
    float val2 = sizeH / (float)ellipseH;

    if (val1 * val1 + val2 * val2 <= 1) {
        return 1;
    } else {
        return 0;
    }
}

int abs(int x) {
    return x > 0 ? x : -x;
}

void init_mask(int w, int h) {
    int ctrX = w / 2;
    int ctrY = h / 2;
    num = 0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int disX = abs(x - ctrX);
            int disY = abs(y - ctrY);

            if (if_in_ellipse(disX, disY)) {
                mask[h * y + x] = 1;
                num++;
            } else {
                mask[h * y + x] = 0;
            }
        }
    }
}

float get_complax(IplImage *img, int r, int c, int w, int h) {
    float sum = 0.0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (mask[y * h + x]) {
                sum += pixval32f(img, r - w / 2 + x, c - h / 2 + y);
            }       
        }
    } 

    float avg = sum / num;
    float complaxVal = 0.0;
 
//  printf("%f %d %d\n", avg, r, c);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (mask[y * h + x]) {
                float tmp = pixval32f(img, r - w / 2 + x, c - h / 2 + y) - avg; 
                complaxVal += tmp * tmp;
            }       
        }
    } 

    return complaxVal;
}

CvPoint get_center(IplImage *img) {
    int origW = img->width;
    int origH = img->height;

    ellipseW = origW / factor; 
    ellipseH = origH / factor;
    mask = new unsigned char[ellipseH * ellipseW];
    init_mask(ellipseW, ellipseH);
    //num = ellipseH * ellipseW;

    int half_w = ellipseW / 2;
    int half_h = ellipseH / 2;
    int ctrX, ctrY;
    float maxComplax;

    for (int y = half_h; y < origH - half_h; y++) {
        for (int x = half_w; x < origW - half_w; x++) {
//          cvSetImageROI(img, cvEllipse(
            float complaxVal = get_complax(img, x, y, ellipseW, ellipseH);
//          printf("%f %d %d\n", complaxVal, x, y);
            if (complaxVal > maxComplax) {
                maxComplax = complaxVal;
                ctrX = x;
                ctrY = y;
            }
        }
    }

    cvCircle(img, cvPoint(ctrX, ctrY), half_h, cvScalar(0, 255, 9));
    printf("%d %d\n", ctrX, ctrY);
    show_image(img, "center");

    return cvPoint(ctrX, ctrY);
}

float *get_ellipse_feature(const IplImage *src) {
    IplImage *img = get_gray(src);

    CvPoint center = get_center(img);
    
}
