/* Image.c : basic operations on an image */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "Image.h"
#include "Constants.h"


/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x,  unsigned int y) {
    int location = y*ImageWidth(image) + x;
    assert(image);
    assert(image->R);

    if (x >= ImageWidth(image) || y >= ImageHeight(image)) {
        fprintf(stderr, "Error: Pixel out of bounds! (x: %u, y: %u)\n", x, y);
        exit(1);
    }
    return image->R[location];      // using array indexing
} // GetPixelR()

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const Image *image, unsigned int x,  unsigned int y){
    int location = y*ImageWidth(image) + x;
    assert(image);
    assert(image->G);
    if (x >= ImageWidth(image) || y >= ImageHeight(image)) {
        fprintf(stderr, "Error: Pixel out of bounds! (x: %u, y: %u)\n", x, y);
        exit(1);
    }
    return image->G[location];
} // GetPixelG()

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const Image *image, unsigned int x,  unsigned int y){
    int location = y*ImageWidth(image) + x;
    assert(image);
    assert(image->B);
    if (x >= ImageWidth(image) || y >= ImageHeight(image)) {
        fprintf(stderr, "Error: Pixel out of bounds! (x: %u, y: %u)\n", x, y);
        exit(1);
    }
    return image->B[location];
} // GetPixelB()

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(Image *image, unsigned int x,  unsigned int y, unsigned char r){
    int location = y*ImageWidth(image) + x;
    assert(image);
    assert(image->R);
    if (x >= ImageWidth(image) || y >= ImageHeight(image)) {
        fprintf(stderr, "Error: Pixel out of bounds! (x: %u, y: %u)\n", x, y);
        exit(1);
    }
    image->R[location] = r; 
} // SetPixelR()

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(Image *image, unsigned int x,  unsigned int y, unsigned char g){
    int location = y*ImageWidth(image) + x;
    assert(image);
    assert(image->G);
    if (x >= ImageWidth(image) || y >= ImageHeight(image)) {
        fprintf(stderr, "Error: Pixel out of bounds! (x: %u, y: %u)\n", x, y);
        exit(1);
    }
    image->G[location] = g; 
} // SetPixelG()

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(Image *image, unsigned int x,  unsigned int y, unsigned char b){
    int location = y*ImageWidth(image) + x;
    assert(image);
    assert(image->B);
    if (x >= ImageWidth(image) || y >= ImageHeight(image)) {
        fprintf(stderr, "Error: Pixel out of bounds! (x: %u, y: %u)\n", x, y);
        exit(1);
    }
    image->B[location] = b; 
} // SetPixelB()

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
Image *CreateImage(unsigned int Width, unsigned int Height){
    Image *image_pointer = (Image*) malloc(sizeof(Image));   // allocate a block of memory for image struct
    if (! image_pointer) {
        perror("Out of memory! Aborting... ");
        exit(10);
    } /* fi */

    // allocate blocks of memory for each color channel
    image_pointer->R =  (unsigned char*) malloc(sizeof(unsigned char)*Width*Height);
    image_pointer->G =  (unsigned char*) malloc(sizeof(unsigned char)*Width*Height);
    image_pointer->B =  (unsigned char*) malloc(sizeof(unsigned char)*Width*Height);

    if (!image_pointer->R || !image_pointer->G || !image_pointer->B) {
        perror("Out of memory for pixel data! Aborting...");
        free(image_pointer->R);
        free(image_pointer->G);
        free(image_pointer->B);
        free(image_pointer);
        exit(10);
    }

    image_pointer -> W = Width;
    image_pointer -> H = Height;

    return image_pointer;
} // *CreateImage()

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image){
    if (image) {
        free(image->R);
        free(image->G);
        free(image->B);       
        free(image);
    }
} // DeleteImage()

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image){
    assert(image);
    return image->W;
} // ImageWidth()

/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image){
    assert(image);
    return image->H;
} // ImageHeight()