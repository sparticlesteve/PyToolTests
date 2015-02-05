"""
This module contains the utilities for pythonizing ASG dual-use tools.
Pythonizing in this context means taking the properties declared in the
property manager and turning them into python property attributes so
the user can set them in a pythonic way.
"""

def generate_getter(prop_name):
    """Generate a getter for the tool property"""
    def get_prop(self):
        return self.getProperty(prop_name)
    return get_prop

def generate_setter(prop_name):
    """Generate a setter for the tool property"""
    def set_prop(self, val):
        return self.setProperty(type(val))(prop_name, val)
    return set_prop

def pythonize_tool(tool):
    """Pythonize an ASG dual-use tool"""
    # Loop over tool properties
    for prop_name, prop in tool.getPropertyMgr().getProperties():
        # Dynamically build python property attribute and bind it to
        # the tool class. Note: cannot bind to a single instance.
        get_prop = generate_getter(prop_name)
        set_prop = generate_setter(prop_name)
        setattr(type(tool), prop_name, property(get_prop, set_prop))
