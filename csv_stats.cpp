/*
This program reads in a csv file and creates an index out of 2 columns 
*/



#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
 

#include <boost/algorithm/string.hpp>

using namespace std;

template <class Container>
void split(const std::string& str, Container& cont,
              const std::string& delims = " ")
{
    boost::split(cont, str, boost::is_any_of(delims));
}


int main (int argc, char *argv[]) 
{
        /* Read in the csv */
	const string newdata = argv[1]; // input file name
	const string sep = argv[2]; // index separator
	const int colnum1 = 0; //first column 
	const int colnum2 = 7; //sixth column
	cout << "Reading data file: " << newdata << endl;
	vector<string> csvlines;

	//Read in the csv file line by line
	ifstream incsv(newdata);
	string l;
	while (getline(incsv, l)) {

		//Split the line by the delimiter
		vector<string> thissplitline;
		string outline;
		split(l, thissplitline, ",");

		//Concatenate the variables to be used in the index
		string thisindex;
		thisindex = thissplitline.at(colnum1) + sep + thissplitline.at(colnum2);

		//Concatenate the index to the beginning of the line w/ separator
		thissplitline.insert(thissplitline.begin(), thisindex);			
		int vectsize = thissplitline.size();
		for (int i = 0; i < vectsize; i++) outline += thissplitline.at(i) + ',';

		//replace the last comma with a newline
		outline.pop_back();
		outline += '\n';


		//Save it in data structure to be written later
		csvlines.push_back(outline);

	}

	//Time to rebuild this into another CSV file with a unified index
	ofstream outfile;
	const string outfname = newdata + "_indexed.csv";
	outfile.open(outfname);
	for (const auto l : csvlines) {
		
		outfile << l;
	
	}

	outfile.close();

	cout << "Written indexed file: " << outfname << endl; 

	return 0;
}

