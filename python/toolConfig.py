"""
Test python module for configuring a tool
"""

def configTool(tool):
    """Function that configures a tool"""

    print "\nHello from configTool in python!"
    print "You've provided a tool named %s" % tool.name()
    print ""

    # Configure the tool
    tool.setProperty("CutLevel", "MediumBad")

    # Test exception throwing
    #if tool.setProperty("BadProp", "BadVal").isFailure():
        #raise Exception("BadProperty")
