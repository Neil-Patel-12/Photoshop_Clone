#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "image.h"
using namespace std;

unsigned char Clamp(int numValue) {
    // used for subtracting the values in each channel
    unsigned int changeNumValue;
    if (numValue < 0) {
        changeNumValue = 0;
    }
    else if (numValue > 255) {
        changeNumValue = 255;
    }
    else {
        changeNumValue = numValue;
    }
    unsigned char mainChar = (unsigned char)(changeNumValue + '\0');
    return mainChar;
}

// need for Normalized bc (precision error)
float quickAdd(float number) { 
    number += 0.5f;
    return number;
}

Image Multiply(Image& tgaA, Image& tgaB) {
    Image tgaC; // the NEW tga image when Multiplied...
    Header head1 = tgaA.GetHeader();
    tgaC.changeHeader(head1);

    vector<Pixel> vector1 = tgaA.GetVector();
    vector<Pixel> vector2 = tgaB.GetVector();

    // change char BGR to Unsigned int for each vector of tga images...
    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueU = (unsigned int)(vector1[i].blue - '\0');
        vector1[i].greenU = (unsigned int)(vector1[i].green - '\0');
        vector1[i].redU = (unsigned int)(vector1[i].red - '\0');
    }
    for (unsigned int i = 0; i < vector2.size(); i++) {
        vector2[i].blueU = (unsigned int)(vector2[i].blue - '\0');
        vector2[i].greenU = (unsigned int)(vector2[i].green - '\0');
        vector2[i].redU = (unsigned int)(vector2[i].red - '\0');
    }

    vector<Pixel> newTGACvec;
    // Normalized(P1) * Normalized(P2) = 0-1  // for each channel
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pixC;
        unsigned int blue = (unsigned int)quickAdd(vector1[i].blueU * vector2[i].blueU / 255.0f); // original pix / 255
        pixC.blue = (unsigned char)(blue + '\0');

        unsigned int green = (unsigned int)quickAdd(vector1[i].greenU * vector2[i].greenU / 255.0f);
        pixC.green = (unsigned char)(green + '\0');

        unsigned int red = (unsigned int)quickAdd(vector1[i].redU * vector2[i].redU / 255.0f);
        pixC.red = (unsigned char)(red + '\0');

        newTGACvec.push_back(pixC);
    }
    tgaC.changeVector(newTGACvec);
    // changeVector will make the newTGACvec go to the class member variable (pixels) ->vector...
    return tgaC;
}

Image Subtract(Image& tgaA, Image& tgaB) {
    Image tgaC;
    Header newHeader = tgaA.GetHeader();
    tgaC.changeHeader(newHeader);

    vector<Pixel> vector1 = tgaA.GetVector();
    vector<Pixel> vector2 = tgaB.GetVector();

    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)((vector1[i].blue) - '\0');
        vector1[i].greenInt = (int)((vector1[i].green) - '\0');
        vector1[i].redInt = (int)((vector1[i].red) - '\0');
    }
    for (unsigned int i = 0; i < vector2.size(); i++) {
        vector2[i].blueInt = (int)((vector2[i].blue) - '\0');
        vector2[i].greenInt = (int)((vector2[i].green) - '\0');
        vector2[i].redInt = (int)((vector2[i].red) - '\0');
    }

    vector<Pixel> newTGACvec;
    // [(P1) - (P2)]
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pixC;
        pixC.blue = Clamp(vector1[i].blueInt - vector2[i].blueInt);
        pixC.green = Clamp(vector1[i].greenInt - vector2[i].greenInt);
        pixC.red = Clamp(vector1[i].redInt - vector2[i].redInt);

        newTGACvec.push_back(pixC);
    }
    tgaC.changeVector(newTGACvec);
    return tgaC;
}
// need to fix this maybe
Image Addcolorgreen(Image& tgaA, int channelBlue, int channelGreen, int channelRed) {
    Image newTGA;
    Header newHeader = tgaA.GetHeader();
    newTGA.changeHeader(newHeader);
    
    vector<Pixel> vector1 = tgaA.GetVector();
    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)((vector1[i].blue) - '\0');
        vector1[i].greenInt = (int)((vector1[i].green) - '\0');
        vector1[i].redInt = (int)((vector1[i].red) - '\0');
    }

    vector<Pixel> newTGAvec;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pixNew;
        pixNew.blue = vector1[i].blue;
        pixNew.green = Clamp(vector1[i].greenInt + channelGreen);
        pixNew.red = vector1[i].red;

        newTGAvec.push_back(pixNew);
    }
    newTGA.changeVector(newTGAvec);
    return newTGA;
}

