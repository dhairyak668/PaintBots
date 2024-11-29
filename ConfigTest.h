#pragma once
#include "Config.h"
#include "ITest.h"

class ConfigTest : public ITest 
{
    private:
        bool testParameters(
            const Config& config, 
            int hit_duration = 20, 
            int paintblob_limit = 30, 
            int rock_lower_bound = 10,
            int rock_upper_bound = 20, 
            int fog_lower_bound = 5, 
            int fog_upper_bound = 10, 
            int long_range_limit = 30
        );

    public:
        bool doTests();
        bool testDefaultConstructor();
        bool testBadFileName();
        bool testGoodFileName();
        bool testEmptyFile();
        bool testCommentOnlyFile();
        bool testWhiteSpaceOnlyFile();
        bool testValidConfigFileMissingParameters();
        bool testInvalidConfigFileMissingParameters();
        bool testInvalidConfigFileInvalidValues();
        bool testNoEqualsInParameterLine();
        bool testInvalidBounds();
        bool testMixedCaseKeys();
        bool testInvalidKeyInParameterLine();

        
};