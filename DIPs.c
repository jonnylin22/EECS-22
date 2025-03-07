/* DIPs.c  */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image.h"
#include "Constants.h"


/* Black and White */
Image *BlackNWhite(Image *image){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    unsigned int temp;

    for (int i = 0; i < width ; i ++ ) {
        for (int j = 0; j < height ; j ++) {
            temp = (GetPixelR(image, i, j) + GetPixelG(image, i, j) + GetPixelB(image, i, j) ) / 3;
            SetPixelR(image, i, j, temp);
            SetPixelG(image, i, j, temp);
            SetPixelB(image, i, j, temp);
        }
    } // end for loop
    return image;
} // *BlackNWhite()

/* Reverse image color */
Image *Negative(Image *image){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    for (int i = 0 ; i < width ; i ++) {
        for (int j = 0; j < height ; j ++) {
            unsigned int r = MAX_PIXEL - GetPixelR(image, i, j);
            SetPixelR(image, i, j, r);
            unsigned int g = MAX_PIXEL - GetPixelG(image, i, j);
            SetPixelG(image, i, j, g);
            unsigned int b = MAX_PIXEL - GetPixelB(image, i, j);
            SetPixelB(image, i, j, b);
        }
    } // end for loop
    return image;
} // *Negative()

/* Color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    replace_r = (replace_r > MAX_PIXEL) ? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_g = (replace_g > MAX_PIXEL) ? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
    replace_b = (replace_b > MAX_PIXEL) ? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

    for (int y = 0; y < height ; y ++) {
        for (int x = 0; x < width ; x++) {
            if (abs(GetPixelR(image, x, y) - target_r) <= threshold   
                    && abs(GetPixelG(image, x, y) - target_g) <= threshold 
                    && abs(GetPixelB(image, x, y) - target_b) <= threshold ) {
                SetPixelR(image, x, y, replace_r);
                SetPixelG(image, x, y, replace_g);
                SetPixelB(image, x, y, replace_b);
            } // end if 
        } // end for 
    }
    return image;
} // *ColorFilter()

/* Edge detection */
Image *Edge(Image *image){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    Image *temp_r = CreateImage(width, height);
    Image *temp_g = CreateImage(width, height);
    Image *temp_b = CreateImage(width, height);

    for (int y = 0 ; y < height ; y ++) {
        for (int x = 0 ; x < width ; x ++) {
            SetPixelR(temp_r, x, y, GetPixelR(image, x, y));
            SetPixelG(temp_g, x, y, GetPixelG(image, x, y));
            SetPixelB(temp_b, x, y, GetPixelB(image, x, y));
        }
    } 

    int sumR = 0;   /* sum of the intensity differences with neighbors */
	int sumG = 0;
	int sumB = 0;
	for (int y = 1; y < height - 1; y++){
		for (int x = 1; x < width - 1; x++){
			for (int n = -1; n <= 1; n++){
				for (int m = -1; m <= 1; m++) {
					int a = (x + m >= width) ? width - 1 : (x + m < 0) ? 0 : x + m;
					int b = (y + n >= height) ? height - 1 : (y + n < 0) ? 0 : y + n;
					sumR += ( GetPixelR(temp_r, x, y) - GetPixelR(temp_r, a, b) );
                    sumG += ( GetPixelG(temp_g, x, y) - GetPixelG(temp_g, a, b) );
					sumB += ( GetPixelB(temp_b, x, y) - GetPixelB(temp_b, a, b) );
				}
			}
            unsigned char r = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;
            SetPixelR(image, x, y, r);
            unsigned char g = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
            SetPixelG(image, x, y, g);
            unsigned char b = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
            SetPixelB(image, x, y, b);
			sumR = sumG = sumB = 0;
		}
	} // end for
    /* set all 24 borders to 0 */
	for (int y = 0; y < height; y++) {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);

        SetPixelR(image, width-1, y, 0);
        SetPixelG(image, width-1, y, 0);
        SetPixelB(image, width-1, y, 0);
	}
	for (int x = 0; x < width; x++) {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);

        SetPixelR(image, x, height-1, 0);
        SetPixelG(image, x, height-1, 0);
        SetPixelB(image, x, height-1, 0);
	}

    DeleteImage(temp_r);
    DeleteImage(temp_g);
    DeleteImage(temp_b);
    return image;
} // *Edge()

/* Flip image vertically */
Image *VFlip(Image *image){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);
    for (int y = 0; y < height/2; y++) {
		for (int x = 0; x < width; x++) {
            int y_location = height - 1 - y;
            unsigned int r = GetPixelR(image, x, y_location);
            unsigned int g = GetPixelG(image, x, y_location);
            unsigned int b = GetPixelB(image, x, y_location);

            SetPixelR(image, x, y_location, GetPixelR(image, x, y));
            SetPixelG(image, x, y_location, GetPixelG(image, x, y));
            SetPixelB(image, x, y_location, GetPixelB(image, x, y));

            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
		}
	} // end for
    return image;
} // *VFlip()