Image Addcolorblue(Image& tgaA, int channelBlue, int channelGreen, int channelRed) {
    Image newTGA;
    Header newHeader = tgaA.GetHeader();
    newTGA.changeHeader(newHeader);

    vector<Pixel> vector1 = tgaA.GetVector();
    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)((vector1[i].blue) - '\0');
        vector1[i].greenInt = (int)((vector1[i].green) - '\0');
        vector1[i].redInt = (int)((vector1[i].red) - '\0');
    }

    vector<Pixel> newTGAvec;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pixNew;
        pixNew.blue = Clamp(vector1[i].blueInt + channelBlue);
        pixNew.green = vector1[i].green;
        pixNew.red = vector1[i].red;

        newTGAvec.push_back(pixNew);
    }
    newTGA.changeVector(newTGAvec);
    return newTGA;
}

Image Addcolorred(Image& tgaA, int channelBlue, int channelGreen, int channelRed) {
    Image newTGA;
    Header newHeader = tgaA.GetHeader();
    newTGA.changeHeader(newHeader);

    vector<Pixel> vector1 = tgaA.GetVector();
    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)((vector1[i].blue) - '\0');
        vector1[i].greenInt = (int)((vector1[i].green) - '\0');
        vector1[i].redInt = (int)((vector1[i].red) - '\0');
    }

    vector<Pixel> newTGAvec;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pixNew;
        pixNew.blue = vector1[i].blue;
        pixNew.green = vector1[i].green;
        pixNew.red = Clamp(vector1[i].redInt + channelRed);

        newTGAvec.push_back(pixNew);
    }
    newTGA.changeVector(newTGAvec);
    return newTGA;
}

// this should rotate the image 180 degrees (upside down)
Image Rotate(Image& tgaA) {
    Image tgaB;
    Header newHeader = tgaA.GetHeader();
    tgaB.changeHeader(newHeader);

    vector<Pixel> vector1 = tgaA.GetVector();
    vector<Pixel> vector2;
    // int lastPix = newHeader.imageWidth * newHeader.imageHeight;

    // we are starting at the top right (index lastPix - 1), ending at bottom left (index 0)
    for (int i = vector1.size() - 1; i >= 0; i--) {
        Pixel pix;

        pix.blue = (vector1[i].blue);
        pix.green = (vector1[i].green);
        pix.red = (vector1[i].red);

        vector2.push_back(pix);
    }
    tgaB.changeVector(vector2);
    return tgaB;
}

Image Screen(Image& tgaA, Image& tgaB) { // screen blending tool
    Image tgaC;
    Header newHeader = tgaA.GetHeader();
    tgaC.changeHeader(newHeader);

    vector<Pixel> vector1 = tgaA.GetVector();
    vector<Pixel> vector2 = tgaB.GetVector();

    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)((vector1[i].blue) - '\0');
        vector1[i].greenInt = (int)((vector1[i].green) - '\0');
        vector1[i].redInt = (int)((vector1[i].red) - '\0');
    }
    for (unsigned int i = 0; i < vector2.size(); i++) {
        vector2[i].blueInt = (int)((vector2[i].blue) - '\0');
        vector2[i].greenInt = (int)((vector2[i].green) - '\0');
        vector2[i].redInt = (int)((vector2[i].red) - '\0');
    }

    vector<Pixel> newTGAvecC;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pixC;
        float blueF = (255 - (255 - (float)vector1[i].blueInt) * (255 - (float)vector2[i].blueInt) / 255.0f);
        pixC.blue = Clamp(quickAdd(blueF));

        float greenF = (255 - (255 - (float)vector1[i].greenInt) * (255 - (float)vector2[i].greenInt) / 255.0f);
        pixC.green = Clamp(quickAdd(greenF));

        float redF = (255 - (255 - (float)vector1[i].redInt) * (255 - (float)vector2[i].redInt) / 255.0f);
        pixC.red = Clamp(quickAdd(redF));

        newTGAvecC.push_back(pixC);
    }
    tgaC.changeVector(newTGAvecC);
    return tgaC;
}
// also known as Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale, Scale
Image Scale(Image& tgaA, int blueChan, int greenChan, int redChan) {
    
    Image tga;
    Header newHeader = tgaA.GetHeader();
    tga.changeHeader(newHeader);
    vector<Pixel> vector1 = tgaA.GetVector();

    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)((vector1[i].blue) - '\0');
        vector1[i].greenInt = (int)((vector1[i].green) - '\0');
        vector1[i].redInt = (int)((vector1[i].red) - '\0');
    }
    vector<Pixel> newTGAvec;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pix;
        pix.blue = Clamp(vector1[i].blueInt * blueChan);
        pix.green = Clamp(vector1[i].greenInt * greenChan);
        pix.red = Clamp(vector1[i].redInt * redChan);
        newTGAvec.push_back(pix);
    }
    tga.changeVector(newTGAvec);
    return tga;
}

