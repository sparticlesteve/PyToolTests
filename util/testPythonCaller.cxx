#include "Python.h"

#include <iostream>

#include "TSystem.h"

#include "xAODRootAccess/Init.h"

#include "PyToolTests/PythonCaller.h"

#include "JetSelectorTools/JetCleaningTool.h"


int main(int argc, char* argv[])
{
  // The application's name
  const char* APP_NAME = argv[0];

  if(!xAOD::Init(APP_NAME)){
    std::cerr << "Error initializing xAOD environment" << std::endl;
    return 1;
  }

  // Parameters
  const std::string className = "JetCleaningTool";
  const std::string toolName = "MyJetCleaningTool";
  const std::string moduleName = "PyToolTests.toolConfig";
  const std::string funcName = "configTool";

  // Instantiate a tool
  std::cout << "Instantiating the tool" << std::endl;
  JetCleaningTool jetCleanTool(toolName);

  // Call the python function
  if(callPythonFunction(&jetCleanTool, className, moduleName, funcName).isFailure()){
    std::cerr << "Error calling python config" << std::endl;
    return EXIT_FAILURE;
  }

  // Initialize the tool
  if(jetCleanTool.initialize().isFailure()){
    std::cerr << "Error initializing JetCleaningTool" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
