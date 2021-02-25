//testfile
#include "tst.h"
#include <sstream>
#include <vector>

//I got some inspirations for parsing the command line arguments from
//stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Error: Expected 2 Arguments" << endl;
        exit(1);
    }

    stringstream ss(argv[1]);
    vector<string> result;

    while (ss.good())
    { //parse argv[1] by comma
        string substr;
        getline(ss, substr, ',');
        //store it in the result vector
        result.push_back(substr);
    }

    //merge the parsed string into a oneline string
    string oneline = "";
    for (size_t i = 0; i < result.size(); i++)
    {
        oneline += result[i];
    }

    //parse the oneline string by whitespace
    stringstream newss(oneline);
    vector<string> vec;
    for (string i; newss >> i;)
    {
        vec.push_back(i);
    }

    //TST object
    TST mytst;

    //run the command
    for (size_t i = 0; i < vec.size(); i = i + 2)
    {
        if (vec[i] == "lookup")
        {
            mytst.lookup(vec[i + 1]);
        }
        else if (vec[i] == "insert")
        {
            mytst.insert(vec[i + 1]);
        }
        else if (vec[i] == "delete")
        {
            mytst.Delete(vec[i + 1]);
        }
        else if (vec[i] == "range_search")
        {
            mytst.RangeSearch(vec[i + 1], vec[i + 3]);
        }
    }

    return 0;
}