Image SeparateColorChannels(Image& tgaA, int checking) {
    Image tga;
    Header newHeader = tgaA.GetHeader();
    tga.changeHeader(newHeader);
    vector<Pixel> vector1 = tgaA.GetVector();

    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueU = (unsigned int)((vector1[i].blue) - '\0');
        vector1[i].greenU = (unsigned int)((vector1[i].green) - '\0');
        vector1[i].redU = (unsigned int)((vector1[i].red) - '\0');
    }

    vector<Pixel> newTGAvec;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pix;
        // change each channel pixel values to the BLUE channel value
        if (checking == 99) {
            pix.blue = vector1[i].blue;
            pix.green = vector1[i].blue;
            pix.red = vector1[i].blue;
        }

        // change each channel pixel values to the GREEN channel value
        else if (checking == 88) {
            pix.blue = vector1[i].green;
            pix.green = vector1[i].green;
            pix.red = vector1[i].green;
        }

        // change each channel pixel values to the RED channel value
        else if (checking == 77) {
            pix.blue = vector1[i].red;
            pix.green = vector1[i].red;
            pix.red = vector1[i].red;
        }
        newTGAvec.push_back(pix);
    }
    tga.changeVector(newTGAvec);
    return tga;
}

Image combine(Image& blue, Image& green, Image& red) {
    Image tga;
    Header newHeader = blue.GetHeader();
    tga.changeHeader(newHeader);
    vector<Pixel> blueVec = blue.GetVector();
    vector<Pixel> greenVec = green.GetVector();
    vector<Pixel> redVec = red.GetVector();

    for (unsigned int i = 0; i < blueVec.size(); i++) {
        blueVec[i].blueU = (unsigned int)((blueVec[i].blue) - '\0');
        greenVec[i].greenU = (unsigned int)((greenVec[i].green) - '\0');
        redVec[i].redU = (unsigned int)((redVec[i].red) - '\0');
    }
    vector<Pixel> TGAvec;
    for (unsigned int i = 0; i < blueVec.size(); i++) {
        Pixel pix;
        pix.blue = blueVec[i].blueU;
        pix.green = greenVec[i].greenU;
        pix.red = redVec[i].redU;
        TGAvec.push_back(pix);
    }
    tga.changeVector(TGAvec);
    return tga;
}

// 1 -[2*(1-NP) * (1-NP)] if greater than (255/2) = 0.5

Image Overlay(Image& tgaA, Image& tgaB) {
    //code...
    Image tgaC;
    Header newHeader = tgaA.GetHeader();
    tgaC.changeHeader(newHeader);
    vector<Pixel> vector1 = tgaA.GetVector();
    vector<Pixel> vector2 = tgaB.GetVector();

    for (unsigned int i = 0; i < vector1.size(); i++) {
        vector1[i].blueInt = (int)(vector1[i].blue);
        vector1[i].greenInt = (int)(vector1[i].green);
        vector1[i].redInt = (int)(vector1[i].red);
    }
    for (unsigned int i = 0; i < vector2.size(); i++) {
        vector2[i].blueInt = (int)(vector2[i].blue);
        vector2[i].greenInt = (int)(vector2[i].green);
        vector2[i].redInt = (int)(vector2[i].red);
    }

    vector<Pixel> newTGAvec;
    for (unsigned int i = 0; i < vector1.size(); i++) {
        Pixel pix;
        // 255/2 = 127.5
        if (vector1[i].blueInt <= 127) {
            pix.blue = quickAdd(2 * vector1[i].blueInt * vector2[i].blueInt / 255.0f);
        }
        else if (vector1[i].blueInt > 127) {
            pix.blue = quickAdd(255 - (2 * (255 - vector1[i].blueInt) * (255 - vector2[i].blueInt) / 255.0f));
        }

        if (vector1[i].greenInt <= 127) {
            pix.green = quickAdd(2 * vector1[i].greenInt * vector2[i].greenInt / 255.0f);
        }
        else if (vector1[i].greenInt > 127) {
            pix.green = quickAdd(255 - (2 * (255 - vector1[i].greenInt) * (255 - vector2[i].greenInt) / 255.0f));
        }

        if (vector1[i].redInt <= 127) {
            pix.red = quickAdd(2 * vector1[i].redInt * vector2[i].redInt / 255.0f);
        }
        else if (vector1[i].redInt > 127) {
            pix.red = quickAdd(255 - (2 * (255 - vector1[i].redInt) * (255 - vector2[i].redInt) / 255.0f));
        }

        newTGAvec.push_back(pix);
    }
    tgaC.changeVector(newTGAvec);
    return tgaC;
}

