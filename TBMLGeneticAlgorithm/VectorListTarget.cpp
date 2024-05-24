#include "stdafx.h"
#include "VectorListTarget.h"
#include "CommonImpl.h"
#include "Utility.h"

VectorListTargetAgent::VectorListTargetAgent(
	VectorListTargetAgent::GenomeCPtr&& genome, const VectorListTargetGenepool* genepool,
	sf::Vector2f startPos, float radius, float moveAcc)
	: Agent(std::move(genome)), genepool(genepool),
	pos(startPos), radius(radius), moveAcc(moveAcc), currentIndex(0)
{}

void VectorListTargetAgent::initVisual()
{
	if (isVisualInit) return;

	// Set up shape
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.0f);

	isVisualInit = true;
}

bool VectorListTargetAgent::evaluate()
{
	if (isFinished) return true;

	// Move position by current vector
	sf::Vector2f nextDir = genome->getValue(currentIndex);
	pos.x += nextDir.x * moveAcc;
	pos.y += nextDir.y * moveAcc;
	currentIndex++;

	// Check finish conditions
	float dist = calculateDist();
	if (currentIndex == genome->getSize() || dist < 0.0f)
	{
		calculateFitness();
		isFinished = true;
	}
	return isFinished;
};

void VectorListTargetAgent::render(sf::RenderWindow* window)
{
	if (!isVisualInit) initVisual();

	// Update shape position and colour
	shape.setPosition(pos.x, pos.y);

	// Draw shape to window
	window->draw(shape);
};

float VectorListTargetAgent::calculateDist()
{
	// Calculate distance to target
	float dx = genepool->getTargetPos().x - pos.x;
	float dy = genepool->getTargetPos().y - pos.y;
	float fullDistSq = sqrt(dx * dx + dy * dy);
	float radii = radius + genepool->getTargetRadius();
	return fullDistSq - radii;
}

float VectorListTargetAgent::calculateFitness()
{
	// Calculate fitness
	float dist = calculateDist();
	fitness = 0.0f;
	if (dist > 0.0f)
	{
		fitness = 0.5f * (1.0f - dist / 500.0f);
		fitness = fitness < 0.0f ? 0.0f : fitness;
	}
	else
	{
		float dataPct = static_cast<float>(currentIndex) / static_cast<float>(genome->getSize());
		fitness = 1.0f - 0.5f * dataPct;
	}

	return fitness;
};

VectorListTargetGenepool::VectorListTargetGenepool(
	std::function<GenomeCnPtr(void)> createGenomeFn, std::function<AgentPtr(GenomeCnPtr)> createAgentFn,
	sf::Vector2f targetPos, float targetRadius)
	: Genepool(createGenomeFn, createAgentFn), targetPos(targetPos), targetRadius(targetRadius)
{
	initVisual();
}

void VectorListTargetGenepool::initVisual()
{
	// Initialize variables
	target.setPosition(targetPos);
	target.setRadius(targetRadius);
	target.setOrigin(targetRadius, targetRadius);
	target.setFillColor(sf::Color::Transparent);
	target.setOutlineColor(sf::Color::White);
	target.setOutlineThickness(1.0f);
};

void VectorListTargetGenepool::render(sf::RenderWindow* window)
{
	Genepool::render(window);

	// Draw target
	window->draw(target);
}

sf::Vector2f VectorListTargetGenepool::getTargetPos() const { return targetPos; }

float VectorListTargetGenepool::getTargetRadius() const { return targetRadius; }
