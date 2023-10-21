# Txt2Html
Text to HTML Converter,
Back in November 2021, I created a cool C++ tool called the "Text to HTML Converter." This nifty application lets you turn regular text files (in UTF-8 format) into HTML files. It's perfect if you want to make your text content suitable for web pages, smartphones, or e-book readers.

Cool Features:-

1. Text to HTML Conversion: You give it a text file, and it spits out an HTML file that looks just like your original text but is now in HTML format.
2. Switches: The program comes with some command-line tricks. Here's what they do:
  -r: If you add this switch, you get a report telling you how many lines it reads from the input file.
  -b: Use this to make the program read the text file in a kind of "raw" binary mode.
  -p: Add this one if you want your paragraphs to be enclosed in HTML tags.

How to Use It-

To get the Text to HTML Converter up and running, open your command line and type:
  txt2html [-r(-b|-p)] sourcefile destinationfile
a. sourcefile: This is the UTF-8 text file you want to convert to HTML.
b. destinationfile: Here's where you type the name of the HTML file you want to create. If you skip this, the program will make a default HTML file with the same name as your source file, but with a .html extension.

Real-Life Examples:-
1. Basic Conversion:
  txt2html input.txt output.html
2. Conversion with a Report:
  txt2html -r input.txt output.html
3. Binary Mode Conversion:
  txt2html -b input.txt output.html
4. Conversion with Paragraph Tags:
  txt2html -p input.txt output.html

What I Learned:-

Building this project taught me a lot about C++ programming and file handling. Here are some of the things I picked up:
1. How to deal with command-line arguments in C++.
2. The ins and outs of working with files, whether they're text or binary.
3. Tricks for playing with strings and shaping them into neat HTML content.
4. How to add customizable switches to a command-line tool.
5. The art of converting plain text into HTML, complete with paragraphs.

This Text to HTML Converter is a handy little tool to have in your coding toolbox. It's perfect for transforming plain text documents into HTML format, whether you're publishing stuff on the web or preparing content for your favorite e-reader. Feel free to use it and tweak it to fit your text-to-HTML conversion needs.

