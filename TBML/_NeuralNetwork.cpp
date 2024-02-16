#include "stdafx.h"
#include "_NeuralNetwork.h"

namespace tbml
{
	namespace nn
	{
		_NeuralNetwork::_NeuralNetwork(fn::LossFunction&& lossFn)
			: lossFn(lossFn)
		{}

		_NeuralNetwork::_NeuralNetwork(fn::LossFunction&& lossFn, std::vector<_Layer*>&& layers)
			: lossFn(lossFn), layers(layers)
		{}

		void _NeuralNetwork::addLayer(_Layer* layer)
		{
			layers.push_back(layer);
		}

		const _Tensor& _NeuralNetwork::propogate(const _Tensor& input)
		{
			if (layers.size() == 0) return _Tensor::ZERO;

			// Funky layout is to ensure const reference throughout
			layers[0]->propogate(input);
			for (size_t i = 1; i < layers.size(); i++)
			{
				layers[i]->propogate(layers[i - 1]->getPropogateOutput());
			}
			return layers[layers.size() - 1]->getPropogateOutput();
		}

		const _Tensor& _NeuralNetwork::train(const std::vector<_Tensor>& inputs, const std::vector<_Tensor>& expectedOutputs, const _TrainingConfig& config)
		{
			// Stochastic gradient descent without batches
			for (size_t i = 0; i < inputs.size(); i++)
			{
				// Propogate
				const _Tensor& output = propogate(inputs[i]);

				// Calculate loss
				const _Tensor& loss = lossFn(output, expectedOutputs[i]);

				// Backpropogate
				backpropogate(loss);
			}

			// TODO: Implement
			return _Tensor::ZERO;
		}

		void _NeuralNetwork::backpropogate(const _Tensor& loss) const
		{
			// TODO: Implement
		}

		_DenseLayer::_DenseLayer(size_t inputSize, size_t outputSize, fn::ActivationFunction&& actFn, _DenseInitType initType, bool useBias)
		{
			weights = _Tensor({ inputSize, outputSize }, 0);

			if (initType == _DenseInitType::RANDOM)
			{
				weights.map([](float _) { return fn::getRandomFloat() * 2 - 1; });
			}

			if (useBias)
			{
				bias = _Tensor({ 1, outputSize }, 0);

				if (initType == _DenseInitType::RANDOM)
				{
					bias.map([](float _) { return fn::getRandomFloat() * 2 - 1; });
				}
			}
		}

		const _Tensor& _DenseLayer::propogate(const _Tensor& input)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		const _Tensor& _DenseLayer::backpropagate(const _Tensor& dToOut)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		_ConvLayer::_ConvLayer(std::vector<size_t> kernel, std::vector<size_t> stride, fn::ActivationFunction&& actFn)
		{}

		const _Tensor& _ConvLayer::propogate(const _Tensor& input)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		const _Tensor& _ConvLayer::backpropagate(const _Tensor& dToOut)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		_FlattenLayer::_FlattenLayer()
		{}

		const _Tensor& _FlattenLayer::propogate(const _Tensor& input)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		const _Tensor& _FlattenLayer::backpropagate(const _Tensor& dToOut)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		_MaxPoolLayer::_MaxPoolLayer()
		{}

		const _Tensor& _MaxPoolLayer::propogate(const _Tensor& input)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}

		const _Tensor& _MaxPoolLayer::backpropagate(const _Tensor& dToOut)
		{
			// TODO: Implement
			return _Tensor::ZERO;
		}
	}
}
