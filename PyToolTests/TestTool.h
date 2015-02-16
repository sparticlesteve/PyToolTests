#ifndef PYTOOLTESTS_TESTTOOL_H
#define PYTOOLTESTS_TESTTOOL_H

#include "AsgTools/AsgTool.h"

/// A class for testing PyROOT tool configuration
class TestTool : public asg::AsgTool
{

    ASG_TOOL_CLASS0(TestTool)

  public:

    TestTool(const std::string& name);

    StatusCode initialize();

  private:

    std::string m_string;
    int m_int;
    float m_float;

};

#endif
