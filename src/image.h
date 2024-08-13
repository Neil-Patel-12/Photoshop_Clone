#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//(1) Declare a Header struct
//(2) Declare each Header element
struct Header {
    char IDLength;
    char colorMapType;
    char imageType;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrgin;
    short yOrgin;

    short imageWidth;
    short imageHeight;

    char pixelDepth;   // this is the bit per pixel; Don't really need!!
    char imageD;
};


//(3) Declare a Pixel struct
struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;

    int blueInt;
    int greenInt;
    int redInt;

    unsigned int blueU;
    unsigned int greenU;
    unsigned int redU;
};

//(4) Declare each Pixel element

//(5) Declare an Image class
class Image {
    //(6) Declare private data member of the Image class
    private:
        string name;      //(7) Declare a name
        ifstream stream;  //(8) Declare a stream (ifstream)
    public:
        Header head;                         //(9) Declare a header for the Image
        vector<Pixel> pixels;                    //(10) Declare a vector of pixels
        void read(const string& inName);     //(12) Declare a read function
        void write(const string& outName);   //(13) Declare a write function
        
        void changeHeader(Header& HeaderObj);
        void changeVector(vector<Pixel>& vector);
        Header GetHeader();
        vector<Pixel> GetVector();
};
