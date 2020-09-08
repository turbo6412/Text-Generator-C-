#include <iostream>
#include <string>
#include <cmath>    // abs()
#include <algorithm>

#include "WordPlay.hpp"

using namespace std;


// Global static variables
static int testCount = 0;
static const int testTotal = 17;
static const string GREEN = "\033[32m";
static const string RED = "\033[31m";
static const string RESET = "\033[0m";

// Prototypes

template <typename T, typename U>
bool assertEquals(const string & nameOfTest, const T & expected, const U & actual);

template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& orig_expected, const vector<U>& orig_actual);

vector<string> v1;

// Main
int main() {

    WordPlay Frankenstein;
    Frankenstein.readIn("Frankenstein or The Modern Prometheus by Mary Shelley.txt");
    cout << "Testing Frankenstein Text File" << endl;
    assertEquals("numberOfWords", 7171, Frankenstein.numberOfWords());
    assertEquals("wordCount: frankenstein", 26, Frankenstein.wordCount("frankenstein"));
    assertEquals("wordBucket: frankenstein", Frankenstein.wordBucketIdMethod1("frankenstein"), Frankenstein.wordBucketIdMethod2("frankenstein"));
    assertEquals("wordCount: life", 115, Frankenstein.wordCount("life"));
    assertEquals("wordCount: feared", 13, Frankenstein.wordCount("feared"));
    assertEquals("wordCount: dream", 18, Frankenstein.wordCount("dream"));
    assertEquals("mostFrequentWord", "the", Frankenstein.mostFrequentWord());
    assertEquals("lookUpWord: vast", true, Frankenstein.lookUpWord("vast"));
    assertEquals("lookUpWord: niw", false, Frankenstein.lookUpWord("niw"));
    /*cout << endl;
    for (int i = 0; i < Frankenstein.spellCheck("niw").size(); ++i)
        cout << Frankenstein.spellCheck("niw")[i] << ' ';
    cout << endl;*/

    v1 = { "new", "now" };
    assertVectorEquals("suggestions for: niw", v1, Frankenstein.suggest("niw"));

    v1.clear();

    WordPlay SleepyHollow;
    SleepyHollow.readIn("The Legend of Sleep Hollow by Washington Irving.txt");
    cout << endl << "Testing Sleep Hollow Text File" << endl;
    assertEquals("numberOfWords", 3231, SleepyHollow.numberOfWords());
    assertEquals("wordCount: ichabod", 45, SleepyHollow.wordCount("ichabod"));
    assertEquals("wordCount: road", 14, SleepyHollow.wordCount("road"));
    assertEquals("wordBucket: road", SleepyHollow.wordBucketIdMethod1("road"), SleepyHollow.wordBucketIdMethod2("road"));
    assertEquals("mostFrequentWord", "the", SleepyHollow.mostFrequentWord());
    assertEquals("lookUpWord: lame", false, SleepyHollow.lookUpWord("lame"));
    
    v1 = { "came", "dame", "game", "name", "same", "late", "lamb"};
    /*cout << endl;
    for (int i = 0; i < SleepyHollow.spellCheck("lame").size(); ++i)
        cout << SleepyHollow.spellCheck("lame")[i] << ' ';
    cout << endl;*/
    assertVectorEquals("suggestions for: lame", v1, SleepyHollow.suggest("lame"));

    cout << endl << RESET << GREEN << "Total tests passed = " << testCount << RESET << "/" << testTotal << endl;

    return 0;
}

template <typename T, typename U>
bool assertEquals(const string& nameOfTest, const T& expected, const U& actual) {
    if (expected == actual) {
        // Green colored text
        cout << RESET << GREEN << "PASSED "
             << RESET << nameOfTest << GREEN << ": expected and actual '" << RESET << actual << GREEN << "'" << RESET << endl;
        testCount++;
        return true;
    }
    // Red colored text
    cout << RESET << RED << "FAILED "
         << RESET << nameOfTest << RED << ": expected '" << RESET << expected << RED << "' but actually '" << RESET << actual << RED << "'" << RESET << endl;
    return false;
}

template <typename T, typename U>
bool assertVectorEquals(const string& nameOfTest, const vector<T>& orig_expected, const vector<U>& orig_actual) {
    vector<T> expected = orig_expected;
    vector<U> actual = orig_actual;
    sort(expected.begin(), expected.end());
    sort(actual.begin(), actual.end());
    if (expected.size() == actual.size()) {
        for (size_t i = 0; i < expected.size(); i++) {
            if (expected[i] != actual[i]) {
                // Red colored text
                cout << RESET << RED << "FAILED "
                    << RESET << nameOfTest << RED << ": expected '" << RESET << expected[i] << RED << "' but actually '" << RESET << actual[i] << RED << "'" << RESET << endl;
                return false;
            }
        }

        // Green colored text
        cout << RESET << GREEN << "PASSED "
            << RESET << nameOfTest << GREEN << ": expected and actual lists match: {" << RESET ;
        for (int i = 0; i < expected.size(); i++) {
            cout << " " << expected[i];
        }
        cout << GREEN << " }" << RESET << endl;

        testCount++;
        return true;
    }

    // Red colored text
    cout << RESET << RED << "FAILED "
        << RESET << nameOfTest << RED << ": expected size '" << RESET << expected.size() << RED << "' but actually size is '" << RESET << actual.size() << RED << "'" << RESET << endl;
    return false;
}