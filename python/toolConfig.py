"""
Test python module for configuring a tool
"""

# Test pythonization here first
from .pythonization import pythonize_tool

def configTool(tool):
    """Function that configures a tool"""

    print "\nHello from configTool in python!"
    print "You've provided a tool named %s" % tool.name()

    # Try pythonizing the tool
    try:
        pythonize_tool(tool)
    except Exception as e:
        print e
        raise e
    print dir(tool)

    # Configure the tool via the pythonized properties
    print "Trying to set CutLevel"
    tool.CutLevel = "MediumBad"
    tool.OutputLevel = 2

    # Configure the tool via prop mgr
    #tool.setProperty("CutLevel", "MediumBad")

    # Test exception throwing
    #if tool.setProperty("BadProp", "BadVal").isFailure():
        #raise Exception("BadProperty")

    # Test adding attributes
    #tool.py_attr = 2
    #print "tool.py_attr %g" % tool.py_attr

    # Test initialization here
    tool.initialize()

    print ""
