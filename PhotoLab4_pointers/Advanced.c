/* Advanced.c */

#include <stdio.h>
#include <assert.h>

#include "Image.h"
#include "Constants.h"

/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H) {
    assert(image);
    Image *cropped = CreateImage(W, H);
    
    int new_width   = (x+W<ImageWidth(image))     ? x+W : ImageWidth(image);
    int new_height  = (y+H<ImageHeight(image))    ? y+H : ImageHeight(image);

    for (int i = x; i < new_width ; i++){
        for (int j = y; j < new_height ; j++) {
            SetPixelR(cropped, i-x, j-y, GetPixelR(image, i, j));
            SetPixelG(cropped, i-x, j-y, GetPixelG(image, i, j));
            SetPixelB(cropped, i-x, j-y, GetPixelB(image, i, j));
        }
    } //end for

    DeleteImage(image);
    return cropped;
} // *Crop()

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight){
    // Variables
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);
    double ScaleX = (double) newWidth / width;
    double ScaleY = (double) newHeight / height;
    Image *resized_image = CreateImage(newWidth, newHeight);
		
	// iterate over the output matrix
	for (int i = 0 ; i < newWidth ; i ++) {
		for (int j = 0 ; j < newHeight ; j ++){
		// compute X and Y prime coordinates
		int x_prime =  (i/ScaleX);
		int y_prime =  (j/ScaleY);	
  
		// Check if new (X,Y) coords exist within image bounds 
		if (x_prime >= 0 && x_prime <= ImageWidth(image) && y_prime >= 0 && y_prime <= ImageHeight(image)) {
            SetPixelR(resized_image, i, j, GetPixelR(image, x_prime, y_prime));
            SetPixelG(resized_image, i, j, GetPixelG(image, x_prime, y_prime));
            SetPixelB(resized_image, i, j, GetPixelB(image, x_prime, y_prime));
		}

		}
	} // end for 

    DeleteImage(image);
    return resized_image;
   
} // *Resize()


/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image){
    assert(image);
    assert(watermark_image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

    int mask_width = ImageWidth(watermark_image);
    int mask_height = ImageHeight(watermark_image);

    for (int x = 0; x < width ; x++) {
        for (int y = 0; y < height ; y++) {
            // Get corresponding pixel from watermark (with wrapping)
            int mask_x = x % mask_width;
            int mask_y = y % mask_height;

            unsigned char mask_r = GetPixelR(watermark_image, mask_x, mask_y);
            unsigned char mask_g = GetPixelG(watermark_image, mask_x, mask_y);
            unsigned char mask_b = GetPixelB(watermark_image, mask_x, mask_y);

            if (mask_r==0 && mask_g==0 && mask_b==0){
                int new_r = GetPixelR(image, x, y)*1.45;
                int new_g = GetPixelG(image, x, y)*1.45;
                int new_b = GetPixelB(image, x, y)*1.45;

                // Clamp values to MAX_PIXEL (255)
                SetPixelR(image, x, y, (new_r > MAX_PIXEL) ? MAX_PIXEL : new_r);
                SetPixelG(image, x, y, (new_g > MAX_PIXEL) ? MAX_PIXEL : new_g);
                SetPixelB(image, x, y, (new_b > MAX_PIXEL) ? MAX_PIXEL : new_b);
            }

        }
    } // end for

    return image;
} // *Watermark()

/* Rotate by 90 */
Image *RotateBy90(Image *image, int rotateDirection){
    assert(image);
    int width = ImageWidth(image);
    int height = ImageHeight(image);

	// initialize output arrays // store transformed pixels
    Image *rotated_image = CreateImage(height, width);

    for (int x = 0; x < width ; x++){
        for (int y = 0; y < height ; y++) {
            if (!rotateDirection) { // clockwise (90 degrees right)
                SetPixelR(rotated_image, height-y-1, x, GetPixelR(image, x, y));
                SetPixelG(rotated_image, height-y-1, x, GetPixelG(image, x, y));
                SetPixelB(rotated_image, height-y-1, x,  GetPixelB(image, x, y));
            } else { // counterclockwise (90 degrees left)
                SetPixelR(rotated_image, y, width-x-1, GetPixelR(image, x, y));
                SetPixelG(rotated_image, y, width-x-1, GetPixelG(image, x, y));
                SetPixelB(rotated_image, y, width-x-1, GetPixelB(image, x, y));
            }

        }
    } // end for

    DeleteImage(image);
    return rotated_image;
} // *RotateBy90