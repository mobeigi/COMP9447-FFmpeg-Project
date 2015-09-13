/*
	This class is designed to log specified text to an output file (ie the log file)
	Kindly provided (through open source) at the following repo:
		https://github.com/SFML/SFML/wiki/Source:-Simple-File-Logger-%28by-mateandmetal%29
	
	**************************************************************************************
	Example usage:
	
	== Main.cpp
	#include "FileLogger.hpp"

		int main() {

			// Create object
			ige::FileLogger myLog ("1.0.4.2", "testfile.txt");

			// Writing warnings or errors to file is very easy and C++ style
			myLog << ige::FileLogger::e_logType::LOG_WARNING << "Hey! ... This is a warning message!";
			myLog << ige::FileLogger::e_logType::LOG_ERROR << "WOW! Something really wrong is happening here!";
			myLog << "This is just a simple text";

			return 0;

		}
	
	== testfile.txt
	My Game Engine, version 1.0.4.2
	Log file created

	[WARNING]: Hey! ... This is a warning message!
	[ERROR]: WOW! Something really wrong is happening here!
	This is just a simple text


	1 warnings
	1 errors
	**************************************************************************************
*/

#ifndef FILELOGGER_HPP
#define FILELOGGER_HPP

#include <fstream>

// Use the namespace you want
namespace ige {

    class FileLogger {

        public:


            // If you can´t/dont-want-to use C++11, remove the "class" word after enum
            enum class e_logType { LOG_ERROR, LOG_WARNING, LOG_INFO };


            // ctor (remove parameters if you don´t need them)
            explicit FileLogger (const char *engine_version, const char *fname)
                  :   numWarnings (0U),
                      numErrors (0U)
            {

                myFile.open (fname);

                // Write the first lines
                if (myFile.is_open()) {
					/*
                    myFile << "My Game Engine, version " << engine_version << std::endl;
                    myFile << "Log file created" << std::endl << std::endl;
					*/
                } // if

            }


            // dtor
            ~FileLogger () {

                if (myFile.is_open()) {
                    myFile << std::endl << std::endl;

                    // Report number of errors and warnings
                    myFile << numWarnings << " warnings" << std::endl;
                    myFile << numErrors << " errors" << std::endl;

                    myFile.close();
                } // if

            }


            // Overload << operator using log type
            friend FileLogger &operator << (FileLogger &logger, const e_logType l_type) {

                switch (l_type) {
                    case ige::FileLogger::e_logType::LOG_ERROR:
                        logger.myFile << "[ERROR]: ";
                        ++logger.numErrors;
                        break;

                    case ige::FileLogger::e_logType::LOG_WARNING:
                        logger.myFile << "[WARNING]: ";
                        ++logger.numWarnings;
                        break;

                    default:
                        logger.myFile << "[INFO]: ";
                        break;
                } // sw


                return logger;

            }


            // Overload << operator using C style strings
            // No need for std::string objects here
            friend FileLogger &operator << (FileLogger &logger, const char *text) {

                logger.myFile << text << std::endl;
                return logger;

            }


            // Make it Non Copyable (or you can inherit from sf::NonCopyable if you want)
            FileLogger (const FileLogger &) = delete;
            FileLogger &operator= (const FileLogger &) = delete;



        private:

            std::ofstream           myFile;

            unsigned int            numWarnings;
            unsigned int            numErrors;

    }; // class end

}  // namespace


#endif // FILELOGGER_HPP