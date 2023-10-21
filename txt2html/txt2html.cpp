/* 
 *Name:	    Yaksh Patel
 *Date:	    5 Nov 2021
 *FileName: txt2html.cpp
 *Purpose:  Create a C++ application that converts a text file into a format more appropriate for use in a webpage,
		    smart-phone, or e-book reader. Specifically, this program converts an UTF-8 text file to an .html containing the
		    same textual content as the original UTF-8 text file.
 */

/*
*PSUDO CODE
*1)Take the input from the command line
*2)If the user provides “-r”, print a report (described in the next section).
*I3)f the user provides “-b”, read the text file in binary mode (or untranslated mode). 
*4)If the user provides “-p”, enclose paragraphs in paragraph tags <p></p>.
*5)Making input of  Switches which can be provided individually (-r -b) or joined (-rb)
*6)Writing an error  if both “-b” and “-p” are provided. If both switches are provided, report error and exit.
*7)If “-r” is provided, display a report that console
	a)The number of complete lines read from the input file, as indicated by the translated newline character.
	b)The number of paragraphs, indicated by <br> tags
*8)If “-r” and “-p”, display a report that console
	a) The number of complete lines read from the input file, as indicated by the translated newline character.
	b)If “-p” is provided, the number of paragraphs, indicated by <p></p> tags
*9)If “-r” and “-b” are provided, display a report that displays:
	a)The number of complete lines read from the input file, as indicated by the untranslated newline character
	b)The number of paragraphs, indicated by <br> tags
*/
#include<iostream>
#include<fstream>
#include <string>
#include <locale>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	//Creating strings for reading file name , writing file name and also for getting file title.
	string in_argument_Vector[10];
	string read_File_Name;
	string write_File_Name;
	string file_Title;

	//creating a vector string named vector_arguments
	vector<string> vector_arguments;
	for (int i = 1; i < argc; ++i) {
		vector_arguments.push_back(argv[i]);       
	}
	//Checking if the input file is given or not from the user in the command Window 
	//if not provided then using EXIT_FAILURE
	if (vector_arguments.empty() || argc > 5)
	{
		cerr << "Error: Invalid input. Incorrect number of parameters[" << argc << "]" << endl;
		cerr << "Usage: txt2html[-r(-b|-p)] sourcefile destinationfile" << endl;
		return EXIT_FAILURE;
	}
	
	//creating a variable named 'x'
	int x = 0;
	for (string str : vector_arguments) in_argument_Vector[++x] = str;
	if (vector_arguments.empty())
	{
		cerr << "Error, no arg....\n";
		return EXIT_FAILURE;
	}
	//Creating boolean for report switch,binary switch and paragraph switch
	bool bool_Report_Switch = false;		
	bool bool_Binary_Switch = false;		
	bool bool_Paragraph_Switch = false;	

	//Creating an  r vector string iterator named 
	vector<string>::iterator Finder = find(vector_arguments.begin(), vector_arguments.end(), "-r");
	if (Finder != vector_arguments.end())
	{
		bool_Report_Switch = true;
		vector_arguments.erase(Finder); 
	}
	//Finding -b switch 
	Finder = find(vector_arguments.begin(), vector_arguments.end(), "-b");
	if (Finder != vector_arguments.end())
	{
		bool_Binary_Switch = true;
		vector_arguments.erase(Finder); 
	}
	//Finding -p switch
	Finder = find(vector_arguments.begin(), vector_arguments.end(), "-p");
	if (Finder != vector_arguments.end())
	{
		bool_Paragraph_Switch = true;
		vector_arguments.erase(Finder);  
	}
	//Report if binary and paragraph switch are together inputted by the user
	if ((bool_Binary_Switch == true) && (bool_Paragraph_Switch == true))
	{
		cerr << "Error: cannot have binary and paragraph switches together." << endl;
		cerr << "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile";
		return EXIT_FAILURE;
	}

	//Creating a size_t unsigned integer named find_html, save_Text and save_Html and assigning value 0 to them.
	size_t find_html = 0;
	size_t save_Text = 0;
	size_t save_Html = 0;

	//Creating a integer datatype large enough to represent any possible string size named found_file_extension
	string::size_type found_file_extension;

	//creating a for loop to find the .txt extension from the command line
	for (int i = 1; i < argc; ++i) {
		found_file_extension = in_argument_Vector[i].find(".txt");
		if (found_file_extension != string::npos) {
			save_Text = i;
			break;
		}
	}

	//creating a for loop to find the .html extension from the command line
	for (int i = 1; i < argc; ++i) {
		found_file_extension = in_argument_Vector[i].find(".html");
		if (found_file_extension != string::npos) {
			save_Html = i;
			if (save_Text < save_Html) {
				find_html = 1;
				break;
			}
			else {
				//Reporting if .txt or .html file not found
				cerr << "Error: there must be a .txt file before a .html file." << endl;
				cerr << "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
				return EXIT_FAILURE;
			}
		}
	}

	if (find_html) {
		if (vector_arguments.size() > 2) {
			//Reporting if output file is not correct
			cerr << "Error: there must be a valid out_file name with a .html extension." << endl;
			cerr << "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
			return EXIT_FAILURE;
		}
	}
	else if (vector_arguments.size() > 1) {
		//Reporting if output file is not correct
		cerr << "Error: there must be a valid out_file name with a .html extension." << endl;
		cerr << "Usage: txt2html [-r(-b|-p)] sourcefile destinationfile" << endl;
		return EXIT_FAILURE;
	}
		
	for (int y = 1; y < argc ; ++y) {
		char* context = NULL;
		char* token = strtok_s(argv[y], ".", &context);

		if ((string)context == "txt" || (string)context == "TXT") {
			read_File_Name = in_argument_Vector[y];
			file_Title = (string)token;
		}
		else if ((string)context == "html" || (string)context == "HTML") {
			write_File_Name = in_argument_Vector[y];
		}
	}
	
	if (write_File_Name.empty()) {
		write_File_Name = file_Title + ".html";
	}
	
	ifstream input_For_File(read_File_Name);
	ofstream output_For_File(write_File_Name);

	if (!input_For_File)
	{
		cerr << "Input file failed opening\n";
		return EXIT_FAILURE;
	}
		
	//Creating a size_t unsigned integer named line_Count, para_Count and p_paragraph_Count and assigning value 0 to them.
	size_t  line_Count = 0;
	size_t  para_count = 0;
	size_t  p_paragraph_Count = 0;

	//Creating a string named line and an int named line_count and assigning it value 0
	string line;
	int line_count = 0;
	
	//getting input for file and reading the file line by line 
	while (getline(input_For_File, line))
	{
		line_Count++;
		if (line_Count < 2) {
			//Inputting the html tags using the txt file 
			output_For_File << "<html>" << endl; 
			output_For_File << "<head>" << endl; 
			output_For_File << "<Title>" << file_Title << "</Title>" << endl;
			output_For_File << "</head>" << endl;
			output_For_File << "<body>" << endl;
			if (bool_Paragraph_Switch) {
				output_For_File << "<p>" << endl;
				++p_paragraph_Count;
			}
		}
		if (line.empty()) {
			++line_count;
		} 
		else {
			if (line_count > 0) {
				if (bool_Paragraph_Switch) {
					output_For_File << "</p>" << endl;
					++p_paragraph_Count;
					for (int i = 0; i < line_count-1; ++i)
						output_For_File << "<br>" << endl;
					output_For_File << "<p>" << endl;
					++p_paragraph_Count;
				}
				else{
					for (int i = 0; i < line_count + 1; ++i)
						output_For_File << "<br>" << endl;
					++para_count;
				}
			}
			line_count = 0;
			output_For_File << line << endl;
			}
	}
	//if for inputting paragraph tag
	if (line_count > 0) {
		if (bool_Paragraph_Switch) {
			output_For_File << "</p>" << endl;
			++p_paragraph_Count;
		}
		else {
			//else for inputting breakline tag
			for (int i = 0; i < line_count + 1; ++i)
				output_For_File << "<br>" << endl;
			++para_count;
		}
	} 
	//tags for closing the body and html
	output_For_File << "</body>" << endl;
	output_For_File << "</html>";
	input_For_File.close();
	output_For_File.close();
	
	locale here("");
	cout.imbue(here);
		for (int i = 1; i < argc; ++i) {
			if (bool_Paragraph_Switch) {
				//Showing the output to the screen and showing the appropriate numbers
				cout << "Input lines processed, counting translated newline character: " << line_Count << endl;
				cout << "Output paragraph processed, counting <p></p> tags: " << p_paragraph_Count << endl;
				break;
			}
			else if (bool_Binary_Switch) {
				char character;
				size_t value = 0;
				ifstream in(read_File_Name, ios::binary);
				
				while (in.get(character)) {
					if (character == '\r' || character == '\n') {
						value++;
					}
				}
				//Showing the result to the screen for untranslated newline character and binary processed
				cout << "Input lines processed, counting untranslated newline character: " << value << endl;
				cout << "Output binary processed: " << para_count << endl;
				input_For_File.close();
				break;
			}
			else if (bool_Report_Switch) {
				////Showing the result to the screen for translated newline character and binary processed
				cout << "Input lines processed, counting translated newline character: " << line_Count << endl;
				cout << "Output binary processed: " << para_count << endl;
				break;
			}
		}

	return EXIT_SUCCESS;
}

