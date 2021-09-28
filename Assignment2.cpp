// Assignment 2 Random Distributions
// Makalee Beelek

// This program generates and plots Uniform, Normal, and Poisson
// distributions.

// include directive
#include <iostream>
#include <random>

// Given class definition for DistributionPair
class DistributionPair
{
  public:
    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }

    std::uint32_t minValue;
    std::uint32_t maxValue;
    std::uint32_t count;
};

// generateUniformDistribution function
// inputs:
//      -howMany: how many integers to randomly generate
//      -min: the minimum number a randomly generated integer can be
//      -max: the maximum number a randomly generated integer can be
//      -numberBins: how many bins to place the numbers in
// outputs:
//      return a DistributionPair vector that is a vector with numberBins
//      amount of bins, each with their specified range and count
// a function that generates howMany random numbers using uniform distribution
// and bins them based on their value
std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    // the range of a bin
    std::uint32_t step = howMany / numberBins;
    // initialize the vector to be returned
    std::vector<DistributionPair> uniformDist;

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(min, max);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        if (i == 0)
        {
            uniformDist.push_back(DistributionPair(0, step));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMax = uniformDist[previousIndex].maxValue;
            uniformDist.push_back(DistributionPair(previousMax + 1, previousMax + 1 + step));
        }
    }

    // randomly generate a number and add 1 to the count of the correct bin
    for (std::uint32_t j = 0; j < howMany; j++)
    {
        std::uint32_t randNum = dist(engine);

        for (int k = 0; k < numberBins; k++)
        {
            if (k == 0)
            {
                if (randNum <= uniformDist[k].maxValue)
                {
                    uniformDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= uniformDist[k].minValue)
                {
                    uniformDist[k].count++;
                }
            }
            else
            {
                if (randNum >= uniformDist[k].minValue && randNum <= uniformDist[k].maxValue)
                {
                    uniformDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return uniformDist;
};

// generateNormalDistribution function
// inputs:
//      -howMany: how many integers to randomly generate
//      -mean: the average of the distribution
//      -stdev: the standard deviation of the distribution
//      -numberBins: how many bins to place the numbers in
// outputs:
//      return a DistributionPair vector that is a vector with numberBins
//      amount of bins, each with their specified range and count
// a function that generates howMany random numbers using normal distribution
// and bins them based on their value
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
{
    // the range of a bin
    std::uint32_t step = howMany / numberBins;
    // initialize the vector to be returned
    std::vector<DistributionPair> uniformDist;

    // get the overall min
    float min = mean - 4 * stdev;
    // get the overall max
    float max = mean + 4 * stdev - 1;

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::normal_distribution<float> dist(min, max);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        if (i == 0)
        {
            uniformDist.push_back(DistributionPair(0, step));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMax = uniformDist[previousIndex].maxValue;
            uniformDist.push_back(DistributionPair(previousMax + 1, previousMax + 1 + step));
        }
    }

    // randomly generate a number and add 1 to the count of the correct bin
    for (std::uint32_t j = 0; j < howMany; j++)
    {
        float randNum = dist(engine);

        for (int k = 0; k < numberBins; k++)
        {
            if (k == 0)
            {
                if (randNum <= uniformDist[k].maxValue)
                {
                    uniformDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= uniformDist[k].minValue)
                {
                    uniformDist[k].count++;
                }
            }
            else
            {
                if (randNum >= uniformDist[k].minValue && randNum <= uniformDist[k].maxValue)
                {
                    uniformDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return uniformDist;
};

//std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
//{
//};

//void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
//{
//};

int main()
{
    std::vector<DistributionPair> uniformDist = generateUniformDistribution(10, 1, 10, 2);
    for (int i = 0; i < uniformDist.size(); i++)
    {
        std::cout << uniformDist[i].count << std::endl;
    }
    return 0;
}
