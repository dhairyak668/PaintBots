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
Config::Config(const string& filename)
{
    hit_duration = 20;
    paintblob_limit = 30;
    rock_lower_bound = 10;
    rock_upper_bound = 20;
    fog_lower_bound = 5;
    fog_upper_bound = 10;
    long_range_limit = 30;

    ifstream file(filename);
    if(!file.is_open())
    {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    while(getline(file, line)){

        trimWhitespace(line);
        
        if(line.empty() || line[0] == '#')
        {
            continue;
        
        }
        int pos = line.find('=');
        if(pos == string::npos)
        {
            file.close();
            throw runtime_error("Invalid line in config file: " + line);
        }
        
        string key = line.substr(0, pos);
        string value = line.substr(pos+1);
        trimWhitespace(key);
        trimWhitespace(value);
        toLowerCase(key);
        
        try {
            if(key == "hit_duration"){
            hit_duration = stoi(value);
            }
            else if(key == "paintblob_limit"){
            paintblob_limit = stoi(value);
            }
            else if(key == "rock_lower_bound"){
            rock_lower_bound = stoi(value);
            }
            else if(key == "rock_upper_bound"){
            rock_upper_bound = stoi(value);
            }
            else if(key == "fog_lower_bound"){
            fog_lower_bound = stoi(value);
            }
            else if(key == "fog_upper_bound"){
            fog_upper_bound = stoi(value);
            }
            else if(key == "long_range_limit"){
            long_range_limit = stoi(value);
            }
            else{
            file.close();
            throw runtime_error("Invalid key in config file: " + key);
            }
        } catch (const invalid_argument& e) { //stoi throws invalid_argument if the string cannot be converted.
            file.close();
            throw runtime_error("Invalid value for key " + key + ": " + value);
        }
    }
    file.close();
    if(rock_lower_bound >= rock_upper_bound)
    {
        throw runtime_error("rock_lower_bound must be less than rock_upper_bound");
    }
    if(fog_lower_bound >= fog_upper_bound)
    {
        throw runtime_error("fog_lower_bound must be less than fog_upper_bound");
    }
}

void Config::trimWhitespace(string& str)
{
    int start = 0;
    int end = str.size() - 1;
    while(start <= end && isspace(str[start])) 
    {
        start++;
    }
    while(end >= start && isspace(str[end])) 
    {
        end--;
    }
    if(start > end)
    {
        str.clear();
        return;
    }
    str = str.substr(start, end - start + 1);
}

void Config::toLowerCase(string& str)
{
    // for(char& c : str) //can replace each character in the string with a lowercase version of itself
    // {
    //     c = tolower(c);
    // }
    for(int i = 0; i < str.size(); i++)
    {
        str[i] = tolower(str[i]);
    }
}

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


