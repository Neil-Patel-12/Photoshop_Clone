#include "image.h"
#include <iostream>
using namespace std;



void Image::read(const string& inName) {
    //(14) Read in the .tga file
    stream.open(inName, ios::binary);

    //(15) Check if the file is opening
    if (stream.is_open()) {
        cout << "The file is now open! yaya!" << endl;
    }
    else if (!stream.is_open()) {
        throw runtime_error("file is closed");
    }

    //(16) Read in each element of the .tga file
    stream.read(&head.IDLength, sizeof(head.IDLength));
    stream.read(&head.colorMapType, sizeof(head.colorMapType));
    stream.read(&head.imageType, sizeof(head.imageType));
    stream.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
    stream.read((char*)&head.colorMapLength, sizeof(head.colorMapLength));
    stream.read(&head.colorMapDepth, sizeof(head.colorMapDepth));
    stream.read((char*)&head.xOrgin, sizeof(head.xOrgin));
    stream.read((char*)&head.yOrgin, sizeof(head.yOrgin));
    stream.read((char*)&head.imageWidth, sizeof(head.imageWidth));
    stream.read((char*)&head.imageHeight, sizeof(head.imageHeight));
    stream.read(&head.pixelDepth, sizeof(head.pixelDepth));
    stream.read(&head.imageD, sizeof(head.imageD));



    //(17) Get the image size by multiplying the image height and width
    int size = head.imageWidth * head.imageHeight;

    //(18) Create a for loop to read in all the pixels
    for (int i = 0; i < size; i++) {
        Pixel pix;
        stream.read((char*)&pix.blue, sizeof(pix.blue));
        stream.read((char*)&pix.green, sizeof(pix.green));
        stream.read((char*)&pix.red, sizeof(pix.red));
        pixels.push_back(pix);
    }

    //(21) Push in each pixel to the pixel vector

}

void Image::write(const string& outName) {
    //(22) Create a .tga file
    ofstream stream(outName, ios_base::binary);

    if (stream.is_open()) {
        cout << "Next file is OPEN!!" << endl;
    }

    //(23) Write out each .tga file header element
    stream.write(&head.IDLength, sizeof(head.IDLength));
    stream.write(&head.colorMapType, sizeof(head.colorMapType));
    stream.write(&head.imageType, sizeof(head.imageType));
    stream.write((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
    stream.write((char*)&head.colorMapLength, sizeof(head.colorMapLength));
    stream.write(&head.colorMapDepth, sizeof(head.colorMapDepth));
    stream.write((char*)&head.xOrgin, sizeof(head.xOrgin));
    stream.write((char*)&head.yOrgin, sizeof(head.yOrgin));
    stream.write((char*)&head.imageWidth, sizeof(head.imageWidth));
    stream.write((char*)&head.imageHeight, sizeof(head.imageHeight));
    stream.write(&head.pixelDepth, sizeof(head.pixelDepth));
    stream.write(&head.imageD, sizeof(head.imageD));

    //(24) Create a for loop to write out each pixel
    int size = head.imageWidth * head.imageHeight;
    //(25) Write out each image pixel
    for (int i = 0; i < size; i++) {
        Pixel pix = pixels[i];
        stream.write((char*)&pix.blue, sizeof(pix.blue));
        stream.write((char*)&pix.green, sizeof(pix.green));
        stream.write((char*)&pix.red, sizeof(pix.red));
    }
}

void Image::changeHeader(Header& HeaderObj) {
    head.IDLength = HeaderObj.IDLength;
    head.colorMapType = HeaderObj.colorMapType;
    head.imageType = HeaderObj.imageType;
    head.colorMapOrigin = HeaderObj.colorMapOrigin;
    head.colorMapLength = HeaderObj.colorMapLength;
    head.colorMapDepth = HeaderObj.colorMapDepth;
    head.xOrgin = HeaderObj.xOrgin;
    head.yOrgin = HeaderObj.yOrgin;
    head.imageWidth = HeaderObj.imageWidth;
    head.imageHeight = HeaderObj.imageHeight;
    head.pixelDepth = HeaderObj.pixelDepth;
    head.imageD = HeaderObj.imageD;
}

void Image::changeVector(vector<Pixel>& vector) {
    // get the updated vector as input and change it to this member variable vector...
    for (unsigned int i = 0; i < vector.size(); i++) {
        pixels.push_back(vector[i]);
    }
}

Header Image::GetHeader() {
    return head;
}

vector<Pixel> Image::GetVector() {
    return pixels;
}