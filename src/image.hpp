/*** image.h  Javi Agenjo (javi.agenjo@gmail.com) 2013
    This file defines the class Image that allows to manipulate images.
    It defines all the need operators for Color and Image.
    It has a TGA loader and saver.
***/

#ifndef IMAGE_H
#define IMAGE_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

float clamp(float x, float a, float b) {
    return x < a ? a : (x > b ? b : x);
}

class Color
{
public:
    const union {
        struct {
            float r;
            float g;
            float b;
        }; // not standard!
        float v[3];
    };

    Color() {
        r = g = b = 0.0;
    }
    Color(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    void set(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

Color operator * (const Color& c,float v) {
    return Color(c.r*v, c.g*v, c.b*v);
}
void operator *= (Color& c,float v) {
    c = c * v;
}
Color operator / (const Color& c,float v) {
    return Color(c.r/v, c.g/v, c.b/v);
}
void operator /= (Color& c,float v) {
    c = c / v;
}
Color operator * (float v, const Color& c) {
    return Color(c.r*v, c.g*v, c.b*v);
}
Color operator + (const Color& a, const Color& b) {
    return Color(a.r+b.r, a.g+b.g, a.b+b.b);
}
void operator += (Color& a,const Color& b) {
    a = a + b;
}
Color operator - (const Color& a, const Color& b) {
    return Color(a.r-b.r, a.g-b.g, a.b-b.b);
}
void operator -= (Color& a,const Color& b) {
    a = a - b;
}
Color toGrayscale(Color& c) {
    float value = 0.3*c.r + 0.6*c.g + 0.1*c.b;
    return Color(value,value,value);
}

class Image
{
    //a general struct to store all the information about a TGA file
    typedef struct sTGAInfo
    {
        unsigned int width;
        unsigned int height;
        unsigned int bpp; //bits per pixel
        unsigned char* data; //bytes with the pixel information
    } TGAInfo;

public:
    unsigned int width;
    unsigned int height;
    Color* pixels;
    float* z_buffer;

    /* CONSTRUCTORS */
    Image() {
        width = 0;
        height = 0;
        pixels = NULL;
    }

    Image(unsigned int width, unsigned int height)
    {
        this->width = width;
        this->height = height;
        pixels = new Color[width*height];
        z_buffer = new float[width*height];
        memset(pixels, 0, width * height * sizeof(Color));
        memset(z_buffer, 0, width * height * sizeof(float));
    }

    //copy constructor
    Image(const Image& c) {
        pixels = NULL;
        z_buffer = NULL;
        width = c.width;
        height = c.height;
        if(c.pixels)
        {
            pixels = new Color[width*height];
            z_buffer = new float[width*height];           
            memcpy(pixels, c.pixels, width*height*sizeof(Color));
            memcpy(z_buffer, c.z_buffer, width * height * sizeof(float));
            
        }
    }

    //assign operator
    Image& operator = (const Image& c)
    {
        if(pixels) {
            delete [] pixels;
            pixels = NULL;
            delete [] z_buffer;
            z_buffer = NULL;
        }

        width = c.width;
        height = c.height;
        if(c.pixels)
        {
            pixels = new Color[width*height*sizeof(Color)];
            z_buffer = new float[width*height];           
            memcpy(pixels, c.pixels, width*height*sizeof(Color));
            memcpy(z_buffer, c.z_buffer, width * height * sizeof(float));
        }
        return *this;
    }

    ~Image()
    {
        if(pixels) {
            delete [] pixels;
            delete [] z_buffer;
        }
    }

    //get the pixel at position x,y
    Color getPixel(unsigned int x, unsigned int y) const
    {
        return pixels[ y * width + x ];
    }

    //set the pixel at position x,y with value C
    void setPixel(const Color& c, unsigned int x, unsigned int y)
    {
        pixels[ y * width + x ] = c;
    }

    bool setPixelWithDepthTest(const Color& c, unsigned int x, unsigned int y, float z) {
        // lower is closer. Returns whether the pixel was painted or not.
        if (z < z_buffer[ y * width + x ]) {
            setPixel(c, x, y);
            z_buffer[ y * width + x ] = z;
            return true;
        }
        return false;
    }

    
    bool isInBounds(unsigned x, unsigned y) {
        return ( x >= 0 && x < width && y >= 0 && y < height);
    }

    //Loads an image from a TGA file
    bool loadTGA(const char* filename)
    {
        unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        unsigned char TGAcompare[12];
        unsigned char header[6];
        unsigned int bytesPerPixel;
        unsigned int imageSize;

        FILE * file = fopen(filename, "rb");
        if ( file == NULL || fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||
                memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||
                fread(header, 1, sizeof(header), file) != sizeof(header))
        {
            std::cerr << "File not found: " << filename << std::endl;
            if (file == NULL)
                return NULL;
            else
            {
                fclose(file);
                return NULL;
            }
        }

        TGAInfo* tgainfo = new TGAInfo;

        tgainfo->width = header[1] * 256 + header[0];
        tgainfo->height = header[3] * 256 + header[2];

        if (tgainfo->width <= 0 || tgainfo->height <= 0 || (header[4] != 24 && header[4] != 32))
        {
            fclose(file);
            delete tgainfo;
            return NULL;
        }

        tgainfo->bpp = header[4];
        bytesPerPixel = tgainfo->bpp / 8;
        imageSize = tgainfo->width * tgainfo->height * bytesPerPixel;

        tgainfo->data = new unsigned char[imageSize];

        if (tgainfo->data == NULL || fread(tgainfo->data, 1, imageSize, file) != imageSize)
        {
            if (tgainfo->data != NULL)
                delete tgainfo->data;

            fclose(file);
            delete tgainfo;
            return false;
        }

        fclose(file);

        //save info in image
        if(pixels)
            delete pixels;

        width = tgainfo->width;
        height = tgainfo->height;
        pixels = new Color[width*height];

        //convert to float all pixels
        for(unsigned int y = 0; y < height; ++y)
            for(unsigned int x = 0; x < width; ++x)
            {
                unsigned int pos = y * width * bytesPerPixel + x * bytesPerPixel;
                this->setPixel(Color( tgainfo->data[pos+2] / 255.0f, tgainfo->data[pos+1] / 255.0f, tgainfo->data[pos] / 255.0f),x,height - y - 1);
            }

        delete [] tgainfo->data;
        delete tgainfo;

        return true;
    }

    // Saves the image to a TGA file
    bool saveTGA(const char* filename)
    {
        unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        FILE *file = fopen(filename, "wb");
        if ( file == NULL )
        {
            fclose(file);
            return false;
        }

        unsigned short header_short[3];
        header_short[0] = width;
        header_short[1] = height;
        unsigned char* header = (unsigned char*)header_short;
        header[4] = 24;
        header[5] = 0;

        //tgainfo->width = header[1] * 256 + header[0];
        //tgainfo->height = header[3] * 256 + header[2];

        fwrite(TGAheader, 1, sizeof(TGAheader), file);
        fwrite(header, 1, 6, file);

        //convert pixels to unsigned char
        unsigned char* bytes = new unsigned char[width*height*3];
        for(unsigned int y = 0; y < height; ++y)
            for(unsigned int x = 0; x < width; ++x)
            {
                Color c = pixels[(height-y-1)*width+x];
                unsigned int pos = (y*width+x)*3;
                bytes[pos+2] = (unsigned char)clamp(c.r * 255,0,255);
                bytes[pos+1] = (unsigned char)clamp(c.g * 255,0,255);
                bytes[pos] = (unsigned char)clamp(c.b * 255,0,255);
            }

        fwrite(bytes, 1, width*height*3, file);
        delete [] bytes;

        fclose(file);
        return true;
    }
};

#endif
