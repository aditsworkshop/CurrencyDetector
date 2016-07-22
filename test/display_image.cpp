#include "/usr/include/opencv2/core/core.hpp"
#include "/usr/include/opencv2/highgui/highgui.hpp"
//#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{

    if( argc != 2)
    {
     cout <<" Usage: ./readnotes original_image" << endl;
     return -1;
    }

    Mat image;

    // image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }


    namedWindow( "Original Image", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Original Image", image );                   // Show our image inside it.
    
	waitKey(0);                                          // Wait for a keystroke in the window

	destroyAllWindows();
    return 0;
}

