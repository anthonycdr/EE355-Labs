#include "lodepng.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// A simple class to handle PNG images
class PNGImage {
public:
    std::vector<unsigned char> image; // stores image data in RGBA format
    unsigned width, height;

    PNGImage() : width(0), height(0) {}

    // Load a PNG file into the image vector.
    bool load(const std::string &filename) {
	//...
        unsigned error = lodepng::decode(image, width, height, filename);
        if (error) {
            std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            return false;
    }
    std::cout << "Image loaded successfully: " << width << "x" << height << std::endl; 
    return true;
}

    // Save the image vector into a PNG file.
    bool save(const std::string &filename) {
   	//...
       unsigned error = lodepng::encode(filename, image, width, height);
        if (error) {
            std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
            return false;
        }
        std::cout << "Image saved successfully as " << filename << std::endl;
        return true;
    }
};

// Function to apply a tint by scaling the red, green, and blue channels.
void tintImage(std::vector<unsigned char>& image, double rFactor, double gFactor, double bFactor) {
		//...
        for (size_t i = 0; i < image.size(); i += 4) {
            image[i]     = std::min(255, static_cast<int>(image[i] * rFactor));
            image[i + 1] = std::min(255, static_cast<int>(image[i + 1] * gFactor));
            image[i + 2] = std::min(255, static_cast<int>(image[i + 2] * bFactor));
        }
    }

// Function to invert the image colors.
void invertImage(std::vector<unsigned char>& image) {
		//...
        for (size_t i = 0; i < image.size(); i += 4) {
            image[i]     = 255 - image[i];
            image[i + 1] = 255 - image[i + 1];
            image[i + 2] = 255 - image[i + 2];
        }
    }

// Function to add Gaussian noise to the image.
void addGaussianNoise(std::vector<unsigned char>& image, double mean, double stddev) {
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(mean, stddev);
    //...
    for (size_t i = 0; i < image.size(); i += 4) {
        int noiseR = static_cast<int>(d(gen));
        int noiseG = static_cast<int>(d(gen));
        int noiseB = static_cast<int>(d(gen));
        image[i]     = std::min(255, std::max(0, static_cast<int>(image[i]) + noiseR));
        image[i + 1] = std::min(255, std::max(0, static_cast<int>(image[i + 1]) + noiseG));
        image[i + 2] = std::min(255, std::max(0, static_cast<int>(image[i + 2]) + noiseB));
    }
    
}

// Function to add salt-and-pepper noise to the image.
void addSaltPepperNoise(std::vector<unsigned char>& image, double noiseRatio) {
    size_t totalPixels = image.size() / 4;
    size_t numNoisy = static_cast<size_t>(totalPixels * noiseRatio);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, totalPixels - 1);
    //...
    for (size_t i = 0; i < numNoisy; i++) {
        size_t index = dis(gen) * 4;
        image[index]     = 0;
        image[index + 1] = 0;
        image[index + 2] = 0;

    }
}

// Function to zoom the image using nearest-neighbor interpolation.
std::vector<unsigned char> zoomImage(const std::vector<unsigned char>& image, unsigned width, unsigned height, double scale, unsigned &newWidth, unsigned &newHeight) {
	//...
	newWidth = static_cast<unsigned>(width * scale);
    newHeight = static_cast<unsigned>(height * scale);
    std::vector<unsigned char> zoomed(newWidth * newHeight * 4);
	
    for(unsigned y = 0; y < newHeight; y++) {
        for(unsigned x = 0; x < newWidth; x++) {
            int srcX = static_cast<int>(x / scale);
            int srcY = static_cast<int>(y / scale);
            size_t srcIndex = (srcY * width + srcX) * 4;
            size_t dstIndex = (y * newWidth + x) * 4;
            zoomed[dstIndex]     = image[srcIndex];
            zoomed[dstIndex + 1] = image[srcIndex + 1];
            zoomed[dstIndex + 2] = image[srcIndex + 2];
            zoomed[dstIndex + 3] = 255;
        }
    }
    return zoomed;
}