// int argc, char* argv[]
// 
// for (int i = 0; i < argc; i++) {
//     cout << argv[i] << endl;
// }
// ["", "ssdsd", "dsdsd", "dsdsd"]

inline bool exists(const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}
Image checking;
int main(int argc, char* argv[]) {
    string inputFileName = "";
    if (argc > 2) {
        inputFileName = (string)argv[2];
    }
    // might NOT need to open the file like this...
    ifstream imageFile(inputFileName, ios::binary);
    if (argc == 1 || (argc == 2 && ((string)(argv[1])) == "--help")) {
        cout << "Project 2: Image Processing, Fall 2023" << endl;
        cout << endl;
        cout << "Usage:" << endl;
        cout << "\t" << "./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    else if (argc >= 2 && string(argv[1]).length() < 4) {
        cout << "Invalid file name." << endl;
        return 0;
    }

    else if (argc >= 2 && string(argv[1]).substr(string(argv[1]).length() - 4) != ".tga") {
        cout << "Invalid file name." << endl;
        return 0;
    }

    else if (argc == 2 || (argc >= 3 && (string(argv[2]).substr(string(argv[2]).length() - 4) != ".tga"))) {
        cout << "Invalid file name." << endl;
        return 0;
    }
    
    if (argc == 3 && !((string)(argv[2]) == "input/car.tga" ||
        (string)(argv[2]) == "input/circles.tga" ||
        (string)(argv[2]) == "input/layer_blue.tga" ||
        (string)(argv[2]) == "input/layer_green.tga" ||
        (string)(argv[2]) == "input/layer_red.tga" ||
        (string)(argv[2]) == "input/layer1.tga" ||
        (string)(argv[2]) == "input/layer2.tga" ||
        (string)(argv[2]) == "input/pattern1.tga" ||
        (string)(argv[2]) == "input/pattern2.tga" ||
        (string)(argv[2]) == "input/text.tga" ||
        (string)(argv[2]) == "input/text2.tga")) {
        cout << "File does not exist." << endl;
        return 0;
    }

    else if (argc == 3) {
        cout << "Invalid method name." << endl;
        return 0;
    }
    else if (!((string)argv[3] == "multiply" ||
        (string)argv[3] == "subtract" ||
        (string)argv[3] == "overlay" ||
        (string)argv[3] == "screen" ||
        (string)argv[3] == "combine" ||
        (string)argv[3] == "flip" ||
        (string)argv[3] == "onlyred" ||
        (string)argv[3] == "onlygreen" ||
        (string)argv[3] == "onlyblue" ||
        (string)argv[3] == "addred" ||
        (string)argv[3] == "addgreen" ||
        (string)argv[3] == "addblue" ||
        (string)argv[3] == "scalered" ||
        (string)argv[3] == "scalegreen" ||
        (string)argv[3] == "scaleblue")) {
        cout << "Invalid method name." << endl;
        return 0;
    }
    else {
        Image Tracking;

        Tracking.read(inputFileName);

        //Header mainHeader = Tracking.GetHeader();

        int argsUsed = 3;

        //            3 < 25
        while (argsUsed < argc) {
            if ((string)argv[argsUsed] == "multiply") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                if (((string)argv[argsUsed]).length() < 4 || ((string)argv[argsUsed]).compare(((string)argv[argsUsed]).length()-4, 4, ".tga") != 0) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 1;
                }
                try {
                    checking.read((string)argv[argsUsed]);
                }
                catch (runtime_error& e) {
                    cout << "Invalid argument, file does not exist." << endl;
                }
                string nameOfImage = (string)argv[argsUsed];
                Image name_to_image;
                name_to_image.read(nameOfImage);
                Tracking = Multiply(Tracking, name_to_image);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "subtract") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                if (((string)argv[argsUsed]).length() < 4 || ((string)argv[argsUsed]).compare(((string)argv[argsUsed]).length() - 4, 4, ".tga") != 0) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 1;
                }
                try {
                    checking.read((string)argv[argsUsed]);
                }
                catch (runtime_error& e) {
                    cout << "Invalid argument, file does not exist." << endl;
                }
                string nameOfImage2 = (string)argv[argsUsed];
                Image name_to_image2;
                name_to_image2.read(nameOfImage2);
                Tracking = Subtract(Tracking, name_to_image2);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "overlay") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                if (((string)argv[argsUsed]).length() < 4 || ((string)argv[argsUsed]).compare(((string)argv[argsUsed]).length() - 4, 4, ".tga") != 0) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 1;
                }
                try {
                    checking.read((string)argv[argsUsed]);
                }
                catch (runtime_error& e) {
                    cout << "Invalid argument, file does not exist." << endl;
                }
                string nameOfImage3 = (string)argv[argsUsed];
                Image name_to_image3;
                name_to_image3.read(nameOfImage3);
                Tracking = Overlay(Tracking, name_to_image3);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "screen") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                if (((string)argv[argsUsed]).length() < 4 || ((string)argv[argsUsed]).compare(((string)argv[argsUsed]).length() - 4, 4, ".tga") != 0) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 1;
                }
                try {
                    checking.read((string)argv[argsUsed]);
                }
                catch (runtime_error& e) {
                    cout << "Invalid argument, file does not exist." << endl;
                }
                string nameOfImage4 = (string)argv[argsUsed];
                Image name_to_image4;
                name_to_image4.read(nameOfImage4);
                Tracking = Screen(Tracking, name_to_image4);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "combine") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                if (((string)argv[argsUsed]).length() < 4 || ((string)argv[argsUsed]).compare(((string)argv[argsUsed]).length() - 4, 4, ".tga") != 0) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 1;
                }
                try {
                    checking.read((string)argv[argsUsed]);
                }
                catch (runtime_error& e) {
                    cout << "Invalid argument, file does not exist." << endl;
                }
                string nameOfImage5 = (string)argv[argsUsed];
                Image name_to_image5;
                name_to_image5.read(nameOfImage5);

                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                if (((string)argv[argsUsed]).length() < 4 || ((string)argv[argsUsed]).compare(((string)argv[argsUsed]).length() - 4, 4, ".tga") != 0) {
                    cout << "Invalid argument, invalid file name." << endl;
                    return 1;
                }
                try {
                    checking.read((string)argv[argsUsed]);
                }
                catch (runtime_error& e) {
                    cout << "Invalid argument, file does not exist." << endl;
                }
                string imageName = (string)argv[argsUsed];
                Image secondImage;
                secondImage.read(imageName);

                Tracking = combine(Tracking, name_to_image5, secondImage);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "flip") {
                Tracking = Rotate(Tracking);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "onlyred") {
                Tracking = SeparateColorChannels(Tracking, 77);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "onlygreen") {
                Tracking = SeparateColorChannels(Tracking, 88);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "onlyblue") {
                Tracking = SeparateColorChannels(Tracking, 99);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "addred") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                int intNum;
                try {
                    intNum = stoi((string)argv[argsUsed]);
                }
                catch (exception& e) {
                    cout << "Invalid argument, expected number." << endl;
                    return 0;
                }
                Tracking = Addcolorred(Tracking, 0, 0, intNum);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "addgreen") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                int intNum;
                try {
                    intNum = stoi((string)argv[argsUsed]);
                }
                catch (exception& e) {
                    cout << "Invalid argument, expected number." << endl;
                    return 0;
                }
                Tracking = Addcolorgreen(Tracking, 0, intNum, 0);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "addblue") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                int intNum;
                try {
                    intNum = stoi((string)argv[argsUsed]);
                }
                catch (exception& e) {
                    cout << "Invalid argument, expected number." << endl;
                    return 0;
                }
                Tracking = Addcolorblue(Tracking, intNum, 0, 0);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "scalered") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                int intNum;
                try {
                    intNum = stoi((string)argv[argsUsed]);
                }
                catch (exception& e) {
                    cout << "Invalid argument, expected number." << endl;
                    return 0;
                }
                Tracking = Scale(Tracking, 1, 1, intNum);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "scalegreen") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                int intNum;
                try {
                    intNum = stoi((string)argv[argsUsed]);
                }
                catch (exception& e) {
                    cout << "Invalid argument, expected number." << endl;
                    return 0;
                }
                Tracking = Scale(Tracking, 1, intNum, 1);
                argsUsed += 1;
            }



            else if ((string)argv[argsUsed] == "scaleblue") {
                argsUsed += 1;
                if (argc <= argsUsed) {
                    cout << "Missing argument." << endl;
                    return 0;
                }
                int intNum;
                try {
                    intNum = stoi((string)argv[argsUsed]);
                }
                catch (exception& e) {
                    cout << "Invalid argument, expected number." << endl;
                    return 0;
                }
                Tracking = Scale(Tracking, intNum, 1, 1);
                argsUsed += 1;
            }



            else {
                cout << "Invalid method name." << endl;
                return 0;
            }
        }
        Tracking.write((string)argv[1]);
    }
    return 0;
}



