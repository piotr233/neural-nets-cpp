//
// Created by piotr on 19/11/2021.
//

#ifndef NEURAL_NETS_CPP_NEURAL_NET_LAYER_H_
#define NEURAL_NETS_CPP_NEURAL_NET_LAYER_H_
#include "../matrix/matrix_vector_operations.h"
#include <iostream>

enum class NormalizingFunction { RELU, SIGMOID };

class Layer {
public:
  Layer(size_t previous_layer_height, size_t layer_height,NormalizingFunction activation_function);
  Layer(const Layer &other) = default;
  Layer &operator=(const Layer &other) = default;

  /// feed forward values
  std::vector<double> FeedForward(const std::vector<double> &input) {

    nodes_ = Add(matrix::Mul(input, weights_), biases_);
    nodes_ = ApplyNormalizingFunction(nodes_, activation_function_);
    return nodes_;
  };

  /// sets all weights and biases to random value ranging from 0 to 1
  void FillRandom();

  /// sets all weights to specified value
  /// \param value to witch weights will be set to
  void FillWeights(double value);

  /// sets all biases to specified value
  /// \param value to witch biases will be set to
  void FillBiases(double value);

  const std::vector<double> &GetNodes() const;

  void Show() {
    std::cout << " weights:\n"
              << ToString(weights_) << "\n biases:\n"
              << ToString(biases_) << std::endl;
  };


  size_t GetLayerHeight() const;
  std::vector<double> &GetBiases() ;
  size_t GetPreviousLayerHeight() const;
  matrix::Matrix<double> &GetWeights() ;

  void SetWeights(const matrix::Matrix<double> &weights);
  void SetBiases(const std::vector<double> &biases);

  static double Relu(double val);

  static double Sigmoid(double val) { return 1.0 - 1.0 / (1.0 + exp(val)); }

  static double SigmoidDerivative(double val) {
    return Sigmoid(val) *  (1 - Sigmoid(val));
  }

  std::vector<double> &
  Layer::ApplyNormalizingFunction(std::vector<double> &target_vector,
                                  NormalizingFunction function_type);

protected:
  size_t layer_height;
  size_t previous_layer_height;

  NormalizingFunction activation_function_;

  matrix::Matrix<double> weights_;
  std::vector<double> biases_;
  std::vector<double> nodes_;
};

#endif // NEURAL_NETS_CPP_NEURAL_NET_LAYER_H_
