#include <iostream>
#include <random>

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

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins)
{
    std::uint32_t step = howMany / numberBins;
    std::vector<DistributionPair> uniformDist;

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(min, max);

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
    return uniformDist;
};

// std::vector < DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins)
//{
//};

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
