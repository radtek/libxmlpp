// -*- C++ -*-

/* main.cc
 *
 * Copyright (C) 2002 The libxml++ development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libxml++/libxml++.h>

#include <iostream>

int main(int argc, char* argv[])
{
  Glib::ustring dtdfilepath;
  if(argc > 1)
    dtdfilepath = argv[1]; //Allow the user to specify a different dtd file to use.
  else
    dtdfilepath = "example.dtd";

  xmlpp::Document document;
  xmlpp::Element* nodeRoot = document.create_root_node("incorrect");

  try
  {
    xmlpp::DtdValidator validator( dtdfilepath );
    try {
      validator.validate( &document );
      std::cout << "Validation successfull" << std::endl;
    }
    catch( const xmlpp::validity_error& )
    {
      std::cout << "Error validating the document" << std::endl;
    }

    xmlpp::Element* nodeRoot = document.create_root_node("example");
    xmlpp::Element * child = document.get_root_node()->add_child("examplechild");
    child->set_attribute("id", "an_id");
    child->add_child("child_of_child");

    try
    {
      xmlpp::DtdValidator validator( dtdfilepath );
      validator.validate( &document );
      std::cout << "Validation successfull" << std::endl;
    }
    catch( const xmlpp::validity_error& )
    {
      std::cout << "Error validating the document" << std::endl;
    }
  }
  catch( const xmlpp::parse_error& )
  {
    std::cerr << "Error parsing the dtd" << std::endl;
  }

}