// Function to apply a glass effect.
// For each pixel, a nearby random pixel (within a specified radius) is used.
std::vector<unsigned char> glassEffect(const std::vector<unsigned char>& src, unsigned width, unsigned height, int radius) {
    std::vector<unsigned char> dst(src.size());
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(-radius, radius);
    //...
    for(unsigned y = 0; y < height; y++) {
        for(unsigned x = 0; x < width; x++) {
            int offsetX = dis(gen);
            int offsetY = dis(gen);
            int newX = std::min(width - 1, std::max(0, static_cast<int>(x + offsetX)));
            int newY = std::min(height - 1, std::max(0, static_cast<int>(y + offsetY));
            size_t srcIndex = (newY * width + newX) * 4;
            size_t dstIndex = (y * width + x) * 4;
            dst[dstIndex]     = src[srcIndex];
            dst[dstIndex + 1] = src[srcIndex + 1];
            dst[dstIndex + 2] = src[srcIndex + 2];
            dst[dstIndex + 3] = 255;
        }
    }
    return dst;
}

// Function to perform edge detection using a Sobel-like operator.
// The image is converted to grayscale and the edge magnitude is computed.
std::vector<unsigned char> edgeDetection(const std::vector<unsigned char>& src, unsigned width, unsigned height) {
    std::vector<unsigned char> dst(src.size(), 255); // Initialize with white pixels.
    std::vector<unsigned char> gray(width * height, 0);
    // Convert to grayscale.
    //...
    for(size_t i = 0; i < src.size(); i += 4) {
        gray[i / 4] = static_cast<unsigned char>(0.299 * src[i] + 0.587 * src[i + 1] + 0.114 * src[i + 2]);
    }

    // Apply a simple Sobel operator.
    for (unsigned y = 1; y < height - 1; y++) {
        for (unsigned x = 1; x < width - 1; x++) {
            int gx = -gray[(y-1)*width + (x-1)] + gray[(y-1)*width + (x+1)]
                     -2 * gray[y*width + (x-1)] + 2 * gray[y*width + (x+1)]
                     -gray[(y+1)*width + (x-1)] + gray[(y+1)*width + (x+1)];
            int gy = -gray[(y-1)*width + (x-1)] - 2 * gray[(y-1)*width + x] - gray[(y-1)*width + (x+1)]
                     + gray[(y+1)*width + (x-1)] + 2 * gray[(y+1)*width + x] + gray[(y+1)*width + (x+1)];
            int edgeVal = std::min(255, abs(gx) + abs(gy));
            size_t dstIndex = (y * width + x) * 4;
            dst[dstIndex]   = edgeVal;
            dst[dstIndex+1] = edgeVal;
            dst[dstIndex+2] = edgeVal;
            dst[dstIndex+3] = 255;
        }
    }
    return dst;
}

// Function to smooth the image using a simple 3x3 average filter.
std::vector<unsigned char> smoothImage(const std::vector<unsigned char>& src, unsigned width, unsigned height) {
    std::vector<unsigned char> dst(src.size());
    //...
    for(unsigned y = 1; y < height - 1; y++) {
        for(unsigned x = 1; x < width - 1; x++) {
            int sumR = 0, sumG = 0, sumB = 0;
            for(int dy = -1; dy <= 1; dy++) {
                for(int dx = -1; dx <= 1; dx++) {
                    size_t srcIndex = ((y + dy) * width + (x + dx)) * 4;
                    sumR += src[srcIndex];
                    sumG += src[srcIndex + 1];
                    sumB += src[srcIndex + 2];
                }
            }
            size_t dstIndex = (y * width + x) * 4;
            dst[dstIndex]     = sumR / 9;
            dst[dstIndex + 1] = sumG / 9;
            dst[dstIndex + 2] = sumB / 9;
            dst[dstIndex + 3] = 255;
        }
    }
        return dst;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: png_lab <input_png_file>" << endl;
        return 1;
    }

    string inputFile = argv[1];
    PNGImage img;
    if (!img.load(inputFile)) {
        cerr << "Error: Could not load the image file." << endl;
        return 1;
    }

    // Create copies of the image data for each operation.
    vector<unsigned char> tinted       = img.image;
    vector<unsigned char> inverted     = img.image;
    vector<unsigned char> gaussianNoisy = img.image;
    vector<unsigned char> spNoisy       = img.image;

    // Apply tint: Increase the red channel.
    tintImage(tinted, 1.2, 1.0, 1.0);

    // Invert colors.
    invertImage(inverted);

    // Add Gaussian noise (mean=0, stddev=30).
    addGaussianNoise(gaussianNoisy, 0.0, 30.0);

    // Add salt-and-pepper noise (affect 5% of pixels).
    addSaltPepperNoise(spNoisy, 0.05);

    // Zoom the image by a factor of 1.5.
    unsigned newWidth, newHeight;
    vector<unsigned char> zoomed = zoomImage(img.image, img.width, img.height, 1.5, newWidth, newHeight);

    // Apply glass effect with a displacement radius of 3.
    vector<unsigned char> glass = glassEffect(img.image, img.width, img.height, 3);

    // Perform edge detection.
    vector<unsigned char> edges = edgeDetection(img.image, img.width, img.height);

    // Smooth the image using a 3x3 average.
    vector<unsigned char> smooth = smoothImage(img.image, img.width, img.height);

    // Save all output images.
    PNGImage outImg;
    outImg.width = img.width;
    outImg.height = img.height;

    outImg.image = tinted;
    outImg.save("tinted.png");

    outImg.image = inverted;
    outImg.save("inverted.png");

    outImg.image = gaussianNoisy;
    outImg.save("gaussian_noisy.png");

    outImg.image = spNoisy;
    outImg.save("saltpepper_noisy.png");

    outImg.image = zoomed;
    outImg.width = newWidth;
    outImg.height = newHeight;
    outImg.save("zoomed.png");

    outImg.image = glass;
    outImg.width = img.width;
    outImg.height = img.height;
    outImg.save("glass.png");

    outImg.image = edges;
    outImg.width = img.width;
    outImg.height = img.height;
    outImg.save("edge.png");

    outImg.image = smooth;
    outImg.width = img.width;
    outImg.height = img.height;
    outImg.save("smooth.png");

    cout << "Processing completed. Check the output PNG files." << endl;
    return 0;
}
