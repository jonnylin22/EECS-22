/* PhotoLab.c : pointers and dynamic memory             */
/*  contains main() function, menu function PrintMenu() */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "Constants.h"
#include "Test.h"
#include "Advanced.h"
#include "DIPs.h"
#include "FileIO.h"
#include "Image.h"

void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image horizontally\n");
	printf("10: Add border to an image\n");
	printf("11: Pixelate an image\n");
	printf("12: Shift an image\n");
	printf("13: Crop an image\n");
	printf("14: Resize an image\n");
	printf("15: Add Watermark to an image\n");
	printf("16: Rotate an image by 90 degree\n");
	printf("17: Test all functions\n");
	printf("18: Exit\n");
}

int main() {
#ifdef DEBUG 
	AutoTest();
	return 0;
#endif	 

	int option;			/* user input option */
	char fname[SLEN];		/* input file name */
	char colorOption[SLEN];
	int RC; // return code

	PrintMenu();
	RC = 1;
	printf("Please make your choice: ");
	scanf("%d", &option);

	Image *image_pointer = NULL;			/* return Image pointer of LoadImage() */
	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;
	/* AddBorder() parameter */
	int border_width;
	/* Pixelate() parameter */
	int block_size = 0;

	/* Shift() parameters */
	int shiftX, shiftY;
	/* Crop() parameters */
	int x, y, W, H; 
	/* Resize() parameters*/
	int newWidth, newHeight;
	/* Watermark() parameters */
	Image *watermark_image = LoadImage("watermark_template");
	/* RotateBy90() parameters*/
	int rotateDirection;

	while (option != EXIT) {
		if (option == 1) {
			if (image_pointer != NULL) {
				DeleteImage(image_pointer);
			}
			printf("Please input the file name to load: ");
			scanf("%75s", fname);
			image_pointer = LoadImage(fname);
			
		}
		else if (option >= 2 && option <= 16) {
			if (RC != SUCCESS)	 {
				printf("No image is read.\n");
			}
			/* now image is loaded */
			else {
				switch(option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%75s", fname);
						SaveImage(fname, image_pointer);
						break;
					case 3:
						image_pointer = BlackNWhite(image_pointer);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						image_pointer = Negative(image_pointer);
						printf("\"Negative\" operation is done!\n");
						break;
					case 5:
						printf("Enter Red   component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);
						image_pointer = ColorFilter(image_pointer, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						image_pointer = Edge(image_pointer);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						image_pointer = Shuffle(image_pointer);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						image_pointer = VFlip(image_pointer);
						printf("\"VFlip\" operation is done!\n");
						break;
					case 9:
						image_pointer = HMirror(image_pointer);
						printf("\"HMirror\" operation is done!\n");
						break;
					case 10:
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s",colorOption);
						image_pointer = AddBorder(image_pointer, colorOption, border_width);
						printf("\"Border\" operation is done!\n");
						break;
					case 11:  	
						printf("Enter block size: ");
						scanf("%d", &block_size);
						image_pointer = Pixelate(image_pointer, block_size);
						printf("\"Pixelate\" operation is done!\n");
						break;
					case 12:
						printf("Please enter the X shift: ");
						scanf("%d", &shiftX);
						printf("Please enter the Y shift: ");
						scanf("%d", &shiftY);
						image_pointer = Shift(image_pointer, shiftX, shiftY);
						printf("\"Shift\" operation is done!\n");
						break;
					case 13: 
						printf("Please enter the X offset value: ");
						scanf("%d", &x);
						printf("Please enter the Y offset value: ");
						scanf("%d", &y);
						printf("Please input the crop width: ");
						scanf("%d", &W);
						printf("Please input the crop height: ");
						scanf("%d", &H);						
						image_pointer = Crop(image_pointer, x, y, W, H);
						printf("\"Crop\" operation is done!\n");
						break;
					case 14: 
						printf("Please input the new image width: ");
						scanf("%d", &newWidth);
						printf("Please input the new image height: ");
						scanf("%d", &newHeight);
						image_pointer = Resize(image_pointer, newWidth, newHeight);
						printf("\"Resizing the imgae\" operation is done!\n");
						break;
					case 15: 
						image_pointer = Watermark(image_pointer, watermark_image);
						printf("\"Watermark\" operation is done!\n");
						break;						
					case 16:
						printf("Please input the direction of rotation (0: clockwise, 1: counterclockwise): ");
						scanf("%d", &rotateDirection);
						image_pointer = RotateBy90(image_pointer, rotateDirection);
						printf("\"RotateBy90\" operation is done!\n");
						break;
		
					default:
						break;
				}
			}
		}
		else if (option == 17) {
			RC = AutoTest();
			if (RC!= SUCCESS) {
				printf("Auto Test failed, error code %d.\n", RC);
			} else {
				printf("AutoTest finished successfully.\n");
			}
		}
		else {
			printf("Invalid selection!\n");
		}

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}
	
	printf("You exit the program.\n");
	DeleteImage(watermark_image);
	DeleteImage(image_pointer);
	return 0;
}
