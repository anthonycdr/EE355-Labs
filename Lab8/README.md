
Name: Anthony Chandra

1. PNG Image Handling
- PNGImage:
  - Loads a PNG file into an std::vector<unsigned char> containing pixel data in RGBA format.
  - Saves processed image data as a PNG file.
  
2. Image Processing Functions
Each function modifies the pixel values stored in a vector.

- Tinting (`tintImage`)
  - Loops through the image vector in steps (RGBA format) then multiplies the red, green, and blue channels by given factors while ensuring values don’t exceed 255.

- Color Inversion (`invertImage`)
  - Iterates through the image vector steps, subtracting each RGB value from 255 to produce an inverted color effect - so e.g. 255 - (RGB Value).

- Gaussian Noise (`addGaussianNoise`) 
  - Uses a normal distribution generator to create random noise values for each pixel's RGB channels then adding the noise while making sure that the values are within the range of 0-255.

- Salt-and-Pepper Noise (`addSaltPepperNoise`)  
  - Randomly selects a percentage of pixels based on `noiseRatio` and sets them to either black (0,0,0) or white (255,255,255) to simulate noise distortion.

- Zooming (`zoomImage`)
  - Create a new image buffer and maps each pixel in the new image to a corresponding nearest neighbor pixel in the original image based on the zoom scale.

- Glass Effect (`glassEffect`)  
  - Randomly changes each pixel's coordinates within a given radius, making sure that the new coordinates remain within valid bounds, and then assigning the pixel color from the new position.

- Edge Detection (`edgeDetection`) 
  - Using weighted RGB values to change image to grayscale, then applies a **Sobel operator** to detect edges by calculating gradient magnitudes in the x and y directions.

- Smoothing (`smoothImage`)
   - Iterates through the image, averaging the values of each pixel with its surrounding 3×3 pixels to create a blur effect.