// This Code also works, However there is a better version above!!

    /*
    /////////////// my code ////////////////
    int argIndexL = 2;

    Image Tracking;
    Tracking.read(string(argv[2]));

    while (argIndexL < argc) {
        //code...
        //code...
        argIndexL += 1;
    }
    Tracking.write(argv[1]);
    return 0;

    // BASICALY
    Image Tracking;
    Tracking.read("opopopoppoop");
    string name = argv[4];
    Image part2;
    part2.read(name);
    Tracking = Multiply(Tracking, part2);









// Original code...

    // Task 1 // part1
    Image Pattern1;
    Pattern1.read("input/pattern1.tga");
    Image Layer1;
    Layer1.read("input/layer1.tga");
    Image part1 = Multiply(Pattern1, Layer1);
    part1.write("output/part1.tga");

    
    // Task 2 // part2
    Image carImage;
    carImage.read("input/car.tga");
    Image Layer2;
    Layer2.read("input/layer2.tga");
    Image part2 = Subtract(carImage, Layer2);
    part2.write("output/part2.tga");
    
    // Task 3 // part3
    Image Layer1_1;
    Layer1_1.read("input/layer1.tga");
    Image Pattern2;
    Pattern2.read("input/pattern2.tga");
    Image text;
    text.read("input/text.tga");
    Image multiply_store = Multiply(Pattern2, Layer1_1);
    Image text_bottom = Screen(multiply_store, text);
    text_bottom.write("output/part3.tga");
    //
    // Task 4 // part4
    Image Layer2_2;
    Layer2_2.read("input/layer2.tga");
    Image circles;
    circles.read("input/circles.tga");
    Image Pattern2_2;
    Pattern2_2.read("input/pattern2.tga");
    Image multiply_store_2 = Multiply(circles, Layer2_2);
    Image load_bottom = Subtract(multiply_store_2, Pattern2_2);
    load_bottom.write("output/part4.tga");
    
    // Task 5 // part5
    Image pattern1;
    Image layer1;
    pattern1.read("input/pattern1.tga");
    layer1.read("input/layer1.tga");
    Image overlay = Overlay(pattern1, layer1);
    overlay.write("output/part5.tga");


    // Task 6 // part6
    Image carImage_2;
    carImage_2.read("input/car.tga");
    Image addGreen = Addcolorgreen(carImage_2, 0, 200, 0);
    addGreen.write("output/part6.tga");
    
    
    // Task 7 // part7
    Image carTGA;
    carTGA.read("input/car.tga");
    // multiply blue 0, green stays same, red by 4
    Image part7 = Scale(carTGA, 0, 1, 4);
    part7.write("output/part7.tga");

    // Task 8 // part8_r.tga // part8_g.tga // part8_b.tga
    Image carImage_3;
    carImage_3.read("input/car.tga");
    Image BLUEchannel = SeparateColorChannels(carImage_3, 99);
    Image GREENchannel = SeparateColorChannels(carImage_3, 88);
    Image REDchannel = SeparateColorChannels(carImage_3, 77);
    BLUEchannel.write("output/part8_b.tga");
    GREENchannel.write("output/part8_g.tga");
    REDchannel.write("output/part8_r.tga");

    
    // Task 9 // part9
    Image blue;
    Image green;
    Image red;
    blue.read("input/layer_blue.tga");
    green.read("input/layer_green.tga");
    red.read("input/layer_red.tga");
    Image part9 = combine(blue, green, red);
    part9.write("output/part9.tga");

    // Task 10 // part10
    Image text2_1;
    text2_1.read("input/text2.tga");
    Image good = Rotate(text2_1);
    good.write("output/part10.tga");
    */

