
#include "layers/neural_layers.h"
#include "utils/utils.h"

void FullLayer::init(Shape _in_shape)
{
    parameters.resize(2);
    parameters[0] = Parameter(in_size * out_size, weight_decay);
    parameters[1] = Parameter(out_size);

    W = parameters[0].values;
    dW = parameters[0].gradients;
    B = parameters[1].values;
    dB = parameters[1].gradients;

    for (int i = 0; i < out_size; i++)
    {
        B[i] = random(-1.0f, 1.0f);
        dB[i] = 0;
    }
    for (int i = 0; i < in_size * out_size; i++)
    {
        W[i] = random(-1.0f, 1.0f);
        dW[i] = 0;
    }

    setTrainable(true);
}

float* FullLayer::forward(float* input)
{
    X.data = input;

    for (int i = 0; i < out_size; i++)
    {
        Y[i] = B[i];
        for (int j = 0; j < in_size; j++)
        {
            Y[i] += X[j] * W[i + j * out_size];
        }
    }

    return Y.data;
}

float* FullLayer::backward(float* d_output)
{
    dY.data = d_output;

    if (trainable)
    {
        for (int i = 0; i < out_size; i++)
        {
            dB[i] += dY[i];
            for (int j = 0; j < in_size; j++)
            {
                dW[i + j * out_size] += X[j] * dY[i];
            }
        }
    }

    for (int i = 0; i < in_size; i++)
    {
        dX[i] = 0;
        for (int j = 0; j < out_size; j++)
        {
            dX[i] += W[j + i * out_size] * dY[j];
        }
    }

    return dX.data;
}

void FullLayer::save(std::ofstream& file)
{
    file.write((char*)&weight_decay, sizeof(float));
}

void FullLayer::load(std::ifstream& file)
{
    file.read((char*)&weight_decay, sizeof(float));
}

FullLayer::FullLayer()
{
    type = FULL_LAYER;
}
FullLayer::FullLayer(int _size, float _weight_decay, Shape _out_shape)
{
    trainable = true;
    weight_decay = _weight_decay;
    type = FULL_LAYER;
    out_size = _size;

    if (_out_shape.size() == 0)
    {
        out_shape = { out_size, 1, 1 };
    }
    else
    {
        out_shape = _out_shape;
    }
}
