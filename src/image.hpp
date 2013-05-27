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
#include <array>

float clamp(float x, float a, float b) { return x < a ? a : (x > b ? b : x); }

class Color
{
public:
    const union {
        struct { float r; float g; float b; }; // not standard!
        float v[3];
    };

    Color() { r = g = b = 0.0; }
    Color(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
    void set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

Color operator * (const Color& c,float v) { return Color(c.r*v, c.g*v, c.b*v); }
void operator *= (Color& c,float v) { c = c * v; }
Color operator / (const Color& c,float v) { return Color(c.r/v, c.g/v, c.b/v); }
void operator /= (Color& c,float v) { c = c / v; }
Color operator * (float v, const Color& c) { return Color(c.r*v, c.g*v, c.b*v); }
Color operator + (const Color& a, const Color& b) { return Color(a.r+b.r, a.g+b.g, a.b+b.b); }
void operator += (Color& a,const Color& b) { a = a + b; }
Color operator - (const Color& a, const Color& b) { return Color(a.r-b.r, a.g-b.g, a.b-b.b); }
void operator -= (Color& a,const Color& b) { a = a - b; }
Color toGrayscale(Color& c) { float value = 0.3*c.r + 0.6*c.g + 0.1*c.b; return Color(value,value,value);}

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

    /* CONSTRUCTORS */
    Image() {
        width = 0; height = 0;
        pixels = NULL;
    }

    Image(unsigned int width, unsigned int height)
    {
        this->width = width;
        this->height = height;
        pixels = new Color[width*height];
        memset(pixels, 0, width * height * sizeof(Color));
    }

    //copy constructor
    Image(const Image& c) {
        pixels = NULL;
        width = c.width;
        height = c.height;
        if(c.pixels)
        {
            pixels = new Color[width*height];
            memcpy(pixels, c.pixels, width*height*sizeof(Color));
        }
    }

    //assign operator
    Image& operator = (const Image& c)
    {
        if(pixels) delete [] pixels;
        pixels = NULL;

        width = c.width;
        height = c.height;
        if(c.pixels)
        {
            pixels = new Color[width*height*sizeof(Color)];
            memcpy(pixels, c.pixels, width*height*sizeof(Color));
        }
        return *this;
    }

    ~Image()
    {
        if(pixels) delete [] pixels;
    }

    //get the pixel at position x,y
    Color getPixel(unsigned int x, unsigned int y) const 
    {
        return pixels[ y * width + x ];
    }

    //set the pixel at position x,y with value C
    void setPixel(const Color& c, unsigned int x, unsigned int y)
    {
        std::cout << "Setting pixel " << x << ", " << y << std::endl;
        pixels[ y * width + x ] = c;
    }

    //change image size (the old one will remain in the top-left corner)
    void resize(unsigned int width, unsigned int height)
    {
        Color* new_pixels = new Color[width*height];
        unsigned int min_width = this->width > width ? width : this->width;
        unsigned int min_height = this->height > height ? height : this->height;

        for(unsigned int x = 0; x < min_width; ++x)
            for(unsigned int y = 0; y < min_height; ++y)
                new_pixels[ y * width + x ] = getPixel(x,y);

        delete [] pixels;
        this->width = width;
        this->height = height;
        pixels = new_pixels;
    }

    //flip the image top-down
    void flipY()
    {
        for(unsigned int x = 0; x < width; ++x)
            for(unsigned int y = 0; y < height * 0.5; ++y)
            {
                Color temp = getPixel(x, height - y - 1);
                setPixel( getPixel(x,y), x, height - y - 1);
                setPixel( temp, x, y );
            }
    }

    //flip the image left-right
    void flipX()
    {
        for(unsigned int x = 0; x < width * 0.5; ++x)
        {
            for(unsigned int y = 0; y < height; ++y)
            {
                Color temp = getPixel(width - x - 1, y);
                setPixel( getPixel(x,y), width - x - 1, y);
                setPixel( temp, x, y );
            }
        }
    }

    void transpose()
    {
        if(pixels == NULL) return;
        Color *new_pixels = new Color[width*height];
        for(unsigned int x = 0; x < width; x++)
        {
            for(unsigned int y = 0; y < height; y++)
            {
                new_pixels[ x * height + y ] = getPixel(x,y);
            }
        }
        unsigned int tmp = height;
        height = width;
        width = tmp;
        delete [] pixels;
        pixels = new_pixels;
    }

    void normalize() {
        float max = 0;
        for(unsigned i = 0; i < width*height; ++i) {
            if(pixels[i].r > max) max = pixels[i].r;
        }
        forEachPixel([max](Color c){return c / max;});
    }

    //fill the image with the color C
    void fill(const Color& c)
    {
        for(unsigned int pos = 0; pos < width*height; ++pos)
            pixels[pos] = c;
    }

    //returns a new image with the area from (startx,starty) of size width,height
    Image getArea(unsigned int start_x, unsigned int start_y, unsigned int width, unsigned int height)
    {
        Image result(width, height);
        for(unsigned int x = 0; x < width; ++x)
            for(unsigned int y = 0; y < height; ++x)
            {
                if( (x + start_x) < this->width && (y + start_y) < this->height) 
                    result.setPixel( getPixel(x + start_x,y + start_y), x, y);
            }
        return result;
    }

    #ifndef IGNORE_LAMBDAS

    //applies an algorithm to every pixel in an image
    // you can use lambda sintax:   img.forEachPixel( [](Color c) { return c*2; });
    // or callback sintax:   img.forEachPixel( mycallback ); //the callback has to be Color mycallback(Color c) { ... }
    template <typename F>
    Image& forEachPixel( F callback )
    {
        for(unsigned int pos = 0; pos < width*height; ++pos)
            pixels[pos] = callback(pixels[pos]);
        return *this;
    }

    #endif

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

#ifndef IGNORE_LAMBDAS

//you can apply and algorithm for two images and store the result in the first one
//forEachPixel( img, img2, [](Color a, Color b) { return a + b; } );
template <typename F>
void forEachPixel(Image& img, const Image& img2, F f) {
    for(unsigned int pos = 0; pos < img.width * img.height; ++pos)
        img.pixels[pos] = f( img.pixels[pos], img2.pixels[pos] );
}

#endif

#endif
