#include "PyToolTests/TestTool.h"

TestTool::TestTool(const std::string& name)
  : asg::AsgTool(name)
{
  declareProperty("MyString", m_string);
  declareProperty("MyInt", m_int);
  declareProperty("MyFloat", m_float);
}

StatusCode TestTool::initialize()
{
  ATH_MSG_INFO("initializing with string " << m_string <<
               ", int " << m_int << ", float " << m_float);
  ATH_MSG_INFO("message lvl: " << MSG::name(msg().level()));
  return StatusCode::SUCCESS;
}
