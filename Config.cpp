#include "Config.h"

Config::Config()
{
    hit_duration = 20;
    paintblob_limit = 30;
    rock_lower_bound = 10;
    rock_upper_bound = 20;
    fog_lower_bound = 5;
    fog_upper_bound = 10;
    long_range_limit = 30;
}

// Config::Config(const string& filename) : Config()
// {
//     loadFromFile(filename);
// }


int Config::getHitDuration() const
{
    return hit_duration;
}

int Config::getPaintBlobLimit() const
{
    return paintblob_limit;
}

int Config::getRockLowerBound() const
{
    return rock_lower_bound;
}

int Config::getRockUpperBound() const
{
    return rock_upper_bound;
}

int Config::getFogLowerBound() const
{
    return fog_lower_bound;
}

int Config::getFogUpperBound() const
{
    return fog_upper_bound;
}

int Config::getLongRangeLimit() const
{
    return long_range_limit;
}
