#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // for remove()
using namespace std;

bool testParameters(const Config& config, int hit_duration = 20, int paintblob_limit = 30, int rock_lower_bound = 10,
 int rock_upper_bound = 20, int fog_lower_bound = 5, int fog_upper_bound = 10, int long_range_limit = 30){
    return((config.getHitDuration() == hit_duration) &&
    (config.getPaintBlobLimit() == paintblob_limit) &&
    (config.getRockLowerBound() == rock_lower_bound) &&
    (config.getRockUpperBound() == rock_upper_bound) &&    
    (config.getFogLowerBound() == fog_lower_bound) &&    
    (config.getFogUpperBound() == fog_upper_bound) &&    
    (config.getLongRangeLimit() == long_range_limit)); 
}

void testDefaultConstructor(){
    try{
        Config config;
        bool passed = testParameters(config);
        cout << "Checking Default Constructors & Getter Functions: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking Default Constructor & Getter Functions: FAIL" << endl;
    }
}

void testBadFileName(){
    try{
        Config config("badfile.txt");
        cout << "Checking Bad File Name: FAIL" << endl;
    }
    catch(const runtime_error& e){
        cout << "Checking Bad File Name: PASS" << endl;
    }
}

void testGoodFileName(){
    ofstream file("goodfile.txt");
    if (!file.is_open()) {
        cout << "Checking Good File Name: FAIL (could not open file)" << endl;
        return;
    }
    file << "hit_duration = 10" << endl;
    file << "paintblob_limit = 20" << endl;
    file << "rock_lower_bound = 5" << endl;
    file << "rock_upper_bound = 15" << endl;
    file << "fog_lower_bound = 2" << endl;
    file << "fog_upper_bound = 8" << endl;
    file << "long_range_limit = 25" << endl;
    file.close();
    try{
        Config config("goodfile.txt");
        bool passed = testParameters(config, 10, 20, 5, 15, 2, 8, 25);
        cout << "Checking Good File Name: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking Good File Name: FAIL" << endl;
    }
    remove("goodfile.txt");
}

void testEmptyFile(){
    ofstream file("emptyfile.txt");
    if (!file.is_open()) {
        cout << "Checking Empty File: FAIL (could not open file)" << endl;
        return;
    }
    file.close();
    try{
        Config config("emptyfile.txt");
        bool passed = testParameters(config);
        cout << "Checking Empty File: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking Empty File: FAIL" << endl;
    }
    remove("emptyfile.txt");
}

void testCommentOnlyFile(){
    ofstream file("commentfile.txt");
    if (!file.is_open()) {
        cout << "Checking Comment Only File: FAIL (could not open file)" << endl;
        return;
    }
    file << "# This is a comment" << endl;
    file << "   \t" << endl;
    file.close();
    try{
        Config config("commentfile.txt");
        bool passed = testParameters(config);
        cout << "Checking Comment Only File: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking Comment Only File: FAIL" << endl;
    }
    remove("commentfile.txt");
}

void testWhiteSpaceOnlyFile(){
    ofstream file("whitespacefile.txt");
    if (!file.is_open()) {
        cout << "Checking White Space Only File: FAIL (could not open file)" << endl;
        return;
    }
    file << "   \t" << endl;
    file.close();
    try{
        Config config("whitespacefile.txt");
        bool passed = testParameters(config);
        cout << "Checking White Space Only File: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking White Space Only File: FAIL" << endl;
    }
    remove("whitespacefile.txt");
}

void testValidConfigFileMissingParameters(){
    ofstream file("validfile.txt");
    if (!file.is_open()) {
        cout << "Checking Valid Config File Missing Parameters: FAIL (could not open file)" << endl;
        return;
    }
    file << "hit_duration = 10" << endl;
    file << "paintblob_limit = 20" << endl;
    file.close();
    try{
        Config config("validfile.txt");
        bool passed = testParameters(config, 10, 20, 10, 20, 5, 10, 30);
        cout << "Checking Valid Config File Missing Parameters: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking Valid Config File Missing Parameters: FAIL" << endl;
    }
    remove("validfile.txt");
}

