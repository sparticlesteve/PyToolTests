"""
Test python module for configuring a tool
"""

from ROOT import MSG

def configTool(tool):
    """Function that configures a tool"""
    # Configure the tool via the pythonized properties
    tool.MyString = "SuperDuper"
    tool.MyInt = 5
    tool.MyFloat = 3.14
    tool.OutputLevel = MSG.DEBUG
