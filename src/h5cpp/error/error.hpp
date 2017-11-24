//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 25, 2017
//
#pragma once

#include <h5cpp/core/windows.hpp>
#include <h5cpp/error/h5c_error.hpp>

namespace hdf5 {
namespace error {

//!
//! \brief singleton class for HDF5 error handling
//!
//! This class facilitates handling of errors originating in
//! the underlying C-API and HDF5 library. Singleton pattern assures
//! a unique point of access to HDF5's active error stack.
//!

class DLL_EXPORT Singleton
{
 public:

  //!
  //! \brief reference to singleton
  //!
  //! Use this static function to access the singleton
  //!
  static Singleton& instance()
  {
    static Singleton singleton_instance;
    return singleton_instance;
  }

  //!
  //! \brief toggle automatic printing of error stack
  //!
  //! By default, HDF5 prints the error stack to sterr upon the occurrence
  //! of every error. Turning this off redirects the stack to be passed out
  //! to the client using nested exceptions.
  //!
  //! \param enable
  //!
  void auto_print(bool enable);

  //!
  //! \brief indicates if automatic printing of error stack is on
  //!
  bool auto_print() const;

  //!
  //! \brief returns most recent error stack as string
  //!
  //! Only works if auto_print is disabled. Returns a printout of the HDF5
  //! error stack resulting from the most recent error condition(s).
  //!
  std::string print_stack();

  //!
  //! \brief returns most recent error stack as Stack
  //!
  //! Only works if auto_print is disabled. Returns a Stack (derived exception)
  //! as extracted from the HDF5 error stack of the most recent error condition(s).
  //!
  H5CError extract_stack();

  //!
  //! \brief throws an exception, potentially nested with error stack
  //!
  //! If auto_print is enabled, throws std::runtime_error. If auto_print is disabled,
  //! it also extracts the error stack and throws a nested exception, with the Stack
  //! object one level deeper. This function is to be used by most other functions
  //! implementing this HDF5 wrapper.
  //!
  //! \param message a user-supplied message for the exception
  //!
  void throw_with_stack(const std::string& message);

 private:

  // Singleton assurance
  Singleton() {}
  Singleton(Singleton const&) = delete;
  void operator=(Singleton const&) = delete;

  bool auto_print_ {true};

 private:
  // Helper functions, used internally only

  // determines if automatic printing is anebled
  // should never be used when extracting error information,
  // as it will overwirte existing error stack contents
  bool auto_print_enabled() const;

  // extracts error stack and throws it as Stcak
  void throw_stack();

  // clears error stack
  void clear_stack();

  // functor for H5EWalk
  static herr_t to_list(unsigned n,
                        const H5E_error2_t *err_desc,
                        std::list<Descriptor>* list);
};


//!
//! \brief indented output of nested exceptions and included error stack
//!
//! This recursive function is provided for formatted output of nested exceptions and,
//! if included, the extracted error stack. For each level of nesting and for each
//! level of the error stack, the output is on a new line and incrementally indented.
//!
//! \param exception
//!
//! \param level indentation level
//!
std::string DLL_EXPORT print_nested(const std::exception& exception, int level =  0);


} // namespace file
} // namespace hdf5