void testInvalidConfigFileMissingParameters(){
    ofstream file("invalidfile.txt");
    if (!file.is_open()) {
        cout << "Checking Invalid Config File Missing Parameters: FAIL (could not open file)" << endl;
        return;
    }
    file << "hit_duration = 10" << endl;
    file << "paintblob_limit = 20" << endl;
    file << "rock_lower_bound = 5" << endl;
    file << "rock_upper_bound = 15" << endl;
    file << "fog_lower_bound = 2" << endl;
    file << "extra_parameter = 100" << endl;
    file.close();
    try{
        Config config("invalidfile.txt");
        cout << "Checking Invalid Config File Missing Parameters: FAIL" << endl;
    }
    catch(const runtime_error& e){
        cout << "Checking Invalid Config File Missing Parameters: PASS" << endl;
    }
    remove("invalidfile.txt");
}

void testInvalidConfigFileInvalidValues(){
    ofstream file("invalidfile.txt");
    if (!file.is_open()) {
        cout << "Checking Invalid Config File Invalid Values: FAIL (could not open file)" << endl;
        return;
    }
    file << "hit_duration = 10" << endl;
    file << "paintblob_limit = invalid" << endl;
    file.close();
    try{
        Config config("invalidfile.txt");
        cout << "Checking Invalid Config File Invalid Values: FAIL" << endl;
    }
    catch(const runtime_error& e){
        cout << "Checking Invalid Config File Invalid Values: PASS" << endl;
    }
    remove("invalidfile.txt");
}

void testNoEqualsInParameterLine(){
    ofstream file("invalidfile.txt");
    if (!file.is_open()) {
        cout << "Checking No Equals In Parameter Line: FAIL (could not open file)" << endl;
        return;
    }
    file << "hit_duration 10" << endl;
    file.close();
    try{
        Config config("invalidfile.txt");
        cout << "Checking No Equals In Parameter Line: FAIL" << endl;
    }
    catch(const runtime_error& e){
        cout << "Checking No Equals In Parameter Line: PASS" << endl;
    }
    remove("invalidfile.txt");
}

void testInvalidKeyInParameterLine(){
    ofstream file("invalidfile.txt");
    if (!file.is_open()) {
        cout << "Checking Invalid Key In Parameter Line: FAIL (could not open file)" << endl;
        return;
    }
    file << "invalid_key = 10" << endl;
    file.close();
    try{
        Config config("invalidfile.txt");
        cout << "Checking Invalid Key In Parameter Line: FAIL" << endl;
    }
    catch(const runtime_error& e){
        cout << "Checking Invalid Key In Parameter Line: PASS" << endl;
    }
    remove("invalidfile.txt");
}

void testMixedCaseKeys(){
    ofstream file("mixedcasefile.txt");
    if(!file.is_open()){
        cout << " Checking Mixed Case Keys: FAIL (could not open file)" << endl;
        return;
    }
    file << "Hit_Duration = 10" << endl;
    file << "PaintBlob_LiMit = 20" << endl;
    file << "ROCK_LOWER_BOUND = 3" << endl;
    file.close();
    try{
        Config config("mixedcasefile.txt");
        bool passed = testParameters(config, 10, 20, 3, 20, 5, 10, 30);
        cout << "Checking Mixed Case Keys: " << (passed ? "PASS" : "FAIL") << endl;
    }
    catch(...){
        cout << "Checking Mixed Case Keys: FAIL" << endl;
    }
    remove("mixedcasefile.txt");
}

void testInValidBounds(){
    ofstream file("invalidfile.txt");
    if(!file.is_open()){
        cout << "Checking Invalid Bounds: FAIL (could not open file)" << endl;
        return;
    }
    file << "hit_duration = 10" << endl;
    file << "paintblob_limit = 20" << endl;
    file << "rock_lower_bound = 20" << endl;
    file << "rock_upper_bound = 10" << endl;
    file << "fog_lower_bound = 8" << endl;
    file << "fog_upper_bound = 2" << endl;
    file.close();
    try{
        Config config("invalidfile.txt");
        cout << "Checking Invalid Bounds: FAIL" << endl;
    }
    catch(const runtime_error& e){
        cout << "Checking Invalid Bounds: PASS" << endl;
    }
    remove("invalidfile.txt");
}

int main(){
    cout << "Config Class Unit Tests" << endl << endl;
    testDefaultConstructor();
    testBadFileName();
    testGoodFileName();
    testEmptyFile();
    testCommentOnlyFile();
    testWhiteSpaceOnlyFile();
    testValidConfigFileMissingParameters();
    testInvalidConfigFileMissingParameters();
    testInvalidConfigFileInvalidValues();
    testNoEqualsInParameterLine();
    testInvalidKeyInParameterLine();
    testMixedCaseKeys();
    testInValidBounds();
    return 0;
}