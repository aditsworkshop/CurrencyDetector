#include "/usr/include/opencv2/core/core.hpp"
#include "/usr/include/opencv2/highgui/highgui.hpp"
#include "/usr/include/opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main( int argc, char ** argv )
{

	static int x, y, c;
	double alpha;
	int beta;
	
	// Set threshold and maxValue
	double thresh = 230;
	double maxValue = 255; 
    
	if( argc > 4)
    {
     cout <<" Usage: ./readnotes original_image alpha[1.0-3.0] beta[0-100]" << endl;
     return -1;
    }

	alpha = strtod(argv[2], NULL);
	beta = atoi(argv[3] );

	if( ( alpha > 3.000000 || alpha < 1.000000 ) ||
		( beta > 100 || beta < 0 ) )
	{
		cout << "alpha: " << alpha << " and beta: " << beta << "values out of range" << endl;
		return -1;	
	}

	//cout << "alpha value: " << alpha << " and beta value: " << beta << endl;
    
	Mat image;
	Mat mod_image, mod_image1;

    // image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	mod_image = Mat::zeros(image.size(), image.type());	

	#if 0 
	// dive down each row
	for( y = 0; y < image.rows; y++ )
	{
		// dive down each column
		for( x = 0; x < image.cols; x++ )
		{
			/** deal with the three components that make up one pixed
			 	i.e., Red, Green and Blue components; hence, c < 3 */
			for( c = 0; c < 3; c++ )
			{
				// Apply the formula g(i,j) = alpha * f(i,j) + beta
				mod_image.at<Vec3b>(y,x)[c] = 	saturate_cast<uchar> /* output of ( (alpha * image ) + beta ) MIGHT be out of range; hence, the conversion */ 
												(
													( 
														alpha * (image.at<Vec3b>(y,x)[c])
											  		) 
													+ 	beta
												);
			}// for( c=0; ... )
		}// for( x=0; ...)
	}// for( y=0; ... )
	#else
	image.convertTo(mod_image1, -1, alpha, beta);
	mod_image1.convertTo(mod_image, -1, alpha, beta);
	//imwrite("./output.jpg", mod_image);
 
	// Binary Threshold
	//threshold( mod_image1, mod_image , thresh, maxValue, CV_THRESH_BINARY);
	threshold( mod_image1, mod_image , thresh, maxValue, 4);

	CvSeq* contours;  //hold the pointer to a contour in the memory block
	CvSeq* result;   //hold sequence of points of a contour
 	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours
 
 	//finding all contours in the image
 	cvFindContours(mod_image, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
 
	std::vector<uchar> mod_imagearr;

	if (mod_image.isContinuous()) 
	{
  		mod_imagearr.assign(mod_image.datastart, mod_image.dataend);
	}
	else 
	{
  		for (int i = 0; i < mod_image.rows; ++i) 
		{
    		mod_imagearr.insert(mod_imagearr.end(), mod_image.ptr<uchar>(i), mod_image.ptr<uchar>(i)+mod_image.cols);
  		}
	}
 
 	//iterating through each contour
 	while(contours)
 	{
 	    //obtain a sequence of points of contour, pointed by the variable 'contour'
 	    result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
          
 	    //if there are 3  vertices  in the contour(It should be a triangle)
 	   	if( result->total == 3 )
 	    {
 	        //iterating through each point
        	CvPoint *pt[3];

        	for( int i=0; i<3; i++)
			{
            	pt[i] = (CvPoint*)cvGetSeqElem(result, i);
         	}
   
	         //drawing lines around the triangle
	         cvLine(mod_imagearr, *pt[0], *pt[1], cvScalar(255,0,0),4);
	         cvLine(mod_imagearr, *pt[1], *pt[2], cvScalar(255,0,0),4);
	         cvLine(mod_imagearr, *pt[2], *pt[0], cvScalar(255,0,0),4);
    	}// if(result->total ...)   
     }// while()	
	#endif
	
	// Create a window for display.
    namedWindow( "Original Image", WINDOW_AUTOSIZE );
    namedWindow( "Modified Image", WINDOW_AUTOSIZE );
    
	// Show image inside the window created above
	imshow( "Original Image", image );           
    imshow( "Modified Image", mod_image );
    
	// Wait for a keystroke in the window
	waitKey(0);

	destroyAllWindows();
    return 0;
}

