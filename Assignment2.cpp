// Assignment 2 Random Distributions
// Makalee Beelek

// This program generates and plots Uniform, Normal, and Poisson
// distributions.

// include std, random, and be able to format output for std::cout
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

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
            uniformDist.push_back(DistributionPair(min, i + 1));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMax = uniformDist[previousIndex].maxValue;
            uniformDist.push_back(DistributionPair(previousMax + 1, previousMax + 2));
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
    // initialize the vector to be returned
    std::vector<DistributionPair> normalDist;

    // get the overall min
    float min = mean - (4 * stdev);
    // get the overall max
    float max = mean + (4 * stdev) - 1;

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::normal_distribution<float> dist(mean, stdev);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        if (i == 0)
        {
            normalDist.push_back(DistributionPair(min, min));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMin = normalDist[previousIndex].minValue;
            normalDist.push_back(DistributionPair(previousMin + 1, previousMin + 1));
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
                if (randNum < normalDist[k].maxValue + 1)
                {
                    normalDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= normalDist[k].minValue)
                {
                    normalDist[k].count++;
                }
            }
            else
            {
                if (randNum < normalDist[k].maxValue + 1 && randNum >= normalDist[k].minValue)
                {
                    normalDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return normalDist;
};

// generatePoissonDistribution function
// inputs:
//      -howMany: how many integers to randomly generate
//      -howOften: goes in as the mean of the distribution
//      -numberBins: how many bins to place the numbers in
// outputs:
//      return a DistributionPair vector that is a vector with numberBins
//      amount of bins, each with their specified range and count
// a function that generates howMany random numbers using poisson distribution
// and bins them based on their value
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins)
{
    // initialize the vector to be returned
    std::vector<DistributionPair> poissonDist;

    // get the overall min
    std::uint8_t min = 0;
    // get the overall max
    std::uint8_t max = numberBins - 1;

    // use uniform integer distribution for random number generation
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::poisson_distribution<int> dist(howOften);

    // set up the bins and define their range
    for (std::uint8_t i = 0; i < numberBins; i++)
    {
        if (i == 0)
        {
            poissonDist.push_back(DistributionPair(min, min));
        }
        else
        {
            auto previousIndex = i - 1;
            std::uint32_t previousMin = poissonDist[previousIndex].minValue;
            poissonDist.push_back(DistributionPair(previousMin + 1, previousMin + 1));
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
                if (randNum <= poissonDist[k].maxValue)
                {
                    poissonDist[k].count++;
                }
            }
            else if (k == numberBins - 1)
            {
                if (randNum >= poissonDist[k].minValue)
                {
                    poissonDist[k].count++;
                }
            }
            else
            {
                if (randNum >= poissonDist[k].minValue && randNum <= poissonDist[k].maxValue)
                {
                    poissonDist[k].count++;
                }
            }
        }
    }

    // return the correct vector
    return poissonDist;
};

// plotDistribution function
// inputs:
//      -title: the title of the distribution
//      -distribution: the vector generated by the distribution functions
//      -maxPlotLineSize: the number of characters to use for the bin that
//                        has the most characters
// a function that plots the distributuion function to the console
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize)
{
    // Print the title
    std::cout << title << std::endl;

    //get the max bin size
    std::uint32_t maxBin = 0;

    for (int i = 0; i < distribution.size(); i++)
    {
        if (distribution[i].count > maxBin)
        {
            maxBin = distribution[i].count;
        }
    }

    // get the number that represents the value of a character
    // for the plot
    float charVal = static_cast<float>(maxPlotLineSize) / maxBin;

    // plot each value in the distribution
    for (int j = 0; j < distribution.size(); j++)
    {
        std::uint32_t numChar = ceil(charVal * distribution[j].count);
        
        std::cout << "[" << std::setw(3) << distribution[j].minValue << ", " << std::setw(3) << distribution[j].maxValue << "] : ";
        
        for (int k = 0; k < numChar; k++)
        {
            std::cout << "*";        
        }

        std::cout << std::endl;
    }
};

// ------------------------------------------------------------------
//
// Testing Code
//
// ------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

namespace testing::detail
{
    using namespace std::string_literals;

    using Bins = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
    using DistFunc = std::function<std::vector<DistributionPair>()>;

#define CS3460_ASSERT_EQ(expected, actual, message)                    \
    if (expected != actual)                                            \
    {                                                                  \
        fail(message, "[ Expected", expected, "but got", actual, "]"); \
        return;                                                        \
    }

#define CS3460_CASE(x) \
    [] {               \
        return x;      \
    };                 \
    std::cout << " Case " << #x << "\n";

    template <typename Message>
    void failInternal(const Message& message)
    {
        std::cout << message << " ";
    }

    template <typename Message, typename... Messages>
    void failInternal(const Message& message, const Messages&... messages)
    {
        failInternal(message);
        failInternal(messages...);
    }

    template <typename... Messages>
    void fail(const Messages&... messages)
    {
        std::cout << "  Assertion failed: ";
        failInternal(messages...);
        std::cout << "\n";
    }

    Bins generateBins(const std::uint32_t min, const std::uint32_t max, const std::uint8_t numberBins)
    {
        const auto binRange = (max - min) / numberBins;
        auto minBin = min;
        auto maxBin = min + binRange;

        Bins results(numberBins);
        for (std::uint8_t bin = 0u; bin < numberBins; bin++)
        {
            results[bin] = { minBin, maxBin };
            minBin = maxBin + 1;
            maxBin = minBin + binRange;
        }

        return results;
    }

    void returnsTheExpectedBins(const DistFunc& func, const Bins& bins)
    {
        const auto result = func();
        CS3460_ASSERT_EQ(bins.size(), result.size(), "Wrong number of bins");
        for (auto i = 0u; i < bins.size(); i++)
        {
            CS3460_ASSERT_EQ(bins[i].first, result[i].minValue, "Wrong minimum value for bin "s + std::to_string(i));
            CS3460_ASSERT_EQ(bins[i].second, result[i].maxValue, "Wrong maximum value for bin "s + std::to_string(i));
        }
    }

    void hasTheCorrectTotalAcrossAllBins(const DistFunc& func, const std::uint32_t howMany)
    {
        const auto result = func();
        const auto add_counts = [](std::uint32_t total, const DistributionPair& bin)
        {
            return total + bin.count;
        };
        CS3460_ASSERT_EQ(howMany, std::accumulate(result.cbegin(), result.cend(), 0u, add_counts),
                         "Wrong number of elements across all bins");
    }

    void testUniformDistribution()
    {
        std::cout << "Testing generateUniformDistribution\n";
        auto func = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 40));
        returnsTheExpectedBins(func, generateBins(0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testNormalDistribution()
    {
        std::cout << "Testing generateNormalDistribution\n";
        auto func = CS3460_CASE(generateNormalDistribution(100000, 50, 5, 40));
        returnsTheExpectedBins(func, generateBins(30, 69, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }

    void testPoissonDistribution()
    {
        std::cout << "Testing generatePoissonDistribution\n";
        auto func = CS3460_CASE(generatePoissonDistribution(100000, 6, 40));
        returnsTheExpectedBins(func, generateBins(0, 39, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);
    }
} // namespace testing::detail

void test()
{
    using namespace testing::detail;

    testUniformDistribution();
    testNormalDistribution();
    testPoissonDistribution();

    std::cout << "\n\n";
}

int main()
{
    test();

    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(100000, 50, 5, 40);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Poisson ---", poisson, 80);

    return 0;
}
