#include <cv.h>
#include <highgui.h>

#include "utils.h"

const int factor = 16;
const int trackNum = 16;
int ellipseW, ellipseH;
unsigned char *mask;

int if_in_ellipse(int sizeW, int sizeH) {
    float val1 = sizeW / (float)ellipseW;
    float val2 = sizeH / (float)ellipseH;

    if (val1 * val1 + val2 * val2 <= 1) {
        return 1;
    } else {
        return 0;
    }
}


CvPoint get_center(IplImage *img) {
    int origW = img->width;
    int origH = img->height;

    ellipseW = origW / factor; 
    ellipseH = origH / factor;
    mask = new unsigned char[ellipseH * ellipseW];

    for (int y = ellipseH; y < origH - ellipseH; y++) {
        for (int x = ellipseW; x < origW - ellipseW; x++) {
//          cvSetImageROI(img, cvEllipse(
        }
    }
}
