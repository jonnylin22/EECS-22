/********************************************************/
/* Advanced.c : new filters for assignment 3 		*/
/* 	function definitions for FishEye(), Rotate()	*/
/*	Posterize(), and MotionBlur()			*/
/********************************************************/

#include "Constants.h"
#include "Advanced.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*** function definitions **/

/* Create a fisheye image W24 */
void FishEye(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double base_factor, double distortion_factor, double scaling_factor) {
	// initialize output arrays // store transformed pixels
	unsigned char R0 [WIDTH][HEIGHT];
	unsigned char G0 [WIDTH][HEIGHT];
	unsigned char B0 [WIDTH][HEIGHT];

	// calculate image center point
	float center_x = WIDTH / 2; 	// 512/2 = 256	
	float center_y = HEIGHT / 2;	// 288/2 = 244
	
	// renaming for convenience	
	double k = distortion_factor;

	// for each pixel in image: calculate stuff
	for (int i = 0 ; i < WIDTH ; i ++) {
		double dx = (i - center_x) / center_x; 
		for (int j = 0 ; j < HEIGHT ; j ++) {
			double dy = (j - center_y) / center_y;
			double radius = sqrt( (dx*dx) + (dy*dy) );
			double distortion = 1+(k*(radius*radius));
			// apply fisheye transformation (polar coords)
			double theta = atan2(dy, dx);
			double new_radius = (radius*base_factor) / (distortion*scaling_factor) ;
			// convert back to cartesian coords
			int x_src = center_x + (new_radius*cos(theta)*center_x);
			int y_src = center_y + (new_radius*sin(theta)*center_y);
			// check if source coords are within bounds and copy pixel
			if (x_src>=0 && x_src<=WIDTH && y_src>=0 && y_src<=HEIGHT) {
				R0[i][j] = R[x_src][y_src];
				G0[i][j] = G[x_src][y_src];
				B0[i][j] = B[x_src][y_src];
				
			} else {	
				R0[i][j] = 0;
				R0[i][j] = 0;
				R0[i][j] = 0; 
			} //end if
		}
	} // end for

	
	// copy transformed array back to original arrays 
	for (int i = 0 ; i < WIDTH ; i ++) {
		for (int j = 0 ; j < HEIGHT ; j ++) {
			R[i][j] = R0[i][j];
			G[i][j] = G0[i][j];
			B[i][j] = B0[i][j];		
		}
	} 

} /* Fisheye() */


/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits) {
	for (int i = 0 ; i < WIDTH ; i ++ ){
		for (int j = 0 ; j < HEIGHT ; j ++) {
			// R pixels: change each red pixel's value  		
			for (int n = 0 ; n < rbits ; n++) {
				int mask = 1 << n;	// create a bit mask ex: 0010
				R[i][j] = R[i][j] | mask; 	// set bit with OR 
				if (n == rbits-1) { 
					R[i][j] = R[i][j] & (~mask);	// AND nth bit with 0
				}
			} 
			// G pixels:
			for (int n = 0 ; n < gbits ; n++) {
				int mask = 1 << n;	// create a bit mask ex: 0010
				G[i][j] = G[i][j] | mask; 	// set bit with OR 
				if (n == gbits-1) { 
					G[i][j] = G[i][j] & (~mask);	// AND nth bit with 0
				}
			}	
			// B pixels:  
			for (int n = 0 ; n < bbits ; n++) {
				int mask = 1 << n;	// create a bit mask ex: 0010
				B[i][j] = B[i][j] | mask; 	// set bit with OR 
				if (n == bbits-1) { 
					B[i][j] = B[i][j] & (~mask);	// AND nth bit with 0
				}
			} 
		}
	} // end for
} // end Posterize()

/* rotate and zoom the image */
void Rotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double Angle, double ScaleFactor,  int CenterX, int CenterY) {
	// variable declarations 
	double rads = -1 * Angle * (M_PI / 180);	// convert degrees to radians
	// initialize output arrays // store transformed pixels
	unsigned char R0 [WIDTH][HEIGHT] ;
	unsigned char G0 [WIDTH][HEIGHT] ;
	unsigned char B0 [WIDTH][HEIGHT] ; 
	// assign output arrays to black first
	for (int i = 0; i < WIDTH; i++) {
    		for (int j = 0; j < HEIGHT; j++) {
        		R0[i][j] = 0;
        		G0[i][j] = 0;
        		B0[i][j] = 0;
    		}
	}
		
	// iterate over the output matrix
	for (int i = 0 ; i < WIDTH ; i ++) {
		for (int j = 0 ; j < HEIGHT ; j ++){
		
		// compute X and Y prime coordinates
		double x_prime_d = (cos(rads)/ScaleFactor)*(i-CenterX) + (-sin(rads)/ScaleFactor)*(j-CenterY) + CenterX;
		double y_prime_d = (sin(rads)/ScaleFactor)*(i-CenterX) + (cos(rads)/ScaleFactor)*(j-CenterY) + CenterY;	
		
            	int x_prime = (int)x_prime_d; 
            	int y_prime = (int)y_prime_d;
  
		// Check if new (X,Y) coords exist within image bounds 
		if (x_prime >= 0 && x_prime <= WIDTH-1 && y_prime >= 0 && y_prime <= HEIGHT-1) {
			R0[i][j] = R[x_prime][y_prime];
			G0[i][j] = G[x_prime][y_prime];
			B0[i][j] = B[x_prime][y_prime];
		}

		}
	} // end for 
	
	// copy back output arrays to original 
	for (int i = 0 ; i < WIDTH ; i ++) {
		for (int j = 0 ; j < HEIGHT ; j ++){
			R[i][j] = R0[i][j]; 
			G[i][j] = G0[i][j]; 
			B[i][j] = B0[i][j]; 
		}
	} // end for 
} // end Rotate()

/* blur an image */ 
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){

	for (int i = 0 ; i < WIDTH ; i++) {
		for (int j = 0; j < HEIGHT ; j++) {
			// calculate average pixel value
			float r_sum = 0;  
            		float g_sum = 0;
            		float b_sum = 0;

			int count = 0; 		// count number of pixels averaged 

			float r_avg, g_avg, b_avg;		
			if (i == WIDTH-1) {
				r_avg = 0.5*R[i][j];
				g_avg = 0.5*G[i][j];
				b_avg = 0.5*B[i][j];
			} else { 
				
				// sum pixels to the right
				for (int n=1; n<=BlurAmount && (i+n)<WIDTH ; n++) {
					count++;
					r_sum += R[i+n][j]; 
					g_sum += G[i+n][j]; 
					b_sum += B[i+n][j];  
				}	 
				// done summing for one pixel: take averages and assign new value

              		       	r_avg = r_sum*(0.5/count);
        	       	        g_avg = g_sum*(0.5/count);
                       		b_avg = b_sum*(0.5/count); 
			} // end if			

  	                       	R[i][j] = (unsigned char) (  0.5 * R[i][j] + r_avg );
                        	G[i][j] = (unsigned char) (  0.5 * G[i][j] + g_avg );
                         	B[i][j] = (unsigned char) (  0.5 * B[i][j] + b_avg ); 
		}
	} // end for


} // end MotionBlur()


/* EOF Advanced.c */