/* Mirror image vertically */
Image *HMirror(Image *image){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    for (int y = 0; y < height ; y ++ ) {
        for (int x = 0; x < width/2 ; x++) {
            int location = width-1-x;

            unsigned char r = GetPixelR(image, x, y);
            SetPixelR(image, location, y, r);
            unsigned char g = GetPixelG(image, x, y);
            SetPixelG(image, location, y, g);
            unsigned char b = GetPixelB(image, x, y);
            SetPixelB(image, location, y, b);
        }
    } // end for

    return image;
} // *HMirror

/* Zoom an image */
Image *AddBorder(Image *image, char *color, int border_width){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    int x, y;
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsupported color.\n");
        return image;
    }
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            if ((y < border_width) || (y > height - 1 - border_width) ||
                    (x < border_width) || (x > width - 1 - border_width)) {
                SetPixelR(image, x, y, border_r);
                SetPixelG(image, x, y, border_g);
                SetPixelB(image, x, y, border_b);
            }
        }
    }

    return image;
} // *AddBorder()


/* Shuffle an image */
Image *Shuffle(Image *image){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

	int block_width = width/SHUFF_WIDTH_DIV;
	int block_height = height/SHUFF_HEIGHT_DIV;
	int i, j, x, y;

    Image *temp_image = CreateImage(width, height);

    for (int y = 0 ; y < height ; y ++) {
        for (int x = 0 ; x < width ; x ++) {
            SetPixelR(temp_image, x, y, GetPixelR(image, x, y));
            SetPixelG(temp_image, x, y, GetPixelG(image, x, y));
            SetPixelB(temp_image, x, y, GetPixelB(image, x, y));
        }
    } 

	for (i = 0; i < SHUFF_HEIGHT_DIV/2; i++){ // only need to iterate throught half of the blocks
		for (j = 0; j < SHUFF_WIDTH_DIV; j++){
			for (x = 0; x < block_width; x++){
				for (y = 0; y < block_height; y++){
                    SetPixelR(temp_image, x, y, GetPixelR(image,x + (j * block_width), y + (i * block_height) ));
                    SetPixelG(temp_image, x, y, GetPixelG(image,x + (j * block_width), y + (i * block_height) ));
                    SetPixelB(temp_image, x, y, GetPixelB(image,x + (j * block_width), y + (i * block_height) ));

                    SetPixelR(image, x + (j * block_width), y + (i * block_height), GetPixelR(image,x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width),y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)) );
                    SetPixelG(image, x + (j * block_width), y + (i * block_height), GetPixelG(image,x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width),y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)) );
                    SetPixelB(image, x + (j * block_width), y + (i * block_height), GetPixelB(image,x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width),y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height)) );

                    SetPixelR(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), GetPixelR(temp_image, x, y) );
                    SetPixelG(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), GetPixelG(temp_image, x, y) );
                    SetPixelB(image, x + ((SHUFF_WIDTH_DIV - 1 -j) * block_width), y + ((SHUFF_HEIGHT_DIV - 1 -i) * block_height), GetPixelB(temp_image, x, y) );
				}
			}
		}
	} // end for
    DeleteImage(temp_image);
    return image;
} // *Shuffle()

/* Pixelate an image */
Image *Pixelate(Image *image, int block_size) {
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

	// if picture dimensions do not divide cleanly into block_size, stop some num pixels before the edge
	for ( int i = 0 ; i < (width - (width % block_size)) ; i +=block_size) { // 128 subsections across of 4 wide
		for (int j = 0 ; j < (height - (height % block_size)) ; j +=block_size ) { // 72 subsections down of 4 tall
			int r_sum = 0;
			int g_sum = 0;
			int b_sum = 0;
			for (int sub_i = 0 ; sub_i < block_size ; sub_i++) {
				for (int sub_j = 0 ; sub_j < block_size ; sub_j++) {
					// iterate on all 16 pixels and add them
					r_sum += GetPixelR(image, i + sub_i, j + sub_j);  
					g_sum += GetPixelG(image, i + sub_i, j + sub_j);
					b_sum += GetPixelB(image, i + sub_i, j + sub_j);
				}
			} 
			int r_avg = r_sum / (block_size*block_size);
			int g_avg = g_sum / (block_size*block_size);
			int b_avg = b_sum / (block_size*block_size);
				
			/* assign averages to each pixel in the block */
			for (int sub_i = 0 ; sub_i < block_size ; sub_i++) {
				for (int sub_j = 0; sub_j < block_size ; sub_j++) {
                    SetPixelR(image, i+sub_i, j + sub_j, r_avg);
                    SetPixelG(image, i+sub_i, j + sub_j, g_avg);
                    SetPixelB(image, i+sub_i, j + sub_j, b_avg);
				}
			}
		} 
	}

    return image;
} // *Pixelate()

/* Shift an image */
Image *Shift(Image *image, int shiftX, int shiftY){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);
    Image *shifted_image = CreateImage(width, height);

    for (int x=0 ; x<width ; x++) {
        for (int y=0; y<height ; y++) {

            int x_new = (x-shiftX+width) % width;
            int y_new = (y-shiftY+height) % height;

            SetPixelR(shifted_image, x, y, GetPixelR(image, x_new, y_new) );
            SetPixelG(shifted_image, x, y, GetPixelG(image, x_new, y_new) );
            SetPixelB(shifted_image, x, y, GetPixelB(image, x_new, y_new) );

        }
    } // end for 

    DeleteImage(image);
    return shifted_image;
} // *Shift()