/*******************************************************************************

   Copyright Alan Garny

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*******************************************************************************/

#include <fstream>
#include <iostream>
#include <libcellml>
#include <sstream>

void usage(char *pAppName)
{
    std::cout << "Usage: " << pAppName << " [C|Python] <CellMLFile>" << std::endl;
}

int main(int pArgC, char *pArgV[])
{
    // Make sure that we we have the correct number of arguments.

    if ((pArgC < 2) || (pArgC > 3)) {
        usage(pArgV[0]);

        return -1;
    }

    // Determine the type of file(s) we want to generate.

    libcellml::GeneratorProfilePtr profile = libcellml::GeneratorProfile::create(libcellml::GeneratorProfile::Profile::C);

    if (pArgC == 3) {
        if (!strcmp(pArgV[1], "Python")) {
            profile->setProfile(libcellml::GeneratorProfile::Profile::PYTHON);
        } else if (strcmp(pArgV[1], "C")) {
            usage(pArgV[0]);

            return -1;
        }
    }

    // Retrieve the contents of the file.

    std::string fileName = pArgV[(pArgC == 2)?1:2];

    std::ifstream file(fileName);
    std::stringstream buffer;

    buffer << file.rdbuf();

    std::string fileContents = buffer.str();

    // Generate the requested code.

    try {
        libcellml::ParserPtr parser = libcellml::Parser::create();
        libcellml::ModelPtr model = parser->parseModel(fileContents);
        libcellml::GeneratorPtr generator = libcellml::Generator::create();

        generator->processModel(model);
        generator->setProfile(profile);

        if (profile->profile() == libcellml::GeneratorProfile::Profile::C) {
            std::ofstream interfaceFile;

            interfaceFile.open(fileName+".h");

            interfaceFile << generator->interfaceCode();
        }

        std::ofstream implementationFile;

        implementationFile.open(fileName+((profile->profile() == libcellml::GeneratorProfile::Profile::C)?".c":".py"));

        implementationFile << generator->implementationCode();
    } catch(...) {
        std::cout << "An error occurred. Please make sure that '" << fileName << "' is a valid CellML file." << std::endl;
    }

    return 0;
}
