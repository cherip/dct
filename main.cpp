#include "dct.h"
#include "utils.h"
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;

//#define METHOD

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        cout << "need parameter!\n";
        return 1;
    }

    IplImage *img = cvLoadImage( argv[1] );
    IplImage *img2 = cvLoadImage( argv[2] );

    compare_image_by_dct( img, img2 );
}
