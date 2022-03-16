#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

namespace parcluster {

struct commandLine {
  int argc;
  char** argv;
  std::string comLine;
  commandLine(int _c, char** _v, std::string _cl)
    : argc(_c), argv(_v), comLine(_cl) {
      if (getOption("-h") || getOption("-help"))
	badArgument();
    }

  commandLine(int _c, char** _v)
    : argc(_c), argv(_v), comLine("bad arguments") { }

  void badArgument() {
    std::cout << "usage: " << argv[0] << " " << comLine << std::endl;
    exit(0);
  }

  // get an argument
  // i is indexed from the last argument = 0, second to last indexed 1, ..
  char* getArgument(int i) {
    if (argc < 2+i) badArgument();
    return argv[argc-1-i];
  }

  // looks for two filenames
  std::pair<char*,char*> IOFileNames() {
    if (argc < 3) badArgument();
    return std::pair<char*,char*>(argv[argc-2],argv[argc-1]);
  }

  std::pair<size_t,char*> sizeAndFileName() {
    if (argc < 3) badArgument();
    return std::pair<size_t,char*>(std::atoi(argv[argc-2]),(char*) argv[argc-1]);
  }

  bool getOption(std::string option) {
    for (int i = 1; i < argc; i++)
      if ((std::string) argv[i] == option) return true;
    return false;
  }

  char* getOptionValue(std::string option) {
    for (int i = 1; i < argc-1; i++)
      if ((std::string) argv[i] == option) return argv[i+1];
    return NULL;
  }

  std::string getOptionValue(std::string option, std::string defaultValue) {
    for (int i = 1; i < argc-1; i++)
      if ((std::string) argv[i] == option) return (std::string) argv[i+1];
    return defaultValue;
  }

  long getOptionLongValue(std::string option, long defaultValue) {
    for (int i = 1; i < argc-1; i++)
      if ((std::string) argv[i] == option) {
	long r = atol(argv[i+1]);
	if (r < 0) badArgument();
	return r;
      }
    return defaultValue;
  }

  int getOptionIntValue(std::string option, int defaultValue) {
    for (int i = 1; i < argc-1; i++)
      if ((std::string) argv[i] == option) {
	int r = atoi(argv[i+1]);
	if (r < 0) badArgument();
	return r;
      }
    return defaultValue;
  }

  double getOptionDoubleValue(std::string option, double defaultValue) {
    for (int i = 1; i < argc-1; i++)
      if ((std::string) argv[i] == option) {
	double val;
	if (sscanf(argv[i+1], "%lf",  &val) == EOF) {
	  badArgument();
	}
	return val;
      }
    return defaultValue;
  }

};

} // End namespace pargeo
