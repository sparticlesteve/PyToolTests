"""
Python wrapper code for setting up and calling user config.
Contains the utilities for pythonizing a dual-use tool.
Pythonizing in this context means taking the properties declared in
the property manager and turning them into python property attributes
so the user can set them in a pythonic way.
"""

import importlib

def generate_getter(prop_name):
    """Generate a getter for the tool property. Doesn't work"""
    def get_prop(self):
        # Doesn't work.
        return self.getProperty(prop_name)
    return get_prop

def generate_setter(prop_name):
    """Generate a setter for the tool property"""
    def set_prop(self, val):
        # Need specialization for OutputLevel enum
        if prop_name == 'OutputLevel':
            self.msg().setLevel(val)
        else:
            # Call the template method proxy
            c = self.setProperty(type(val))(prop_name, val)
            if c.isFailure():
                raise Exception('Error setting property: ' + prop_name)
    return set_prop

def pythonize_tool(tool):
    """Pythonize an ASG dual-use tool"""
    # Loop over tool properties
    for prop_name, prop in tool.getPropertyMgr().getProperties():
        # Build python property attribute and bind it to tool class
        get_prop = generate_getter(prop_name)
        set_prop = generate_setter(prop_name)
        setattr(type(tool), prop_name, property(get_prop, set_prop))

def execute_user_func(tool, user_mod_name, user_func_name):
    """
    Pythonizes tool and applies user function.
    Also catches any exceptions and prints them.
    """
    try:
        # Import the user function
        user_mod = importlib.import_module(user_mod_name)
        user_func = getattr(user_mod, user_func_name)
        # Pythonize the tool
        pythonize_tool(tool)
        # Call user function
        user_func(tool)
    except Exception as e:
        print e
        raise e

