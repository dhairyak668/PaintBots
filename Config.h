#pragma once
#include <string>
using namespace std;
/**
 * @class Config
 * @brief A class to manage configuration settings.
 * 
 * The Config class encapsulates various configuration parameters
 * such as hit duration, paint blob limit, rock bounds, fog bounds,
 * and long range limit.
 */
class Config{
    private:
    int hit_duration;
    int paintblob_limit;
    int rock_lower_bound;
    int rock_upper_bound;
    int fog_lower_bound;
    int fog_upper_bound;
    int long_range_limit;
    void loadFromFile(const string& filename);

    public:

    /**
     * @brief Default Construct a new Config object.
     * sets the default values for the configuration parameters.
     */
    Config();

    // Config(const string& filename);

    /**
     * @brief Get the hit duration.
     * @return The hit duration as an integer.
     */
    int getHitDuration() const;

    /**
     * @brief Get the paint blob limit.
     * @return The paint blob limit as an integer.
     */
    int getPaintBlobLimit() const;

    /**
     * @brief Get the lower bound for rocks.
     * @return The lower bound for rocks as an integer.
     */
    int getRockLowerBound() const;

    /**
     * @brief Get the upper bound for rocks.
     * @return The upper bound for rocks as an integer.
     */
    int getRockUpperBound() const;

    /**
     * @brief Get the lower bound for fog.
     * @return The lower bound for fog as an integer.
     */
    int getFogLowerBound() const;

    /**
     * @brief Get the upper bound for fog.
     * @return The upper bound for fog as an integer.
     */
    int getFogUpperBound() const;

    /**
     * @brief Get the long range limit.
     * @return The long range limit as an integer.
     */
    int getLongRangeLimit() const;
};
