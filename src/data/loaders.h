#pragma once

#include "data/graphics.h"
#include "data/array.h"
#include "data/data.h"

bool load_image(const char* filename, Color *dest, int *_w = NULL, int *_h = NULL);

bool load_image(const char* filename, Array<Color> &dest, int *_w = NULL, int *_h = NULL);

void reverse_bytes(unsigned char* dest, unsigned char* src, int size);

bool load_mnist_images(const char* filename, DataSet &dest, int samples = 0);

bool load_mnist_labels(const char* filename, DataSet &dest, int num_class, int samples = 0);