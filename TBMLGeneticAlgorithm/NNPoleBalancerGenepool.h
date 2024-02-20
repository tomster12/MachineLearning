#pragma once

#include "GenepoolSimulation.h"
#include "CommonImpl.h"

// https://researchbank.swinburne.edu.au/file/62a8df69-4a2c-407f-8040-5ac533fc2787/1/PDF%20(12%20pages).pdf
class NNPoleBalancerGenepool;
class NNPoleBalancerAgent : public tbml::ga::Agent<NNGenome>
{
public:
	NNPoleBalancerAgent(NNPoleBalancerAgent::GenomePtr&& genome) : Agent(std::move(genome)) {};
	NNPoleBalancerAgent(
		float cartMass, float poleMass, float poleLength, float force,
		float trackLimit, float angleLimit, float timeLimit,
		NNPoleBalancerAgent::GenomePtr&& genome);
	void initVisual();

	bool step() override;
	void render(sf::RenderWindow* window) override;

	float calculateFitness();

private:
	const float g = 9.81f;
	const float timeStep = 0.02f;
	const float METRE_TO_UNIT = 200.0f;

	sf::RectangleShape cartShape;
	sf::RectangleShape poleShape;

	float cartMass = 1.0f;
	float poleMass = 0.1f;
	float poleLength = 0.5f;
	float force = 1;
	float trackLimit = 2.4f;
	float angleLimit = 0.21f;
	float timeLimit = 5.0f;

	tbml::Matrix netInput;
	float poleAngle = 0.0f;
	float poleVelocity = 0.0f;
	float poleAcceleration = 0.0f;
	float cartPosition = 0.0f;
	float cartVelocity = 0.0f;
	float cartAcceleration = 0.0f;
	float time = 0.0f;
};

class NNPoleBalancerGenepool : public tbml::ga::Genepool<NNGenome, NNPoleBalancerAgent>
{
public:
	NNPoleBalancerGenepool(
		float cartMass, float poleMass, float poleLength, float force,
		float trackLimit, float angleLimit, float timeLimit,
		std::vector<size_t> layerSizes, std::vector<tbml::fn::ActivationFunction> actFns);

protected:
	float cartMass;
	float poleMass;
	float poleLength;
	float force;
	float trackLimit;
	float angleLimit;
	float timeLimit;
	std::vector<size_t> layerSizes;
	std::vector<tbml::fn::ActivationFunction> actFns;

	GenomePtr createGenome() const override;
	AgentPtr createAgent(GenomePtr&& data) const override;
};