# Copyright 2013 Tecent Inc.
# All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish, dis-
# tribute, sublicense, and/or sell copies of the Software, and to permit
# persons to whom the Software is furnished to do so, subject to the fol-
# lowing conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABIL-
# ITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
# SHALL THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#



"""
    Configure Class For ini

"""
 
import ConfigParser


class Conf:

  def __init__(self, conf_file):
    """Constructor.
    
    Args:
      conf_file: A file of configure
    
    """
    self.conf_file = conf_file
    
    self.oConf = ConfigParser.ConfigParser()
    self.oConf.read(self.conf_file)
    

  def get(self, conf_section, conf_key):
    """Get configure
    
    Args:
      conf_section:Name of section
      conf_key:Name of key
    Returns:   
      string:configure OR empty if no exists
    """
    try:
      return self.oConf.get(conf_section, conf_key)
    except Exception:
      return ""
    
    
    
  
  
  
  
  
  